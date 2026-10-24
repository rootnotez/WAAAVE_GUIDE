#version 120

uniform sampler2DRect cam1;

varying vec2 texCoordVarying;

void main()
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;

    
    gl_Position = ftransform();
}
