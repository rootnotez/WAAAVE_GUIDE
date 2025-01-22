#version 460

/*
Things that need to be fixed
-resolution biz
*/

const float PI=3.1415926535;
const float TWO_PI=6.2831855;

//NEW BIZ




//uniform sampler2DRect input1Tex;

in vec2 texCoordVarying;

out vec4 outputColor;


uniform sampler2DRect tex0;

uniform float saturation0;
uniform float saturation1;
uniform float saturation2;
uniform float saturation3;
uniform float saturation4;
uniform float saturation5;
uniform float saturation6;
uniform float saturation7;

uniform float hue0;
uniform float hue1;
uniform float hue2;
uniform float hue3;
uniform float hue4;
uniform float hue5;
uniform float hue6;
uniform float hue7;

uniform float bright0;
uniform float bright1;
uniform float bright2;
uniform float bright3;
uniform float bright4;
uniform float bright5;
uniform float bright6;
uniform float bright7;

uniform float hueLfo0;
uniform float hueLfo1;
uniform float hueLfo2;
uniform float hueLfo3;
uniform float hueLfo4;
uniform float hueLfo5;
uniform float hueLfo6;
uniform float hueLfo7;

uniform float brightLfo0;
uniform float brightLfo1;
uniform float brightLfo2;
uniform float brightLfo3;
uniform float brightLfo4;
uniform float brightLfo5;
uniform float brightLfo6;
uniform float brightLfo7;





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

