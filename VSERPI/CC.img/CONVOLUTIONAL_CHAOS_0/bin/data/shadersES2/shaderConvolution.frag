precision highp float;


uniform sampler2D tex0;
uniform sampler2D fb;

uniform float c0;
uniform float c1;
uniform float c2;
uniform float c3;
uniform float c4;
uniform float c5;
uniform float c6;
uniform float c7;
uniform float c8;
uniform float c9;
uniform float c10;
uniform float c11;
uniform float c12;
uniform float c13;
uniform float c14;
uniform float c15;

const float xScale=.0015625;
const float yScale=.0020833;
varying vec2 texCoordVarying;
 
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
	vec4 color = texture2D(tex0, texCoordVarying);
	vec4 fbColor0= texture2D(fb, texCoordVarying+c8*vec2(-xScale,-yScale));
	vec4 fbColor1= texture2D(fb, texCoordVarying+c9*vec2(0.0,-yScale));
	vec4 fbColor2= texture2D(fb, texCoordVarying+c10*vec2(xScale,-yScale));
	vec4 fbColor3= texture2D(fb, texCoordVarying+c11*vec2(xScale,0.0));
	vec4 fbColor4= texture2D(fb, texCoordVarying+c12*vec2(xScale,yScale));
	vec4 fbColor5= texture2D(fb, texCoordVarying+c13*vec2(0.0,yScale));
	vec4 fbColor6= texture2D(fb, texCoordVarying+c14*vec2(-xScale,yScale));
	vec4 fbColor7= texture2D(fb, texCoordVarying+c15*vec2(-xScale,0.0));
	
	//this works but might not be the best
	
	color=mix(color,fbColor0,c0);
	color=mix(color,fbColor1,c1);
	color=mix(color,fbColor2,c2);
	color=mix(color,fbColor3,c3);
	color=mix(color,fbColor4,c4);
	color=mix(color,fbColor5,c5);
	color=mix(color,fbColor6,c6);
	color=mix(color,fbColor7,c7);
	
	
	//this works kinda glitchieye, too many freezes
	/*
	color+=2.0*(c0*fbColor0+c1*fbColor1+c2*fbColor2+c3*fbColor3+c4*fbColor4+c5*fbColor5+c6*fbColor6+c7*fbColor7);
	color=color/(c0+c1+c2+c3+c4+c5+c6+c7+1.0);
	*/
	
	gl_FragColor = color;
}
