#version 460

in vec2 texCoordVarying;

out vec4 outputColor;

uniform sampler2DRect tex0;

uniform float blur_amount;



//lets try out some kind of upscaling here, or at the very least blur and filter
void main()
{
	vec4 color=texture(tex0, texCoordVarying);
	//old temporal vortex blur shader controls
	/*
	//float x=.0016;
	//float y=.0022;
	
	float x=.0032;
	float y=.0044;
	
	vec4 color=texture2D(tex0, texCoordVarying)
				+texture2D(tex0, texCoordVarying+vec2(x,y))
				+texture2D(tex0, texCoordVarying+vec2(x,-y))
				+texture2D(tex0, texCoordVarying+vec2(-x,y))
				+texture2D(tex0, texCoordVarying+vec2(-x,-y));
	color.rgb=color.rgb*.18;
	
	gl_FragColor = mix(texture2D(tex0, texCoordVarying),color,blur_amount);
	
	*/
	
	
	//seems like somethings up with texCoordVaryingX and Y ...
	//color = vec4(texCoordVarying.x/1280.0,1.0,texCoordVarying.y/720.0,1.0);
	
	
	outputColor=color;
}
