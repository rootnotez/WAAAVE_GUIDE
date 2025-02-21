#version 120


uniform sampler2DRect tex0;

uniform float fade;

varying vec2 texCoordVarying;

void main()
{
  
    vec4 color =texture2DRect(tex0, texCoordVarying);
    color=color*fade;
    color.r=.1*fract(1000*sin(color.r))*color.r;
    
    if(color.r<.1&&color.g<.1&&color.b<.1){color=vec4(0);}
    gl_FragColor = color;
}
