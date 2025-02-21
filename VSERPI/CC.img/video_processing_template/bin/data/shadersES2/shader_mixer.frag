precision highp float;


uniform sampler2D tex0;

uniform sampler2D fb0;






uniform float fb1_mix;

uniform float fb0_xdisplace;
uniform float fb0_ydisplace;


varying vec2 texCoordVarying;



//here is how to write a function
//"vec3" defines what value gets returned, "rgb2hsb" is how
//this function gets called, "in  vec3 c" means it takes in
//a single vec3 as an argument and passes it into a variable
//named c.  
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




//main() is the main function being called per pixel. 
//every bit of code in here is being called simultaneously
//for each pixel on the output screen.  it is important
//when doing real time video processing to figure out
//what operations are best performed in the shader and 
//which operations are best performed outside of the shader
//from a computational standpoint, say we want to have
//sd video resolution at 30fps.  sd video is 720x480 
//(i mean not quite but thats the best way to work with it
//from within the raspberry pi) so thats 345,600 pixels per
//frame, which means per second we have this code running
//10,368,000 times per second.  if you work out what things
//need to happen only once per frame vs the things that need
//to happen on a pixel by pixel basis that means you can
//optimize your code by having an operation only perform 
//30 times per second vs 10,368,000 times per second.  for
//small programs and small resolutions you might not 
//notice much difference but when you are trying out larger
//things and working with multiple textures these things
//tend to add up! 
void main()
{
	//important to note that texCoordVarying here seems to be automatically scaled between 0 and 1
	
	
	//i'm definining a dummy variable that we can put just
	//any color into.  colors have 4 variables (r, g, b, a)
	//which translates to red, green, blue, and alpha
	//rgb translates to how bright the individual rgb liquid
	//crystals/leds/rgb phosphors get drawn to the screen
	//alpha translates to the 'transparancy' of the pixel
	vec4 color=vec4(0,0,0,0);
	
	
	//here i am defining another color and using texture2D
	//to  pull a color out of a texture that has been sent 
	//to the gpu.  in the c++ code you will see that 
	//the camera input was sent to the gpu by the command
	//cam1.draw() within shader.begin() and shader.end()
	//when you do that it automatically gets bound to a 
	//predefined variable named tex0
	//texCoordVarying 
	vec4 cam1_color = texture2D(tex0, texCoordVarying);
	
	
	//uncomment this to see what happens
	//what pow() is doing is 
	//taking the first value in and calculating it
	//to the power of the second exponent
	//so this is taking in the rgba values of the 
	//camera color and squaring each one'
	//you can also feed it like .5 if you want to do
	//fractional powers
	//this is a cheap way to increase/decrease contrast
	//but with some color and saturation glitching possible
	
	//cam1_color =pow(cam1_color,2);
	
	
	//ok i want to do some stuff in hsb now, here
	//is how i get those values to play with
	//cam1_color_hsb is a vector with 3 components 
	//(hue, saturation, brightness)
	//so cam1_color_hsb.x is hue
	//cam1_color_hsb.y is saturation
	//cam1_color_hsb.z is brightness
	//all normalized from 0 to 1
	vec3 cam1_color_hsb= rgb2hsb(vec3(cam1_color.r,cam1_color.g,cam1_color.b));
	
	//ok if you want to invert brightness uncomment this
	//cam1_color_hsb.z=1.0-cam1_color_hsb.z;
	
	//if you want to desaturate everything and have black
	//and white
	//cam1_color_hsb.y=0;
	
	
	//then we have to convert back into rgb before we do anything else
	cam1_color=vec4(vec3(hsb2rgb(vec3(cam1_color_hsb.x,cam1_color_hsb.y,cam1_color_hsb.z))),1.0);
	
	
	
	
	//some notes on coordinates
	//texCoordVarying is variable defined over in the
	//vertex shader that specifies what pixel we are drawing
	//in this version of gl coordinates are scaled from 0 to 1
	//so if our texture we are drawing has resolution of 720x480
	//then for the x coordinate 0 means the far left hand side
	//of the screen, .5 means 360 pixels over right in the 
	//center of the screen and 720 is far right hand
	//for y 0 means the top of the screen, .5 means 240 pixels
	//down from that and 1 means 480 pixels down at the bottom
	//of the screen
	//for doing feedback stuffs its good to have a lot of 
	//control over where you are grabbing pixels from 
	//so i like to define an extra coordinate variable to
	//keep track of all of that
	vec2 fb0_coord=vec2(texCoordVarying.x,texCoordVarying.y);
	
    //lets displace the x and y by the amount that we sent in from
    //the c++ code via the uniform variables fb0_xdisplace and
    //fb0_ydisplace
    fb0_coord=vec2(fb0_coord.x+fb0_xdisplace,fb0_coord.y+fb0_ydisplace);
	
	//then lets get the color data out of the fb0 texture
	vec4 fb0_color = texture2D(fb0, fb0_coord);

	
	//we can either blend the two colors together
	//using mix()
	//the final value is the amount that we mix together
	//mix() expects only values of 0 to 1 for this
	//but it can be fun to experiment with going out of 
	//bounds here with negative values or like going way over
	//this is a general technique i recommend for experimenting
	//seeing how the baked in functions respond to out of 
	//bounds inputs is sort of like trying to to circuit
	//bending on hardware
	color=mix(cam1_color, fb0_color,.5);
	
	
	//and or try to luma key things together
	//remember that cam1_color_hsb.z is the brightness of cam1
	//that we calculated earlier
	
	
	//this means that if the brightness of the
	//camera input is less than .5 we will
	//key in the framebuffer delay
	if(cam1_color_hsb.z<.5)
	{
		color=fb0_color;
	}
	
	
	
	
	
	//gl_FragColor is the color we draw to the screen!
	gl_FragColor = color;
}
