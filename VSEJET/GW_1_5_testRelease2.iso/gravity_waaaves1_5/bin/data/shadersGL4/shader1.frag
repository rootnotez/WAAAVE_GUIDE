#version 460

uniform int ch1HdAspectOn;
uniform int ch2HdAspectOn;
uniform vec2 ch1HdAspectXYFix;
const float PI=3.1415926535;
const float TWO_PI=6.2831855;

uniform sampler2DRect ch1Tex;
uniform sampler2DRect ch2Tex;
uniform sampler2DRect tex0; //fb2 for now
uniform sampler2DRect fb1TemporalFilter;

uniform vec2 input1XYFix;
	

uniform float inverseWidth1;
uniform float inverseHeight1;

uniform float hdFixX;
uniform float hdFixY;



uniform float ratio;

uniform float width;
uniform float height;
uniform float inverseWidth;
uniform float inverseHeight;

uniform float ch1AspectRatio;
uniform float ch1HdZCrib;
uniform float ch1ScaleFix;

uniform vec2 ch1XYDisplace;
uniform float ch1ZDisplace;
uniform float ch1Rotate;
uniform vec3 ch1HSBAttenuate;
uniform float ch1Posterize;
uniform float ch1PosterizeInvert;
uniform int ch1PosterizeSwitch;
uniform float ch1KaleidoscopeAmount;
uniform float ch1KaleidoscopeSlice;
uniform float ch1BlurAmount;
uniform float ch1BlurRadius;
uniform float ch1SharpenAmount;
uniform float ch1SharpenRadius;
uniform float ch1FiltersBoost;	

uniform int ch1HMirror;
uniform int ch1VMirror;
uniform int ch1HFlip;
uniform int ch1VFlip;
uniform int ch1HueInvert;
uniform int ch1SaturationInvert;
uniform int ch1BrightInvert;
uniform int ch1RGBInvert;
uniform int ch1GeoOverflow;
uniform int ch1Solarize;

uniform float ch2AspectRatio;
uniform float ch2HdZCrib;
uniform float ch2ScaleFix;


uniform float ch2MixAmount;
uniform vec3 ch2KeyValue;
uniform float ch2KeyThreshold;
uniform float ch2KeySoft;	
uniform int ch2MixType;
uniform int ch2MixOverflow;
uniform int ch2KeyOrder;

uniform vec2 ch2XYDisplace;
uniform float ch2ZDisplace;
uniform float ch2Rotate;
uniform vec3 ch2HSBAttenuate;
uniform float ch2Posterize;
uniform float ch2PosterizeInvert;
uniform int ch2PosterizeSwitch;
uniform float ch2KaleidoscopeAmount;
uniform float ch2KaleidoscopeSlice;
uniform float ch2BlurAmount;
uniform float ch2BlurRadius;
uniform float ch2SharpenAmount;
uniform float ch2SharpenRadius;
uniform float ch2FiltersBoost;	

uniform int ch2HMirror;
uniform int ch2VMirror;
uniform int ch2HFlip;
uniform int ch2VFlip;
uniform int ch2HueInvert;
uniform int ch2SaturationInvert;
uniform int ch2BrightInvert;
uniform int ch2RGBInvert;
uniform int ch2GeoOverflow;
uniform int ch2Solarize;

uniform float fb1MixAmount;
uniform vec3 fb1KeyValue;
uniform float fb1KeyThreshold;
uniform float fb1KeySoft;	
uniform int fb1MixType;
uniform int fb1MixOverflow;
uniform int fb1KeyOrder;

uniform vec2 fb1XYDisplace;
uniform float fb1ZDisplace;
uniform float fb1Rotate;
uniform vec4 fb1ShearMatrix;
uniform float fb1KaleidoscopeAmount;
uniform float fb1KaleidoscopeSlice;
uniform int fb1HMirror;
uniform int fb1VMirror;
uniform int fb1HFlip;
uniform int fb1VFlip;
uniform int	fb1RotateMode;
uniform	int fb1GeoOverflow;

uniform vec3 fb1HSBOffset;
uniform vec3 fb1HSBAttenuate;
uniform vec3 fb1HSBPowmap;
uniform float fb1HueShaper;
	
uniform float fb1Posterize;
uniform float fb1PosterizeInvert;
uniform int fb1PosterizeSwitch;
uniform int fb1HueInvert;
uniform int fb1SaturationInvert;
uniform int fb1BrightInvert;

