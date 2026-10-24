precision highp float;

const float TWO_PI = 6.283185307;

uniform sampler2D tex0;

//shear biz
uniform float control1_0;
uniform float control1_1;
uniform float control1_2;
uniform float control1_3;

uniform float control1_4;
uniform float control1_5;
uniform float control1_6;
uniform float control1_7;
//xyz displace
uniform float control1_8;
uniform float control1_9;
uniform float control1_10;

uniform float control1_11;
uniform float control1_12;
uniform float control1_13;

//kaleid
uniform float control1_14;

//lumakey original back in
uniform float control1_15;

//switches
uniform int toroidSwitch;
uniform int mirrorSwitch;

varying vec2 texCoordVarying;
//---------------------------------------------------------- 
vec2 shear(in vec2 inCoord,in vec4 shearMatrix){
	inCoord.x-=0.5;
	inCoord.y-=0.5;

	inCoord.x=shearMatrix.x*inCoord.x+shearMatrix.y*inCoord.y;
	inCoord.y=shearMatrix.z*inCoord.x+shearMatrix.w*inCoord.y;

	inCoord.x+=0.5;
	inCoord.y+=0.5;
	return inCoord;
}
//------------------------------------------------------------------
vec2 spiralize(in vec2 inCoord,in float amount,in float angle,in vec2 center){

	inCoord=2.0*inCoord-1.0;

	float radius=distance(inCoord,vec2(center.x,center.y));
	radius = (amount-radius)/amount;
	float theta=radius*angle;
	float s=sin(theta);
	float c=cos(theta);
	//dang rewrite all the matrix shit this way ya goof
	inCoord= vec2( dot( inCoord, vec2(c,-s) )
				 , dot( inCoord, vec2(s, c) ) );

	inCoord*=.5;
	inCoord+=.5;

	return inCoord;
}
//--------------------------------------------
vec2 kaleidoscope(in vec2 inCoord,in float segment){
	if(segment>0.0){
		//inCoord.xy=inCoord.xy/inDim.xy;
		inCoord=2.0*inCoord-1.0;
	
		float radius=sqrt( dot(inCoord,inCoord) );
		float angle=atan(inCoord.y,inCoord.x);
		float segmentAngle=TWO_PI/segment;
		angle-=segmentAngle*floor(angle/segmentAngle);
		angle=min(angle,segmentAngle-angle);
		inCoord=radius*vec2(cos(angle),sin(angle));

		inCoord=.5*(inCoord+1.0);
		//inCoord.xy=inCoord.xy*inDim.xy;
	}
	return inCoord;
}
//---------------------------------------------------------------

//need to fix what happens when we go 3 screens up (-3 in y direction)
//and three screens over in x direction?
vec2 toroidCoord(in vec2 inCoord){
    
	//how to remove the if statements
	//if inCoord.x> inDim.x then inCoord.x/inDim.x >1 meaning int(inCoord.x/inDim.x)=1 so we can use this as logic
    //if(abs(inCoord.x)>1.0){inCoord.x=abs(1.0-inCoord.x);}
    //if(abs(inCoord.y)>1.0){inCoord.y=abs(1.0-inCoord.y);}
    
	if(abs(inCoord.x)>1.0){inCoord.x=abs(1.0-inCoord.x);}
	if(abs(inCoord.y)>1.0){inCoord.y=abs(1.0-inCoord.y);}
	
	inCoord=fract(inCoord);
	
    return inCoord;
}
//---------------------------------------------------------------
vec2 mirrorCoord(in vec2 inCoord,in vec2 inDim){

	
	if(inCoord.x<0.0){inCoord.x=abs(inCoord.x);}
	if(inCoord.y<0.0){inCoord.y=abs(inCoord.y);}
	inCoord.x=mod(inCoord.x,inDim.x*2.0);
	inCoord.y=mod(inCoord.y,inDim.y*2.0);
    
    if(inCoord.x>inDim.x){inCoord.x=inDim.x-mod(inCoord.x,inDim.x);}
    if(inCoord.y>inDim.y){inCoord.y=inDim.y-mod(inCoord.y,inDim.y);}
    

    return inCoord;
}
//---------------------------------------- 
vec3 rgb2hsb(in vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

//if we want to work with hsb space in shaders we have to
//convert the rgba color into an hsb, do some hsb stuffs
//and then convert back into rgb for the final draw to the screen
vec3 hsb2rgb(in vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec2 coord=texCoordVarying;
	
	coord=kaleidoscope(coord,control1_14);
	
	coord.x+=control1_8;
	coord.y+=control1_9;
	
	coord.xy-=.5;
	coord.xy*=1.0+control1_10;
	coord.xy+=.5;
	
	coord = shear(coord, vec4(1.0+control1_0,control1_1,control1_2,1.0+control1_3));
	
	coord= spiralize(coord, control1_4, control1_5, vec2(control1_6,control1_7));
	
	if(toroidSwitch==1){
		coord=toroidCoord(coord);
	}
	if(mirrorSwitch==1){
		coord=mirrorCoord(coord,vec2(1.0,1.0));
	}
	
	vec4 color = texture2D(tex0, coord);
	if(coord.x>1.0 ||  coord.x<0.0){color=vec4(0.0,0.0,0.0,0.0);}
	if(coord.y>1.0 || coord.y<0.0){color=vec4(0.0,0.0,0.0,0.0);}
		
	//lumakey original signal over the processed signal
	vec4 outColor=texture2D(tex0,texCoordVarying);
	float bright=rgb2hsb(vec3(outColor.r,outColor.g,outColor.b)).z;
	if(bright>control1_15){
		color=outColor;
	}
	
	//work onn this later
	/*
	vec4 outColor=texture2D(tex0,texCoordVarying);
	float chromaDistance=distance(control1_15,outColor.rgb);
	if(chromaDistance>0){
			
	}	
	*/	
	gl_FragColor = color;
}
