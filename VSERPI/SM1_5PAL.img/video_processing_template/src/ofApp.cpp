/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#include "ofApp.h"

#include "iostream"


float az = 1.0;
float sx = 0;
float dc = 0;




int fb0_delayamount=0;



//dummy variables for midi control


float c1=0.0;
float c2=0.0;


int width=0;
int height=0;






//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	
	//this clamps the frame rate at 30fps
	//most usb cameras only work at 30 or 60
	//but it might be hard to get anything complex
	//to run at 60fps without framedropping or insconsistent
	//frame rates
	ofSetFrameRate(30);
    
    //this makes the background black
    ofBackground(0);
   
	//run this to hide the mouse cursor on the screen
    ofHideCursor();
	
		
	//so we are drawing a screen size of 720 by 480
	//however there aren't really any usb cameras that
	//work at that resolution so we grab the closest we can
	width=640;
	height=480;
	
	
	//we need to initiate the camera
	cam1.initGrabber(width,height);
	
	//and we need to allocate memory for the framebuffer
	framebuffer0.allocate(width,height);
	
	//this clears the data that we just allocated
	//we don't have to do this for the code to run
	//but if you don't clear the data it will be full
	//of random mishmash that was drawn to your screen in
	//recent history which can be fun to play with
	framebuffer0.begin();
	ofClear(0,0,0,255);
	framebuffer0.end();
	
	
	
	framebuffer1.allocate(width,height);
	
	
	framebuffer1.begin();
	ofClear(0,0,0,255);
	framebuffer1.end();

	
	//this is telling the c++ where to find the 
	//shader files.  the default path it is looking
	//into is bin/data, so this is short for
	//"look into bin/data/shadersES2 and see if you 
	//can find two files named shader_mixer.vert 
	//and shader_mixer.frag
	shader_mixer.load("shadersES2/shader_mixer");
	
	
	
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	
	//we need to update the camera every time to get a new frame
	cam1.update();
	
	
	
}

//--------------------------------------------------------------
void ofApp::draw() {


	//begin midi biz
	
	//we store midi input messages in a buffer and then
	//each time this code runs per frame we look at all the
	//messages in the buffer and assign that information to
	//control variables
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];

		
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {

               
                //midi control change values default range
                //from 0 to 127
                //here you can see two ways to normalize them
                //c1 we will remap to go from 0 to 1
                if(message.control==16){
					
					//c1=(message.value-63.0)/63.0;
                    c1=(message.value)/127.00;
                    
                }
                
                //c2 we will map from -1 to 1 for bipolar controls
                if(message.control==17){
                    c2=(message.value-63.0)/63.0;
                   //   c2=(message.value)/127.00;
                    
                }
         
              
            }
           
			
		}//

	
	}
	
	
	//end midi biz
	
	
	//control attenuation section

	
	
	
	//ok so here is the plan.  try out 1 framebuffer and test out how far back
//in time we can go.  the mix will have the following controls
//hsb for framebuffer 0 and 1
//positions on framebuffer0 ionly 
//some kind of chaotic hue mixing for fb0
//lumakeying on fb0 only
    

    
    
    //----------------------------------------------------------
    //
	
	//so first we will draw everything to a framebuffer
	//so that we have something to ping pong for feedback
	//everything within the framebuffer.begin() and 
	//framebuffer.end() will be drawn to a virtual screen
	//in the graphics memory, it won't be drawn to the
	//actual screen until
	//we call framebuffer.draw
	framebuffer0.begin();
	
	//then we call the shader to being
	//in between shader.begin() and shader.end()
	//all the nitty gritty of what is happening per
	//pixel is happening over in the shader zones
	//so basically all we do are doing on the 
	//c++ side is binding textures and sending some
	//variables over
    shader_mixer.begin();

	//calling .draw() on anything within a texture
	//binds that texture to the gpu
	//the first one you draw is automatically given the
	//name tex0 over on the shader side
	cam1.draw(0,0);
   
    //but if we want to do camera input and do feedback on it
    //we need to also send the previous frame over to the 
    //shaders as a texture, this is the format for doing so
    shader_mixer.setUniformTexture("fb0", framebuffer1.getTexture(),1);


    
    //if we want to have input from our midi devices or
    //from our keyboard we need to send these variables over
    //as well.  setUniform1f is how we send over single float
    //numbers.  we can also call setUniform1i to send over integers
    //or setUniform2f to send over a vector with 2 components
    //and so on and so on
    shader_mixer.setUniform1f("fb0_xdisplace",sx+.01*c1);
    shader_mixer.setUniform1f("fb0_ydisplace",dc+.01*c2);
  
    shader_mixer.end();
	framebuffer0.end();
	
	
	//_----___---------_-_-----_--_-_--_--_
	
	
	//here is where we draw to the screen
	framebuffer0.draw(0,0,720,480);
	

	//_-------------------------------------------
	
	//this is called a ping pong buffer
	//its the fundamental way we do feedback using framebuffers
	//we draw our output screen to an extra framebuffer object
	//and then pass that back into our shader to process it
	framebuffer1.begin(); 
    ofPushMatrix();
	
    framebuffer0.draw(0,0);
	
	ofPopMatrix();
	
    framebuffer1.end();

	
//i use this block of code to print out like useful information for debugging various things and/or just to keep the 
//framerate displayed to make sure i'm not losing any frames while testing out new features.  uncomment the ofDrawBitmap etc etc
//to print the stuff out on screen
   ofSetColor(255);
   string msg="fps="+ofToString(ofGetFrameRate(),2);
  // ofDrawBitmapString(msg,10,10);
}

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//here is how i map controls from the keyboard
    
    //fb0 x displace
    if (key == 's') {sx += .0001;}
    if (key == 'x') {sx -= .0001;}
    
    //fb0 y displace
    if (key == 'd') {dc += .0001;}
    if (key == 'c') {dc -= .0001;}
        
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