//fb1 filters 
uniform	float fb1BlurAmount;
uniform	float fb1BlurRadius;
uniform	float fb1SharpenAmount;
uniform	float fb1SharpenRadius;
uniform	float fb1TemporalFilter1Amount;
uniform	float fb1TemporalFilter1Resonance;
uniform	float fb1TemporalFilter2Amount;
uniform	float fb1TemporalFilter2Resonance;
uniform float fb1FiltersBoost;	

uniform float ch1CribX;
uniform float ch2CribX;
uniform float cribY;

in vec2 texCoordVarying;

out vec4 outputColor;

//color space conversions
vec3 rgb2hsb(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsb2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float hueShaper(float inHue,float shaper){
	inHue=fract(abs(inHue+shaper*sin(inHue*0.3184713) ));
	return inHue;
}

vec3 colorQuantize(vec3 inColor, float amount, float amountInvert){
	
	inColor=inColor*amount;
	inColor=floor(inColor);
	inColor=inColor*amountInvert;

	return inColor;
}

vec4 blurAndSharpen(sampler2DRect blurAndSharpenTex,vec2 coord, float sharpenAmount, float sharpenRadius, float sharpenBoost,float blurRadius,float blurAmount){
	vec4 originalColor=texture2DRect(blurAndSharpenTex,coord);
	
	//blur
	vec4 colorBlur=texture2DRect(blurAndSharpenTex,coord+vec2(blurRadius,blurRadius))
    + texture2DRect(blurAndSharpenTex,coord+vec2(0,blurRadius))
    + texture2DRect(blurAndSharpenTex,coord+vec2(-blurRadius,blurRadius))
    +texture2DRect(blurAndSharpenTex,coord+vec2(-blurRadius,0.0))
    +texture2DRect(blurAndSharpenTex,coord+vec2(-blurRadius,-blurRadius))
    +texture2DRect(blurAndSharpenTex,coord+vec2(0.0,-blurRadius))
    +texture2DRect(blurAndSharpenTex,coord+vec2(blurRadius,-blurRadius))
    +texture2DRect(blurAndSharpenTex,coord+vec2(blurRadius,0.0));

	colorBlur*=.125;

	colorBlur=mix(originalColor,colorBlur,blurAmount);

	//sharpen
    float color_sharpen_bright=
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(sharpenRadius,0)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(-sharpenRadius,0)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(0,sharpenRadius)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(0,-sharpenRadius)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(sharpenRadius,sharpenRadius)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(-sharpenRadius,sharpenRadius)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(sharpenRadius,-sharpenRadius)).rgb).z+
    rgb2hsb(texture2DRect(blurAndSharpenTex,coord+vec2(-sharpenRadius,-sharpenRadius)).rgb).z;
    
    color_sharpen_bright=color_sharpen_bright*.125;
    
    vec3 colorBlurHsb=rgb2hsb(colorBlur.rgb);
    colorBlurHsb.z-=(sharpenAmount)*color_sharpen_bright;
    
    //try baking in the sharpenBoost into the amount
    //this does not work so well over here lol
    if(sharpenAmount>0){
        colorBlurHsb.z*=(1.0+sharpenAmount+sharpenBoost);
    }
    
    return vec4(hsb2rgb(colorBlurHsb),1.0);
}


vec2 rotate(vec2 coord,float theta,int mode){

	vec2 rotate_coord=vec2(0,0);
	//this version does not preserve aspect ratio
	if(mode==0){
		vec2 center_coord=vec2(coord.x-width/2,coord.y-height/2);
		float spiral=abs(coord.x+coord.y)/2*width;
		coord.x=spiral+coord.x;
		coord.y=spiral+coord.y;
		rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
		rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
		rotate_coord=rotate_coord+vec2(width/2,height/2);
	}
	//so lets try one that does and see what happens
	//so this works, can try switchable versions for a bit and see how one feels
	//while this preserves the aspect ratio of what feeds into it,
	//the other version is always circular which is def fun a lot of time.
	if(mode==1){
		vec2 center_coord=vec2((coord.x-width/2)*inverseWidth,(coord.y-height/2)*inverseHeight);
		float spiral=abs(coord.x+coord.y)/2*width;
		coord.x=spiral+coord.x;
		coord.y=spiral+coord.y;
		rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
		rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
		//rotate_coord=rotate_coord+vec2(width/2,height/2);
		rotate_coord.x=width*rotate_coord.x+width/2;
		rotate_coord.y=height*rotate_coord.y+height/2;
	}

    return rotate_coord;
    
    
}//endrotate

