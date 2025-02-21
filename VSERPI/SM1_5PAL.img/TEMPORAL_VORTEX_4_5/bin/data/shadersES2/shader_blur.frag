precision highp float;


uniform sampler2D tex0;


uniform float blur_amount;

varying vec2 texCoordVarying;


void main()
{
	
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
}