void main()
{
	

	
	
	
	
	
	
	
	
	//NEW BIZ
	//blurrin a lil bit
	//add a switch for this maybe
    float x=1;
	float y=1;
	
	vec4 color=texture(tex0, texCoordVarying)
				+texture(tex0, texCoordVarying+vec2(x,y))
				+texture(tex0, texCoordVarying+vec2(x,-y))
				+texture(tex0, texCoordVarying+vec2(-x,y))
				+texture(tex0, texCoordVarying+vec2(-x,-y))
				+texture(tex0, texCoordVarying+vec2(0,-y))
				+texture(tex0, texCoordVarying+vec2(0,y))
				+texture(tex0, texCoordVarying+vec2(x,0))
				+texture(tex0, texCoordVarying+vec2(-x,0));
				
	color.rgb=color.rgb/9.0;
	
	//convert to HSB
	vec3 colorHsb=rgb2hsb(vec3(color.r,color.g,color.b));
	
	//create the 8 bands & assign hue and saturations
	vec3 bandHsb0=vec3(fract(hue0+hueLfo0),saturation0,colorHsb.z);
	vec3 bandHsb1=vec3(fract(hue1+hueLfo1),saturation1,colorHsb.z);
	vec3 bandHsb2=vec3(fract(hue2+hueLfo2),saturation2,colorHsb.z);
	vec3 bandHsb3=vec3(fract(hue3+hueLfo3),saturation3,colorHsb.z);
	vec3 bandHsb4=vec3(fract(hue4+hueLfo4),saturation4,colorHsb.z);
	vec3 bandHsb5=vec3(fract(hue5+hueLfo5),saturation5,colorHsb.z);
	vec3 bandHsb6=vec3(fract(hue6+hueLfo6),saturation6,colorHsb.z);
	vec3 bandHsb7=vec3(fract(hue7+hueLfo7),saturation7,colorHsb.z);
	
	//offset the brightness
	bandHsb0.z=abs(bandHsb0.z+bright0+brightLfo0);
	bandHsb1.z=abs(bandHsb1.z+bright1+brightLfo1);//if i add any lfo here it kills the output. if i add sin(brightLfo1) its fine....so just manually add 1 lfo here whatever
	//u0date: if i comment out the foldover section that restores brightLfo to working...
	bandHsb2.z=abs(bandHsb2.z+bright2+brightLfo2);
	bandHsb3.z=abs(bandHsb3.z+bright3+brightLfo3);
	bandHsb4.z=abs(bandHsb4.z+bright4+brightLfo4);
	bandHsb5.z=abs(bandHsb5.z+bright5+brightLfo5);
	bandHsb6.z=abs(bandHsb6.z+bright6+brightLfo6);
	bandHsb7.z=abs(bandHsb7.z+bright7+brightLfo7);
	/*bandHsb3.z=abs(bandHsb3.z+bright3+brightLfo3);
	bandHsb4.z=abs(bandHsb4.z+bright4+brightLfo4);
	bandHsb5.z=abs(bandHsb5.z+bright5+brightLfo5);
	bandHsb6.z=abs(bandHsb6.z+bright6+brightLfo6);
	bandHsb7.z=abs(bandHsb7.z+bright7+brightLfo7);
	*/
	
	//try wrapping around
	/*
	bandHsb0.z=fract(bandHsb0.z);
	bandHsb1.z=fract(bandHsb1.z);
	bandHsb2.z=fract(bandHsb2.z);
	bandHsb3.z=fract(bandHsb3.z);
	bandHsb4.z=fract(bandHsb4.z);
	bandHsb5.z=fract(bandHsb5.z);
	bandHsb6.z=fract(bandHsb6.z);
	bandHsb7.z=fract(bandHsb7.z);
	*/
	
	//fold the brightness over instead of wrapping around
	if(bandHsb0.z>1.0){
		bandHsb0.z=abs(1.0-bandHsb0.z);
		bandHsb0.z=1.0-bandHsb0.z;
	}
	
	if(bandHsb1.z>1.0){
		//bandHsb1.z=abs(1.0-bandHsb1.z);
		//bandHsb1.z=1.0-bandHsb1.z;
	}
	
	if(bandHsb2.z>1.0){
		bandHsb2.z=abs(1.0-bandHsb2.z);
		bandHsb2.z=1.0-bandHsb2.z;
	}
	if(bandHsb3.z>1.0){
		bandHsb3.z=abs(1.0-bandHsb3.z);
		bandHsb3.z=1.0-bandHsb3.z;
	}
	if(bandHsb4.z>1.0){
		bandHsb4.z=abs(1.0-bandHsb4.z);
		bandHsb4.z=1.0-bandHsb4.z;
	}
	if(bandHsb5.z>1.0){
		bandHsb5.z=abs(1.0-bandHsb5.z);
		bandHsb5.z=1.0-bandHsb5.z;
	}
	if(bandHsb6.z>1.0){
		bandHsb6.z=abs(1.0-bandHsb6.z);
		bandHsb6.z=1.0-bandHsb6.z;
	}
	if(bandHsb7.z>1.0){
		bandHsb7.z=abs(1.0-bandHsb7.z);
		bandHsb7.z=1.0-bandHsb7.z;
	}
	
	//convert to RGB
	vec3 bandRgb0=hsb2rgb(bandHsb0);
	vec3 bandRgb1=hsb2rgb(bandHsb1);
	vec3 bandRgb2=hsb2rgb(bandHsb2);
	vec3 bandRgb3=hsb2rgb(bandHsb3);
	vec3 bandRgb4=hsb2rgb(bandHsb4);
	vec3 bandRgb5=hsb2rgb(bandHsb5);
	vec3 bandRgb6=hsb2rgb(bandHsb6);
	vec3 bandRgb7=hsb2rgb(bandHsb7);
	
	vec3 colorOutRgb=vec3(0.0);
	
	if(colorHsb.z<.125){
		colorOutRgb=mix(bandRgb0,bandRgb1,colorHsb.z*8.0);
	}
	
	if(colorHsb.z>.125 && colorHsb.z<.25){
		colorOutRgb=mix(bandRgb1,bandRgb2,(colorHsb.z-.125)*8.0);
	}
	if(colorHsb.z>.25 && colorHsb.z<.375){
		colorOutRgb=mix(bandRgb2,bandRgb3,(colorHsb.z-.25)*8.0);
	}
	if(colorHsb.z>.375 && colorHsb.z<.5){
		colorOutRgb=mix(bandRgb3,bandRgb4,(colorHsb.z-.375)*8.0);
	}
	if(colorHsb.z>.5 && colorHsb.z<.625){
		colorOutRgb=mix(bandRgb4,bandRgb5,(colorHsb.z-.5)*8.0);
	}
	if(colorHsb.z>.625 && colorHsb.z<.75){
		colorOutRgb=mix(bandRgb5,bandRgb6,(colorHsb.z-.625)*8.0);
	}
	if(colorHsb.z>.75 && colorHsb.z<.875){
		colorOutRgb=mix(bandRgb6,bandRgb7,(colorHsb.z-.75)*8.0);
	}
	if(colorHsb.z>.875){
		colorOutRgb=bandRgb7;
	}
	
	color.rgb=colorOutRgb;





	outputColor = color;
	
	
	
	
	
	
	
	//outputColor=input1Color;
}
