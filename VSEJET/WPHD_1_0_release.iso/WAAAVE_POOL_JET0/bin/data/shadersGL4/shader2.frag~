#version 460

const float PI=3.1415926535;
const float TWO_PI=6.2831855;


uniform sampler2DRect block2InputTex;
uniform sampler2DRect tex0; //fb2 for now
uniform sampler2DRect fb2TemporalFilter;

uniform float ratio;
uniform float block2AspectRatio;

uniform float width;
uniform float height;
uniform float inverseWidth;
uniform float inverseHeight;
uniform float inverseWidth1;
uniform float inverseHeight1;

uniform int block2InputMasterSwitch;

uniform float block2InputWidth;
uniform float block2InputHeight;
uniform float block2InputWidthHalf;
uniform float block2InputHeightHalf;

uniform float block2InputAspectRatio;
uniform float block2InputHdZCrib;
uniform float block2InputScaleFix;
uniform float block2InputCribX;

uniform vec2 block2InputXYDisplace;
uniform float block2InputZDisplace;
uniform float block2InputRotate;
uniform vec3 block2InputHSBAttenuate;
uniform float block2InputPosterize;
uniform float block2InputPosterizeInvert;
uniform int block2InputPosterizeSwitch;
uniform float block2InputKaleidoscopeAmount;
uniform float block2InputKaleidoscopeSlice;
uniform float block2InputBlurAmount;
uniform float block2InputBlurRadius;
uniform float block2InputSharpenAmount;
uniform float block2InputSharpenRadius;
uniform float block2InputFiltersBoost;	


uniform int block2InputHMirror;
uniform int block2InputVMirror;
uniform int block2InputHFlip;
uniform int block2InputVFlip;
uniform int block2InputHueInvert;
uniform int block2InputSaturationInvert;
uniform int block2InputBrightInvert;
uniform int block2InputRGBInvert;
uniform int block2InputGeoOverflow;
uniform int block2InputSolarize;


uniform float fb2MixAmount;
uniform vec3 fb2KeyValue;
uniform float fb2KeyThreshold;
uniform float fb2KeySoft;	
uniform int fb2MixType;
uniform int fb2MixOverflow;
uniform int fb2KeyOrder;

uniform vec2 fb2XYDisplace;
uniform float fb2ZDisplace;
uniform float fb2Rotate;
uniform vec4 fb2ShearMatrix;
uniform float fb2KaleidoscopeAmount;
uniform float fb2KaleidoscopeSlice;
uniform int fb2HMirror;
uniform int fb2VMirror;
uniform int fb2HFlip;
uniform int fb2VFlip;

uniform int	fb2RotateMode;
uniform	int fb2GeoOverflow;

uniform vec3 fb2HSBOffset;
uniform vec3 fb2HSBAttenuate;
uniform vec3 fb2HSBPowmap;
uniform float fb2HueShaper;
	
uniform float fb2Posterize;
uniform float fb2PosterizeInvert;
uniform int fb2PosterizeSwitch;
uniform int fb2HueInvert;
uniform int fb2SaturationInvert;
uniform int fb2BrightInvert;

//fb2 filters 
uniform	float fb2BlurAmount;
uniform	float fb2BlurRadius;
uniform	float fb2SharpenAmount;
uniform	float fb2SharpenRadius;
uniform	float fb2TemporalFilter1Amount;
uniform	float fb2TemporalFilter1Resonance;
uniform	float fb2TemporalFilter2Amount;
uniform	float fb2TemporalFilter2Resonance;
uniform float fb2FiltersBoost;	



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

		inCoord=rotate(inCoord,-slice,1);
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