vec2 rotate1(vec2 coord,float theta,int mode){
	float width1=640.0;
	float height1=480.0;
	vec2 rotate_coord=vec2(0,0);
	//this version does not preserve aspect ratio
	if(mode==0){
		vec2 center_coord=vec2(coord.x-width1/2,coord.y-height1/2);
		float spiral=abs(coord.x+coord.y)/2*width1;
		coord.x=spiral+coord.x;
		coord.y=spiral+coord.y;
		rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
		rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
		rotate_coord=rotate_coord+vec2(width1/2,height1/2);
	}
	//so lets try one that does and see what happens
	//so this works, can try switchable versions for a bit and see how one feels
	//while this preserves the aspect ratio of what feeds into it,
	//the other version is always circular which is def fun a lot of time.
	if(mode==1){
		vec2 center_coord=vec2((coord.x-width1/2)*inverseWidth1,(coord.y-height1/2)*inverseHeight1);
		float spiral=abs(coord.x+coord.y)/2*width1;
		coord.x=spiral+coord.x;
		coord.y=spiral+coord.y;
		rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
		rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
		//rotate_coord=rotate_coord+vec2(width1/2,height1/2);
		rotate_coord.x=width1*rotate_coord.x+width1/2;
		rotate_coord.y=height1*rotate_coord.y+height1/2;
	}

    return rotate_coord;
    
    
}//endrotate


vec2 kaleidoscope(vec2 inCoord, float segment, float slice){
	if(segment>0.0){
	//question: can we rotate the coords in here to select which portion of the screen we
	//are kaleidoscoping from??
		inCoord=rotate(inCoord,slice,1);

		inCoord.x=inCoord.x/width;
		inCoord.y=inCoord.y/height;

		inCoord=2.0*inCoord-1.0;
	
		float radius=sqrt( dot(inCoord,inCoord) );
		float angle=atan(inCoord.y,inCoord.x);
		float segmentAngle=TWO_PI/segment;
		angle-=segmentAngle*floor(angle/segmentAngle);
		angle=min(angle,segmentAngle-angle);
		inCoord=radius*vec2(cos(angle),sin(angle));

		inCoord=.5*(inCoord+1.0);
		inCoord.x*=width;
		inCoord.y*=height;

		inCoord=rotate1(inCoord,-slice,1);
	}
	return inCoord;
}



vec2 kaleidoscope1(vec2 inCoord, float segment, float slice){
	if(segment>0.0){
	//question: can we rotate the coords in here to select which portion of the screen we
	//are kaleidoscoping from??
		float width1=640;
		float height1=480;
		inCoord=rotate1(inCoord,slice,0);

		inCoord.x=inCoord.x/width1;
		inCoord.y=inCoord.y/height1;

		inCoord=2.0*inCoord-1.0;
	
		float radius=sqrt( dot(inCoord,inCoord) );
		float angle=atan(inCoord.y,inCoord.x);
		float segmentAngle=TWO_PI/segment;
		angle-=segmentAngle*floor(angle/segmentAngle);
		angle=min(angle,segmentAngle-angle);
		inCoord=radius*vec2(cos(angle),sin(angle));

		inCoord=.5*(inCoord+1.0);
		inCoord.x*=width1;
		inCoord.y*=height1;

		inCoord=rotate1(inCoord,-slice,0);
	}
	return inCoord;
}


//takes in coords and shears them
vec2 shear(vec2 inCoord, vec4 shearMatrix){
	inCoord.x-=640;
	inCoord.y-=360;

	inCoord.x=shearMatrix.x*inCoord.x+shearMatrix.y*inCoord.y;
	inCoord.y=shearMatrix.z*inCoord.x+shearMatrix.w*inCoord.y;

	inCoord.x+=640;
	inCoord.y+=360;
	return inCoord;
}


float mirror(float a){
	if(a>0){return a;}
	if(a<0){return -(1+a);}
}

vec2 wrapCoord(vec2 coord){
    
    //if(abs(coord.x)>width){coord.x=abs(width-coord.x);}
    //if(abs(coord.y)>height){coord.y=abs(height-coord.y);}
    
    coord.x=mod(coord.x,width);
    coord.y=mod(coord.y,height);
    
    return coord;
}

vec2 mirrorCoord(vec2 coord){
	float widthLess=width-1.0;
	float heightLess=height-1.0;

    coord.x=(widthLess)-mirror(mod(coord.x,2.0*widthLess)-widthLess);
    coord.y=(heightLess)-mirror(mod(coord.y,2.0*heightLess)-heightLess);
    
    return coord;
}



