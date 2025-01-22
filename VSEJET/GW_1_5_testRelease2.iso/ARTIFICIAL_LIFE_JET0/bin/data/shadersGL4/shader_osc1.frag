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

//th AL biz of declarations
uniform sampler2DRect tex0;

uniform sampler2DRect cam1;

//uniform sampler2DRect osc1_mod;

uniform float osc1_r_offset;
uniform float osc1_g_offset;
uniform float osc1_b_offset;
uniform float osc1_powmod;

uniform float osc1_rm;
uniform float osc1_pm;
uniform float osc1_rate;
uniform float osc1_frequency;
uniform float osc1_amp;
uniform float osc1_angle;

uniform int osc1_shape;

uniform float osc1_m_rm;
uniform float osc1_m_pm;
uniform float osc1_m_rate;
uniform float osc1_m_frequency;
uniform float osc1_m_amp;
uniform float osc1_m_angle;

uniform int osc1_m_shape;

uniform float width;
uniform float height;

uniform float pm_weight;

uniform float osc1_spiral;
uniform float osc1_rotate;
uniform float osc1_modulation_rotate;

uniform float osc1_m_spiral;
uniform float osc1_m_rotate;
uniform float osc1_m_modulation_rotate;

uniform float osc1_cam1_pm;

uniform int osc1_overflow_switch;

uniform float osc1_cutoff;

uniform float osc1_m_cam1_pm;

uniform float osc1_width;
uniform float osc1_pwm;
uniform float osc1_m_width;
uniform float osc1_m_pwm;

uniform int internal_feedback_switch1;

uniform float qq;

uniform float osc1_feedback_filter;

//lets make everything from 0-1 here for now
float oscillate(float theta,int shape,float width){
    float osc=0.0;
    
      if(shape==0){
        osc=(sin(theta)+1.0)*.5;
        if(width>0){
        	osc=clamp(osc+width,0.0,1.0);
        }
        if(width<0){
        	osc=pow(osc,(1+10.0*abs(width)));
        }
    }
    
    //squarewave..can add a dc offset for pwm too?
    if(shape==1){
        osc=sign(sin(theta)+width);
    }
    
    
    //haha tanwave
    //osc=tan(theta);
    
    //sawtooth??
    if(shape==2){
        osc=fract(theta/6.18);
        if(width>0){
       		osc=clamp(osc+width,0.0,1.0);
        }
        if(width<0){
        	osc=pow(osc,(1+10.0*abs(width)));
        }
    }

    
    return osc;
    
}

