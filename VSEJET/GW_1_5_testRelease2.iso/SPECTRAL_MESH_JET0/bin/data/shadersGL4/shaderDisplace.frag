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

//tha WP biz of declarations
//cam1=external input
uniform sampler2DRect tex0;


void main()
{

	vec4 input1Color = texture(tex0, texCoordVarying);
	
	outputColor = input1Color;



//old shader biz
/*
vec4 color=texture2D(tex0,texCoordVarying);
    float bright =.33*color.r+.5*color.g+.16*color.b;
    
   // color.w=bright;
    
    //greyscale try
    color=b_w_switch*vec4(bright)+(1.0-b_w_switch)*color;
    
     
      color.rgb=invert_switch*(1.0-color.rgb)+(1.0-invert_switch)*color.rgb;   
  
    
    
    //make sure to offer bright switch for this too
    if(luma_switch==0){
		if(bright<luma_key_level){
			color.w=0.0;
			}
    }
    
    if(luma_switch==1){
		if(bright>luma_key_level){
			color.w=0.0;
			}
    }
	
	
	//color.w=bright;
    gl_FragColor =color;

*/

}