vec2 wrapCoord1(vec2 coord){
    float width1=640;
	float height1=480;
    //if(abs(coord.x)>width1){coord.x=abs(width1-coord.x);}
    //if(abs(coord.y)>height1){coord.y=abs(height1-coord.y);}
    
    coord.x=mod(coord.x,width1);
    coord.y=mod(coord.y,height1);
    
    return coord;
}

vec2 mirrorCoord1(vec2 coord){
	float width1=639;
	float height1=479;
    //trying out a different kind of wrapping for rotations
    /*
    if(coord.x>width1){coord.x=width1-mod(coord.x,width1);}
    if(coord.y>height1){coord.y=height1-mod(coord.y,height1);}
    
    if(coord.x<0){coord.x=abs(coord.x);}
    if(coord.y<0){coord.y=abs(coord.y);}
    */
    coord.x=(width1)-mirror(mod(coord.x,2.0*width1)-width1-1.0);
    coord.y=(height1)-mirror(mod(coord.y,2.0*height1)-height1-1.0);
    
    return coord;
}

//general signal utilities
float wrap(float inColor){

	if(inColor<0.0){
		inColor=1.0-abs(inColor);
	}

	if(inColor>1.0){
		inColor=fract(inColor);
	}

	return inColor;
}

float foldover(float inColor){

	if(inColor<0.0){
		inColor=abs(inColor);
	}

	if(inColor>1.0){
		inColor=1.0-(fract(inColor));
	}

	if(inColor<0.0){
		inColor=abs(inColor);
	}
	return inColor;
}

//MIX
//fg is foreground color, bg is background
//mixOverflowModes 0-clamp,1 wrap,2 fold
//keying notes: keyvalue is vec3, if we want to lumakey we have the rgb values for keyvalue be constant
//keying logic is taken care of outside of the function

vec4 mixnKeyVideo(vec4 fg, vec4 bg, float amount, int selectMixMode, float keyThreshold,
float keySoft,vec3 keyValue,int keyOrder,int mixOverflow,vec4 mask,int keyMaskSwitch){
	//vec3 fgHsb=rgb2hsb(vec3(fg.rgb));
	//float fgBright=rgb2hsv(vec3(fg.rgb)).z;

	//might need to troubleshoot order of operations here??
	//keying
	if(keyOrder==1){
		vec4 dummy=fg;
		fg=bg;
		bg=dummy;
	}

	vec4 outColor=vec4(0.0,0.0,0.0,1.0);
	//lerp
	if(selectMixMode==0){
		outColor=mix(fg, bg, amount);
	}
	//addsubtrack
	if(selectMixMode==1){
		outColor.rgb=fg.rgb+amount*bg.rgb;
	}

	//difference
	if(selectMixMode==2){
		outColor.rgb=abs(fg.rgb-amount*bg.rgb);
	}

	//mult
	if(selectMixMode==3){
		outColor.rgb=mix(fg.rgb,fg.rgb*bg.rgb,amount);
	}

	//dodge
	if(selectMixMode==4){
		outColor.rgb=mix(fg.rgb,fg.rgb/(1.00001-bg.rgb),amount);
	}

	//clamp, wrap, fold
	if(mixOverflow==0){
		outColor.rgb=clamp(outColor.rgb,0.0,1.0);
	}

	if(mixOverflow==1){
		//outColor.rgb=fract(abs(outColor.rgb));
		outColor.r=wrap(outColor.r);
		outColor.g=wrap(outColor.g);
		outColor.b=wrap(outColor.b);
	}

	if(mixOverflow==2){
	//foldover
		outColor.r=foldover(outColor.r);
		outColor.g=foldover(outColor.g);
		outColor.b=foldover(outColor.b);
	}
	//alpha, i think this is NAM??
	/*
	if(selectMixMode==3){
		fg.a=mix(fg.a,fgHsb.z,amount);
		outColor=mix(fg,fg*bg,amount);
	}
	//OK I HAVE AN IDEA
	//key between fg and bg with max(fg,bg*amount) as a test
	//NAM??
	if(selectMixMode==3){
		fg.a=mix(fg.a,fgHsb.z,amount);
		outColor=mix(fg,fg*bg,amount);
	}
	*/
	

	float chromaDistance=distance(keyValue,fg.rgb);
	float lower=chromaDistance-keyThreshold;

	if( chromaDistance < keyThreshold ){
		//outColor=mix(bg,fg,keySoft*(abs(keyValue-lower)/lower));

		//i don't quite think this is working, lets try something else some 
		//other time...I think the way to do it is to have generated a blur earlier in the
		//chain, and use the blurred value to 
		outColor=mix(bg,outColor,keySoft*abs(1.0-(chromaDistance-keyThreshold)));
		//outColor=bg;
		//outColor=mix(bg,fg,keySoft*abs(1.0-(chromaDistance-keyThreshold)));
	 }

	 //add an outline to the key value
	 //lets add the ability to thicken it as well
	 //this kinda looks like shit but maybe also with a blur?
	 /*
	 vec4 keyOutlineColor = vec4(0.0,1.0,0.0,1.0);
	 float outlineThreshold=.01;
	 if( abs(chromaDistance-keyThreshold)<= outlineThreshold ){
		outColor=keyOutlineColor;
	 }
	*/


	//so masking will be a different mode than luma or chromakeying so
	//will need to have a different switch for that integrated in here lol
	
	//taking for granted that the mask is in greyscale so any rgb value can be
	//used as test
	//starting off with 1 (white) returns fg and 0 (black) returns bg
	if(keyMaskSwitch==1){
		outColor=mix(outColor,bg,mask.g);
	}
	return outColor;
}