vec2 rotate(vec2 coord,float theta){
    vec2 center_coord=vec2(coord.x-640,coord.y-360);
    vec2 rotate_coord=vec2(0.0,0.0);
    float spiral=abs(coord.x+coord.y)/2.0*width;
    coord.x=spiral+coord.x;
    coord.y=spiral+coord.y;
    rotate_coord.x=center_coord.x*cos(theta)-center_coord.y*sin(theta);
    rotate_coord.y=center_coord.x*sin(theta)+center_coord.y*cos(theta);
    
    
    rotate_coord=rotate_coord+vec2(640,360);
    
    return rotate_coord;
    
    
}//endrotate

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
	vec4 color = vec4(0.0,0.0,0.0,1.0);
	//NEW BIZ
	vec2 input1Coords=texCoordVarying;

	vec4 input1Color = texture(cam1, input1Coords+vec2(1.5,1.5));
	vec3 input1Color_hsb=rgb2hsb(input1Color.rgb);
	
	 //new coordinate tests
    vec2 newCoordVarying=texCoordVarying-vec2(0,0);
	
	 vec4 osc_mod_1=texture(tex0,texCoordVarying+vec2(1.5,1.5));
    
    //vec4 input1Color=texture2D(cam1,fract(texCoordVarying+vec2(.005,.005)));
    
    float om1_bright=.299*osc_mod_1.r+.587*osc_mod_1.g+.114*osc_mod_1.b;
    /*
    vec2 axis=rotate(texCoordVarying, osc1_angle);
    
    float osc1_arg=osc1_rate+axis.x*(osc1_frequency+osc1_pm*om1_bright);

    color.rgb=(osc1_amp+osc1_rm*om1_bright)*vec3(oscillate(osc1_arg+,0,0));
    */
    
    
    vec2 m_axis=vec2(0.0,0.0);
    
    //old spiral thing
    //float osc1_spiral_new=osc1_spiral*distance(texCoordVarying, vec2(.5,.5));
    
    //trying a new techniqe for spiral thing try adjusting the .5 .5 part?
    float osc1_spiral_new=2.0*osc1_spiral*distance(newCoordVarying, vec2(640,360));
    
    float osc1_m_spiral_new=osc1_m_spiral*distance(texCoordVarying, vec2(640,360));
    
    vec2 axis=osc1_spiral_new+rotate(texCoordVarying, osc1_angle+osc1_rotate
    +osc1_modulation_rotate*oscillate(
		osc1_m_cam1_pm*input1Color_hsb.z+osc1_m_rate+
		osc1_m_spiral_new+(rotate(texCoordVarying, osc1_m_angle+osc1_m_rotate
		+osc1_m_modulation_rotate*oscillate(
			osc1_rate+rotate(texCoordVarying, osc1_angle).y*(osc1_frequency),osc1_shape,osc1_width)
		).y+.01)*(osc1_m_frequency+.1*osc1_m_pm*oscillate(osc1_rate+rotate(texCoordVarying, osc1_angle+osc1_spiral_new+osc1_rotate).y*(osc1_frequency)+
	osc1_m_cam1_pm*input1Color_hsb.z,osc1_shape,osc1_width)),osc1_m_shape,osc1_m_width));
    
    //+rotate(texCoordVarying, osc1_m_angle+osc1_m_spiral*distance(texCoordVarying, vec(.5,.5))+osc1_m_rotate+osc1_m_modulation_rotate*oscillate(osc1_rate+rotate(texCoordVarying, osc1_angle).x*(osc1_frequency),osc1_shape,0)).x*(osc1_m_frequency),osc1_m_shape,0));
	
	m_axis=osc1_m_spiral_new+rotate(texCoordVarying, osc1_m_angle+osc1_m_rotate
	+osc1_m_modulation_rotate*oscillate(osc1_rate+rotate(texCoordVarying, osc1_angle+osc1_spiral_new+osc1_rotate).y*(osc1_frequency)+
	osc1_m_cam1_pm*input1Color_hsb.z,osc1_shape,osc1_width)
	);
	
    //float osc1_m_arg=osc1_m_rate+(m_axis.x+.01)*(osc1_m_frequency+.1*osc1_m_pm*om1_bright);
    
    //tryin something new with osc1_m pm
    float osc1_m_arg=osc1_m_rate+(m_axis.y+.01)*(osc1_m_frequency);
    
    float osc1_m=osc1_m_amp*oscillate(osc1_m_arg+osc1_m_cam1_pm*input1Color_hsb.z,osc1_m_shape,osc1_m_width);
    
    
    
    
    //try out this new filter thing
   
    
    float clampit=clamp(om1_bright-osc1_cutoff,0.0,1.0);
    
    
    float filtered=om1_bright*(1.0-clampit)+.5*clampit;
    
    //filtered=om1_bright;
    
    
    
    float osc1_arg=osc1_rate+axis.y*(osc1_frequency+osc1_m_pm*osc1_m+osc1_pm*filtered);


	float filtered_rm=om1_bright*om1_bright;
	
	color.rgb=(osc1_amp+osc1_rm*filtered_rm+osc1_m_rm*osc1_m)*vec3(oscillate(osc1_arg+input1Color_hsb.z*osc1_cam1_pm,osc1_shape,osc1_width+osc1_pwm*om1_bright+osc1_m_pwm*osc1_m));
	
	
	if(osc1_overflow_switch==1){
        //color.rgb=2.0*fract(color.rgb*.5);
        
        color.rgb=fract(color.rgb);
    }
    
    if(osc1_overflow_switch==2){
        if(color.r>1.0){
            color.rgb=vec3((1.0-fract(color.r)));
        }
    }
    
    if(osc1_overflow_switch==3){
        if(color.r>1.0){
            color.rgb=vec3(fract(color.r-tan(color.r*.25+osc1_arg)));
        }
    }
	
	
	//3 band colorizer
	
	vec3 colorHsb=rgb2hsb(color.rgb);	
	
	float bright=colorHsb.z;
	
	//maybe try some adjusted brightness curves
	bright=pow(bright,2.0);
	
	//colorize
	vec3 colorHsbBand1=vec3(osc1_r_offset,osc1_powmod,colorHsb.z);
	vec3 colorHsbBand2=vec3(osc1_g_offset,osc1_powmod,colorHsb.z);
	vec3 colorHsbBand3=vec3(osc1_b_offset,osc1_powmod,colorHsb.z);
	
	//convert back to rgb for soft keying
	vec4 colorRgbBand1=vec4(hsb2rgb(colorHsbBand1),1.0);
	vec4 colorRgbBand2=vec4(hsb2rgb(colorHsbBand2),1.0);
	vec4 colorRgbBand3=vec4(hsb2rgb(colorHsbBand3),1.0);
	
	if(bright<.5){
		color=mix(colorRgbBand1,colorRgbBand2,bright*2.0);
	}
	
	if(bright>.5){
		color=mix(colorRgbBand2,colorRgbBand3,(bright-.5)*2.0);	
	}
	//color.rgb=hsb2rgb(colorHsb);	
		
	//color.rgb=pow(color.rgb,vec3(1.0+osc1_powmod));
	
	
	if(internal_feedback_switch1==1){
		input1Color_hsb.z=input1Color_hsb.z*(1.0+.25*osc1_feedback_filter);
		input1Color_hsb.y=input1Color_hsb.y*(1.0+.25*osc1_feedback_filter);
		input1Color.rgb=hsb2rgb(input1Color_hsb);
		color.rgb=mix(color.rgb,input1Color.rgb,osc1_feedback_filter);
	}
	
	
	
	
	
	
	outputColor=color;
	//outputColor=input1Color;
}