//takes in coords and shears them
vec2 shear1(vec2 inCoord, vec4 shearMatrix){
	inCoord.x-=block2InputWidthHalf;
	inCoord.y-=block2InputHeightHalf;

	inCoord.x=shearMatrix.x*inCoord.x+shearMatrix.y*inCoord.y;
	inCoord.y=shearMatrix.z*inCoord.x+shearMatrix.w*inCoord.y;

	inCoord.x+=block2InputWidthHalf;
	inCoord.y+=block2InputHeightHalf;
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

vec2 wrapCoord1(vec2 coord, float width1, float height1){
   
    coord.x=mod(coord.x,width1);
    coord.y=mod(coord.y,height1);
    
    return coord;
}

vec2 mirrorCoord1(vec2 coord, float width1, float height1){
	
    width1=width1-1.0;
	height1=height1-1.0;
   
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
//mixmodes 0=lerp, 1=add/subtrac, 2=mult, 3=nothing interesting?
//mixOverflowModes 0-clamp,1 wrap,2 fold?;
//notes: do we want to try anything different for subtractive?
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
	/*
	vec2 shader2InputCoords=texCoordVarying*ratio;
	shader2InputCoords.x*=block2AspectRatio;
	vec4 shader2InputColor=texture(shader2Input,shader2InputCoords);
	*/
	
	
	
	
	
	
	
	
	
	
	
	//NEW FIXED input scaling and repositioning
	vec2 block2InputCoords=texCoordVarying;
	
	
	if(block2InputMasterSwitch==1){
		block2InputCoords.x*=block2InputAspectRatio;
		//this centers image but not coords
		block2InputCoords-=vec2(320+block2InputCribX,120);
		
		//this centers coords so scaling works properly
		//we want to offer a switch for PILLAR BOX or FULLSCREEN SD mode
		block2InputCoords-=vec2(320,240);
		block2InputCoords*=block2InputScaleFix+block2InputHdZCrib;
		//something else we might want to do in here
		//is to add a fudge factor to the x b/c it seems like theres some aspect 
		//ratio issues even with usb cameras...
		block2InputCoords+=vec2(320,240);
		//of course this works, 320+320=640, 240+120=360, (640,360) is center of (1280,720)
	}
	
	
	if(block2InputHFlip==1){
		block2InputCoords.x=block2InputWidth-block2InputCoords.x;
	}
	if(block2InputVFlip==1){
		block2InputCoords.y=block2InputHeight-block2InputCoords.y;
	}
	
	if(block2InputHMirror==1){
        if(block2InputCoords.x.x>block2InputWidthHalf){block2InputCoords.x=abs(block2InputWidth-block2InputCoords.x);}
    }//endifhflip1
    if(block2InputVMirror==1){
        if(block2InputCoords.y>block2InputHeightHalf){block2InputCoords.y=abs(block2InputHeight-block2InputCoords.y);}
    }//endifvflip1
	
	if(block2InputWidth==1280){
		block2InputCoords=kaleidoscope(block2InputCoords,block2InputKaleidoscopeAmount,block2InputKaleidoscopeSlice);
	}
	if(block2InputWidth==640){
		block2InputCoords=kaleidoscope1(block2InputCoords,block2InputKaleidoscopeAmount,block2InputKaleidoscopeSlice);		
	}
	
	
	//block2InputCoords=kaleidoscope1(block2InputCoords,block2InputKaleidoscopeAmount,block2InputKaleidoscopeSlice);
	
		
	block2InputCoords+=block2InputXYDisplace;	
	
	//zdisplace
	block2InputCoords-=vec2(block2InputWidthHalf,block2InputHeightHalf);
	block2InputCoords=block2InputCoords*(block2InputZDisplace);
	//gonna need to double check this
	//block2InputCoords=block2InputCoords*(1.0+block2InputZDisplace+block2InputHdZCrib);
	block2InputCoords+=vec2(block2InputWidthHalf,block2InputHeightHalf);
	if(block2InputWidth==1280){
		block2InputCoords=rotate(block2InputCoords,block2InputRotate,0);
	}
	if(block2InputWidth==640){
		block2InputCoords=rotate1(block2InputCoords,block2InputRotate,0);		
	}
	
	//got to fix these...	
	if(block2InputGeoOverflow==1){block2InputCoords=wrapCoord1(block2InputCoords, block2InputWidth,block2InputHeight);}
	if(block2InputGeoOverflow==2){block2InputCoords=mirrorCoord1(block2InputCoords, block2InputWidth,block2InputHeight);}	
		
		
	vec4 block2InputColor=blurAndSharpen(block2InputTex,block2InputCoords,block2InputSharpenAmount,block2InputSharpenRadius,
		block2InputFiltersBoost,block2InputBlurRadius,block2InputBlurAmount);	
    //vec4 block2InputColor = texture(block2InputTex, block2InputCoords);
	//block2InputColor.rgb=1.0-block2InputColor.rgb;
	
	//clamp shits out
	if(block2InputCoords.x>block2InputWidth || block2InputCoords.y> block2InputHeight || block2InputCoords.x<0.0 || block2InputCoords.y<0.0){
		block2InputColor=vec4(0.0);
	}

    //experiment more with this...
	//block2InputColor.rgb+=(1.0-block2InputHSBAttenuate);
	vec3 block2InputColorHSB=rgb2hsb(block2InputColor.rgb);
	
	//block2InputColorHSB*=block2InputHSBAttenuate;
	
	block2InputColorHSB=pow(block2InputColorHSB,block2InputHSBAttenuate);
	
	//inverts
	if(block2InputHueInvert==1){block2InputColorHSB.x=1.0-block2InputColorHSB.x;}
	if(block2InputSaturationInvert==1){block2InputColorHSB.y=1.0-block2InputColorHSB.y;}
	if(block2InputBrightInvert==1){block2InputColorHSB.z=1.0-block2InputColorHSB.z;}
	
	block2InputColorHSB.x=fract(block2InputColorHSB.x);
	
	if(block2InputSolarize==1){
		block2InputColorHSB.z=solarize(block2InputColorHSB.z);
		//if(block2InputColorHSB.z>.5){block2InputColorHSB.z=1.0-block2InputColorHSB.z;}
	}
	
	block2InputColor.rgb=hsb2rgb(block2InputColorHSB);
	
	
	if(block2InputRGBInvert==1){block2InputColor.rgb=1.0-block2InputColor.rgb;}
	
	if(block2InputPosterizeSwitch==1){
		block2InputColor.rgb=colorQuantize(block2InputColor.rgb,block2InputPosterize,block2InputPosterizeInvert);
	}
	
	
	
	
	
	
	
	
	
	/*
	vec2 fb2Coords=texCoordVarying;
	fb2Coords.x-=5.0;
	vec4 fb2Color=texture(tex0,fb2Coords);
	*/
	
	
	//fb2
	vec2 fb2Coords=texCoordVarying;
	vec2 center=vec2(640,360);
	//geometry
	if(fb2HFlip==1){
		fb2Coords.x=width-fb2Coords.x;
	}
	if(fb2VFlip==1){
		fb2Coords.y=height-fb2Coords.y;
	}

	if(fb2HMirror==1){
        if(fb2Coords.x.x>width/2){fb2Coords.x=abs(width-fb2Coords.x);}
    }//endifhflip1
    if(fb2VMirror==1){
        if(fb2Coords.y>height/2){fb2Coords.y=abs(height-fb2Coords.y);}
    }//endifvflip1

	fb2Coords=kaleidoscope(fb2Coords,fb2KaleidoscopeAmount,fb2KaleidoscopeSlice);
	
	fb2Coords+=fb2XYDisplace;
	fb2Coords-=center;
	fb2Coords*=fb2ZDisplace;
	fb2Coords+=center;
	
	fb2Coords=rotate(fb2Coords,fb2Rotate,fb2RotateMode);
	
	fb2Coords=shear(fb2Coords,fb2ShearMatrix);
	
	if(fb2GeoOverflow==1){fb2Coords=wrapCoord(fb2Coords);}
	if(fb2GeoOverflow==2){fb2Coords=mirrorCoord(fb2Coords);}
			
	
	
	//vec4 blurAndSharpen(sampler2DRect blurAndSharpenTex,vec2 coord, float sharpenAmount, float sharpenRadius, float sharpenBoost,float blurRadius,float blurAmount)
	vec4 fb2Color=blurAndSharpen(tex0,fb2Coords,fb2SharpenAmount,fb2SharpenRadius,
		fb2FiltersBoost,fb2BlurRadius,fb2BlurAmount);
	
	//vec4 fb2Color=texture(tex0,fb2Coords);
	
	
	
	//clamp shits out
	if(fb2GeoOverflow==0){
		if(fb2Coords.x>1280.0 || fb2Coords.y> 720.0 || fb2Coords.x<0.0 || fb2Coords.y<0.0){
			fb2Color=vec4(0.0);
		}
	}
	
	//fb2 color biz
	vec3 fb2ColorHSB=rgb2hsb(fb2Color.rgb);
	
	fb2ColorHSB.x=hueShaper(fb2ColorHSB.x,fb2HueShaper);
	fb2ColorHSB+=fb2HSBOffset;
	fb2ColorHSB*=fb2HSBAttenuate;
	fb2ColorHSB=pow(fb2ColorHSB,fb2HSBPowmap);	

	/*
	if(fb2PosterizeSwitch==1){
		fb2ColorHSB=colorQuantize(fb2ColorHSB,fb2Posterize,fb2PosterizeInvert);
	}
	*/
	//inverts
	if(fb2HueInvert==1){fb2ColorHSB.x=1.0-fb2ColorHSB.x;}
	if(fb2SaturationInvert==1){fb2ColorHSB.y=1.0-fb2ColorHSB.y;}
	if(fb2BrightInvert==1){fb2ColorHSB.z=1.0-fb2ColorHSB.z;}
	
	
	fb2ColorHSB.x=fract(fb2ColorHSB.x);
	fb2ColorHSB.y=clamp(fb2ColorHSB.y,0.0,1.0);
	fb2ColorHSB.z=clamp(fb2ColorHSB.z,0.0,1.0);
	fb2Color.rgb=hsb2rgb(fb2ColorHSB);
	
	if(fb2PosterizeSwitch==1){
		fb2Color.rgb=colorQuantize(fb2Color.rgb,fb2Posterize,fb2PosterizeInvert);
	}
	
		
	vec4 outColor=mixnKeyVideo(block2InputColor,fb2Color,fb2MixAmount,fb2MixType,fb2KeyThreshold,fb2KeySoft
					,fb2KeyValue,fb2KeyOrder,fb2MixOverflow,vec4(0.0,0.0,0.0,0.0),0);


	//temporal filter
	//experiment more with temporal filter displacement
	//vec4 temporalFilter1Color=texture(fb2TemporalFilter,texCoordVarying+vec2(.01,.01));
	vec4 temporalFilter1Color=texture(fb2TemporalFilter,texCoordVarying);
	vec3 temporalFilter1ColorHSB=rgb2hsb(temporalFilter1Color.rgb);
	vec3 temporalFilter2ColorHSB=temporalFilter1ColorHSB;
	
	//should off board this step out of the shader
	//2 variables, tempFilResSat and tempFilResBright
	temporalFilter1ColorHSB.y=clamp((temporalFilter1ColorHSB.y*(1.0+fb2TemporalFilter1Resonance*.25)),0.0,1.0);
	temporalFilter1ColorHSB.z=clamp((temporalFilter1ColorHSB.z*(1.0+fb2TemporalFilter1Resonance*.5)),0.0,1.0);
	
	temporalFilter1Color.rgb=hsb2rgb(temporalFilter1ColorHSB);
	outColor=clamp(mix(outColor,temporalFilter1Color,fb2TemporalFilter1Amount),0.0,1.0);
	
	temporalFilter2ColorHSB.y=clamp((temporalFilter2ColorHSB.y*(1.0+fb2TemporalFilter2Resonance*.25)),0.0,1.0);
	temporalFilter2ColorHSB.z=clamp((temporalFilter2ColorHSB.z*(1.0+fb2TemporalFilter2Resonance*.5)),0.0,1.0);
	
	vec4 temporalFilter2Color=vec4(hsb2rgb(temporalFilter2ColorHSB),1.0);
	outColor=clamp(mix(outColor,temporalFilter2Color,fb2TemporalFilter2Amount),0.0,1.0);

	outColor.a=1.0;				
	
	outputColor=outColor;
}