float solarize(float inBright){
	if(inBright>.5){inBright=1.0-inBright;}
	return inBright;
}

void main()
{
	//CHANNEL1-
	//NEW FIXED input scaling and repositioning
	vec2 ch1Coords=texCoordVarying;
	
	ch1Coords.x*=ch1AspectRatio;
	//this centers image but not coords
	ch1Coords-=vec2(320+ch1CribX,120);
	
	//this centers coords so scaling works properly
	//we want to offer a switch for PILLAR BOX or FULLSCREEN SD mode
	ch1Coords-=vec2(320,240);
	ch1Coords*=ch1ScaleFix+ch1HdZCrib;
	//something else we might want to do in here
	//is to add a fudge factor to the x b/c it seems like theres some aspect 
	//ratio issues even with usb cameras...
	ch1Coords+=vec2(320,240);
	//of course this works, 320+320=640, 240+120=360, (640,360) is center of (1280,720)
	
	
	//new hd fix attempt
	if(ch1HdAspectOn==1){
		ch1Coords=texCoordVarying;
		ch1Coords.y=ch1HdAspectXYFix.y*ch1Coords.y;
		ch1Coords.x=ch1HdAspectXYFix.x*ch1Coords.x;
	}
	
	
	if(ch1HFlip==1){
		ch1Coords.x=640-ch1Coords.x;
	}
	if(ch1VFlip==1){
		ch1Coords.y=480-ch1Coords.y;
	}
	
	if(ch1HMirror==1){
        if(ch1Coords.x.x>320.0){ch1Coords.x=abs(640-ch1Coords.x);}
    }//endifhflip1
    if(ch1VMirror==1){
        if(ch1Coords.y>240.0){ch1Coords.y=abs(480-ch1Coords.y);}
    }//endifvflip1
	
	ch1Coords=kaleidoscope1(ch1Coords,ch1KaleidoscopeAmount,ch1KaleidoscopeSlice);
	
		
	ch1Coords+=ch1XYDisplace;	
	
	//zdisplace
	ch1Coords-=vec2(320.0,240.0);
	ch1Coords=ch1Coords*(ch1ZDisplace);
	//gonna need to double check this
	//ch1Coords=ch1Coords*(1.0+ch1ZDisplace+ch1HdZCrib);
	ch1Coords+=vec2(320.0,240.0);
	
	ch1Coords=rotate1(ch1Coords,ch1Rotate,0);		
		
	if(ch1GeoOverflow==1){ch1Coords=wrapCoord1(ch1Coords);}
	if(ch1GeoOverflow==2){ch1Coords=mirrorCoord1(ch1Coords);}	
	
	
	//add blur and sharpen here	
	vec4 ch1Color=blurAndSharpen(ch1Tex,ch1Coords,ch1SharpenAmount,ch1SharpenRadius,
		ch1FiltersBoost,ch1BlurRadius,ch1BlurAmount);
	
    //vec4 ch1Color = texture(ch1Tex, ch1Coords);
	//ch1Color.rgb=1.0-ch1Color.rgb;
	
	//clamp shits out
	if(ch1Coords.x>640.0 || ch1Coords.y> 480.0 || ch1Coords.x<0.0 || ch1Coords.y<0.0){
		ch1Color=vec4(0.0);
	}

    //ch1Color.rgb+=ch1HSBAttenuate;
    //experiment more with this...
	//ch1Color.rgb+=(1.0-ch1HSBAttenuate);
	vec3 ch1ColorHSB=rgb2hsb(ch1Color.rgb);
	
	//ch1ColorHSB*=ch1HSBAttenuate;
	ch1ColorHSB=pow(ch1ColorHSB,ch1HSBAttenuate);	
	
	
	//inverts
	if(ch1HueInvert==1){ch1ColorHSB.x=1.0-ch1ColorHSB.x;}
	if(ch1SaturationInvert==1){ch1ColorHSB.y=1.0-ch1ColorHSB.y;}
	if(ch1BrightInvert==1){ch1ColorHSB.z=1.0-ch1ColorHSB.z;}
	
	ch1ColorHSB.x=fract(ch1ColorHSB.x);
	
	if(ch1Solarize==1){
		ch1ColorHSB.z=solarize(ch1ColorHSB.z);
		//if(ch1ColorHSB.z>.5){ch1ColorHSB.z=1.0-ch1ColorHSB.z;}
	}
	
	ch1Color.rgb=hsb2rgb(ch1ColorHSB);
	
	
	if(ch1RGBInvert==1){ch1Color.rgb=1.0-ch1Color.rgb;}
	
	if(ch1PosterizeSwitch==1){
		ch1Color.rgb=colorQuantize(ch1Color.rgb,ch1Posterize,ch1PosterizeInvert);
	}
	
	
	
	
	
	
	
	/*
	//CHANNEL2
	vec2 ch2Coords=texCoordVarying*ratio;
	ch2Coords.x*=ch2AspectRatio;
	
	ch2Coords+=vec2(ch2CribX,cribY);
		
	ch2Coords+=ch2XYDisplace;	
	
	//zdisplace
	ch2Coords-=vec2(320.0,240.0);
	ch2Coords=ch2Coords*(1.0+ch2ZDisplace);
	ch2Coords+=vec2(320.0,240.0);
		
    vec4 ch2Color = texture(ch2Tex, ch2Coords);
	//ch2Color.rgb=1.0-ch2Color.rgb;
	
	//clamp shits out
	if(ch2Coords.x>640.0 || ch2Coords.y> 480.0 || ch2Coords.x<0.0 || ch2Coords.y<0.0){
		ch2Color=vec4(0.0);
	}
	
	*/
	
	
	
	//NEW FIXED input scaling and repositioning
	vec2 ch2Coords=texCoordVarying;
	
	ch2Coords.x*=ch2AspectRatio;
	//this centers image but not coords
	ch2Coords-=vec2(320+ch2CribX,120);
	
	//this centers coords so scaling works properly
	//we want to offer a switch for PILLAR BOX or FULLSCREEN SD mode
	ch2Coords-=vec2(320,240);
	ch2Coords*=ch2ScaleFix+ch2HdZCrib;
	//something else we might want to do in here
	//is to add a fudge factor to the x b/c it seems like theres some aspect 
	//ratio issues even with usb cameras...
	ch2Coords+=vec2(320,240);
	//of course this works, 320+320=640, 240+120=360, (640,360) is center of (1280,720)
	
	
	//new hd fix attempt
	if(ch2HdAspectOn==1){
		ch2Coords=texCoordVarying;
		ch2Coords.y=ch1HdAspectXYFix.y*ch2Coords.y;
		ch2Coords.x=ch1HdAspectXYFix.x*ch2Coords.x;
	}
	
	
	if(ch2HFlip==1){
		ch2Coords.x=640-ch2Coords.x;
	}
	if(ch2VFlip==1){
		ch2Coords.y=480-ch2Coords.y;
	}
	
	if(ch2HMirror==1){
        if(ch2Coords.x.x>320.0){ch2Coords.x=abs(640-ch2Coords.x);}
    }//endifhflip1
    if(ch2VMirror==1){
        if(ch2Coords.y>240.0){ch2Coords.y=abs(480-ch2Coords.y);}
    }//endifvflip1
	
	ch2Coords=kaleidoscope1(ch2Coords,ch2KaleidoscopeAmount,ch2KaleidoscopeSlice);
	
		
	ch2Coords+=ch2XYDisplace;	
	
	//zdisplace
	ch2Coords-=vec2(320.0,240.0);
	ch2Coords=ch2Coords*(ch2ZDisplace);
	//gonna need to double check this
	//ch2Coords=ch2Coords*(1.0+ch2ZDisplace+ch2HdZCrib);
	ch2Coords+=vec2(320.0,240.0);
	
	ch2Coords=rotate1(ch2Coords,ch2Rotate,0);		
		
	if(ch2GeoOverflow==1){ch2Coords=wrapCoord1(ch2Coords);}
	if(ch2GeoOverflow==2){ch2Coords=mirrorCoord1(ch2Coords);}	
		
	vec4 ch2Color=blurAndSharpen(ch2Tex,ch2Coords,ch2SharpenAmount,ch2SharpenRadius,
		ch2FiltersBoost,ch2BlurRadius,ch2BlurAmount);	
    
	
	//clamp shits out
	if(ch2Coords.x>640.0 || ch2Coords.y> 480.0 || ch2Coords.x<0.0 || ch2Coords.y<0.0){
		ch2Color=vec4(0.0);
	}

	vec3 ch2ColorHSB=rgb2hsb(ch2Color.rgb);
	
	ch2ColorHSB=pow(ch2ColorHSB,ch2HSBAttenuate);
	
	//ch2ColorHSB*=ch2HSBAttenuate;
	
	/*
	if(ch2PosterizeSwitch==1){
		ch2ColorHSB=colorQuantize(ch2ColorHSB,ch2Posterize,ch2PosterizeInvert);
	}	
	*/
	
	//inverts
	if(ch2HueInvert==1){ch2ColorHSB.x=1.0-ch2ColorHSB.x;}
	if(ch2SaturationInvert==1){ch2ColorHSB.y=1.0-ch2ColorHSB.y;}
	if(ch2BrightInvert==1){ch2ColorHSB.z=1.0-ch2ColorHSB.z;}
	
	ch2ColorHSB.x=fract(ch2ColorHSB.x);
	
	if(ch2Solarize==1){
		ch2ColorHSB.z=solarize(ch2ColorHSB.z);
		//if(ch1ColorHSB.z>.5){ch1ColorHSB.z=1.0-ch1ColorHSB.z;}
	}
	
	ch2Color.rgb=hsb2rgb(ch2ColorHSB);
	
	
	if(ch2RGBInvert==1){ch2Color.rgb=1.0-ch2Color.rgb;}
	
	if(ch2PosterizeSwitch==1){
		ch2Color.rgb=colorQuantize(ch2Color.rgb,ch2Posterize,ch2PosterizeInvert);
	}
	
	
	
	
	
	
	//fb1
	vec2 fb1Coords=texCoordVarying;
	vec2 center=vec2(640,360);
	//geometry
	if(fb1HFlip==1){
		fb1Coords.x=width-fb1Coords.x;
	}
	if(fb1VFlip==1){
		fb1Coords.y=height-fb1Coords.y;
	}
	

	if(fb1HMirror==1){
        if(fb1Coords.x.x>width/2){fb1Coords.x=abs(width-fb1Coords.x);}
    }//endifhflip1
    if(fb1VMirror==1){
        if(fb1Coords.y>height/2){fb1Coords.y=abs(height-fb1Coords.y);}
    }//endifvflip1

	fb1Coords=kaleidoscope(fb1Coords,fb1KaleidoscopeAmount,fb1KaleidoscopeSlice);
	/*
	if(fb1HMirror==1){
        //if(fb1Coords.x>width/2){fb1Coords.x=abs(width-fb1Coords.x);}
        if(fb1Coords.x.x>width/2){fb1Coords.x=abs(width-fb1Coords.x);}
    }//endifhflip1
    if(fb1VMirror==1){
        if(fb1Coords.y>height/2){fb1Coords.y=abs(height-fb1Coords.y);}
    }//endifvflip1
    */
	//fb1Coords=kaleidoscope(fb1Coords,5.0,fb1KaleidoscopeSlice);
	fb1Coords+=fb1XYDisplace;
	fb1Coords-=center;
	fb1Coords*=fb1ZDisplace;
	fb1Coords+=center;
	
	fb1Coords=rotate(fb1Coords,fb1Rotate,fb1RotateMode);
	
	fb1Coords=shear(fb1Coords,fb1ShearMatrix);
	
	if(fb1GeoOverflow==1){fb1Coords=wrapCoord(fb1Coords);}
	if(fb1GeoOverflow==2){fb1Coords=mirrorCoord(fb1Coords);}
			
	
	
	//vec4 blurAndSharpen(sampler2DRect blurAndSharpenTex,vec2 coord, float sharpenAmount, float sharpenRadius, float sharpenBoost,float blurRadius,float blurAmount)
	vec4 fb1Color=blurAndSharpen(tex0,fb1Coords,fb1SharpenAmount,fb1SharpenRadius,
		fb1FiltersBoost,fb1BlurRadius,fb1BlurAmount);
	
	//vec4 fb1Color=texture(tex0,fb1Coords);
	
	
	
	//clamp shits out
	if(fb1GeoOverflow==0){
		if(fb1Coords.x>1280.0 || fb1Coords.y> 720.0 || fb1Coords.x<0.0 || fb1Coords.y<0.0){
			fb1Color=vec4(0.0);
		}
	}
	
	//fb1 color biz
	vec3 fb1ColorHSB=rgb2hsb(fb1Color.rgb);
	
	fb1ColorHSB.x=hueShaper(fb1ColorHSB.x,fb1HueShaper);
	fb1ColorHSB+=fb1HSBOffset;
	fb1ColorHSB*=fb1HSBAttenuate;
	fb1ColorHSB=pow(fb1ColorHSB,fb1HSBPowmap);	
	
	/*
	if(fb1PosterizeSwitch==1){
		fb1ColorHSB=colorQuantize(fb1ColorHSB,fb1Posterize,fb1PosterizeInvert);
	}
	*/
	//inverts
	if(fb1HueInvert==1){fb1ColorHSB.x=1.0-fb1ColorHSB.x;}
	if(fb1SaturationInvert==1){fb1ColorHSB.y=1.0-fb1ColorHSB.y;}
	if(fb1BrightInvert==1){fb1ColorHSB.z=1.0-fb1ColorHSB.z;}
	
	
	fb1ColorHSB.x=fract(fb1ColorHSB.x);
	fb1ColorHSB.y=clamp(fb1ColorHSB.y,0.0,1.0);
	fb1ColorHSB.z=clamp(fb1ColorHSB.z,0.0,1.0);
	
	fb1Color.rgb=hsb2rgb(fb1ColorHSB);
	
	if(fb1PosterizeSwitch==1){
		fb1Color.rgb=colorQuantize(fb1Color.rgb,fb1Posterize,fb1PosterizeInvert);
	}
	
	//dummy output color
	//vec4 outColor=vec4(0.0);
	
	
	//mix ch1 with ch2
	vec4 outColor=mixnKeyVideo(ch1Color,ch2Color,ch2MixAmount,ch2MixType,ch2KeyThreshold,
		ch2KeySoft,ch2KeyValue,ch2KeyOrder,ch2MixOverflow,vec4(0.0,0.0,0.0,0.0),0);
	//mix ch2 with fb1
	outColor=mixnKeyVideo(outColor,fb1Color,fb1MixAmount,fb1MixType,fb1KeyThreshold,
		fb1KeySoft,fb1KeyValue,fb1KeyOrder,fb1MixOverflow,vec4(0.0,0.0,0.0,0.0),0);
	
	//temporal filter
	vec4 temporalFilter1Color=texture(fb1TemporalFilter,texCoordVarying);
	vec3 temporalFilter1ColorHSB=rgb2hsb(temporalFilter1Color.rgb);
	vec3 temporalFilter2ColorHSB=temporalFilter1ColorHSB;
	
	//should off board this step out of the shader
	//2 variables, tempFilResSat and tempFilResBright
	temporalFilter1ColorHSB.y=clamp((temporalFilter1ColorHSB.y*(1.0+fb1TemporalFilter1Resonance*.25)),0.0,1.0);
	temporalFilter1ColorHSB.z=clamp((temporalFilter1ColorHSB.z*(1.0+fb1TemporalFilter1Resonance*.5)),0.0,1.0);
	
	temporalFilter1Color.rgb=hsb2rgb(temporalFilter1ColorHSB);
	outColor=clamp(mix(outColor,temporalFilter1Color,fb1TemporalFilter1Amount),0.0,1.0);
	
	temporalFilter2ColorHSB.y=clamp((temporalFilter2ColorHSB.y*(1.0+fb1TemporalFilter2Resonance*.25)),0.0,1.0);
	temporalFilter2ColorHSB.z=clamp((temporalFilter2ColorHSB.z*(1.0+fb1TemporalFilter2Resonance*.5)),0.0,1.0);
	
	vec4 temporalFilter2Color=vec4(hsb2rgb(temporalFilter2ColorHSB),1.0);
	outColor=clamp(mix(outColor,temporalFilter2Color,fb1TemporalFilter2Amount),0.0,1.0);
	
	outColor.a=1.0;	
	outputColor=outColor;
}
