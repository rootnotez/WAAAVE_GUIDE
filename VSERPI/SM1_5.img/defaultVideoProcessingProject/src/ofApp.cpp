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

#define MIDI_MAGIC 63.50f
#define CONTROL_THRESHOLD .04f
//0 is picaputre, 1 is usbinput
bool inputswitch=1;
int hdAspectRatioSwitch=0;
float az = 1.0;
float sx = 0;
float dc = 0;

//dummy variables for midi control

float c1=0.0;
float c2=0.0;

int width=0;
int height=0;

const int controlSize=17;

float control1[controlSize];

bool midiActiveFloat[controlSize];

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofBackground(0);
    ofHideCursor();
	
	width=640;
	height=480;
	
	inputSetup();
	
	allocateAndDeclareSundries();
	
	shaderGeometry.load("shadersES2/shaderGeometry");
	midiSetup();
	
	for(int i=0;i<controlSize;i++){
		control1[i]=0.0;
		midiActiveFloat[i]=0;
	}
}
//--------------------------------------------------------------
void ofApp::inputSetup(){
	
	//omx_settings();
	if(inputswitch==0){
		//videoGrabber.setup(settings);
	}

	if(inputswitch==1){
		input1.setDesiredFrameRate(30);
		input1.initGrabber(width,height);
	}
}
//------------------------------------------------------------
void ofApp::allocateAndDeclareSundries(){
	framebuffer0.allocate(width,height);
	framebuffer0.begin();
	ofClear(0,0,0,255);
	framebuffer0.end();
	
	aspectFixFb.allocate(width,height);
	aspectFixFb.begin();
	ofClear(0,0,0,255);
	aspectFixFb.end();
}
//--------------------------------------------------------------
void ofApp::update() {
	inputUpdate();
	midiBiz();
}
//--------------------------------------------------------------
void ofApp::inputUpdate(){
	if(inputswitch==1){
		input1.update();
	}
	if(inputswitch==0){
		//omx_updates();	
	}
	//corner crop and stretch to preserve hd aspect ratio
	if(hdAspectRatioSwitch==1){
		aspectFixFb.begin();
		input1.draw(-106,0,853,480);
		aspectFixFb.end();		
	}
}
//--------------------------------------------------------------
void ofApp::draw() {

	framebuffer0.begin();
	shaderGeometry.begin();
	
	if(inputswitch==0){
		//videoGrabber.draw(0,0);
	}
	if(inputswitch==1){
		if(hdAspectRatioSwitch==0){
			input1.draw(0,0);
		}
		if(hdAspectRatioSwitch==1){
			aspectFixFb.draw(0,0,640,480);
		}
	}
	
	
	shaderGeometry.end();
	framebuffer0.end();
	
	framebuffer0.draw(0,0,720,480);
	
	//i use this block of code to print out like useful information for debugging various things and/or just to keep the 
	//framerate displayed to make sure i'm not losing any frames while testing out new features.  uncomment the ofDrawBitmap etc etc
	//to print the stuff out on screen
    ofSetColor(255);
    string msg="fps="+ofToString(ofGetFrameRate(),2);
    // ofDrawBitmapString(msg,10,10);
  
    /*
    for(int i=0;i<controlSize;i++){
	  cout<<control1[i]<<endl;	
    }
    */
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
	while(midiMessages.size() > 2) {
		midiMessages.erase(midiMessages.begin());
	}
}

//----------------------------------------------------------
void ofApp::midiSetup(){
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
//----------------------------------------------------------
void ofApp::midiBiz(){
                
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
	
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                
                if(message.control>15 && message.control<24){
					if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-control1[message.control-16])<CONTROL_THRESHOLD){
							midiActiveFloat[message.control-16]=TRUE;
					}
					if(midiActiveFloat[message.control-16]==1){
						control1[message.control-16]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
					}	
                }
                
                if(message.control>119 && message.control<128){
					if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-control1[message.control-120+8])<CONTROL_THRESHOLD){
							midiActiveFloat[message.control-120+8]=TRUE;
					}
					if(midiActiveFloat[message.control-120+8]==1){
						control1[message.control-120+8]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    }
                }
                if(message.control==58){
					for(int i=0;i<controlSize;i++){
						control1[i]=0.0;
						midiActiveFloat[i]=0;
					}
				}
				if(message.control==62){					
                    if(message.value==127){
                         hdAspectRatioSwitch=1;
                    }                    
                    if(message.value==0){
						hdAspectRatioSwitch=0;
                    }
                }
            }
		}
	}	
}

//----------------------------------------------------------

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

/*
//__------------------------------------------------------------
void ofApp::omx_settings(){
	
	settings.sensorWidth = 640;
    settings.sensorHeight = 480;
    settings.framerate = 30;
    settings.enableTexture = true;
    settings.sensorMode=7;
    
    settings.flickerCancellation=true;
    settings.frameStabilization=true;
    
    settings.whiteBalance ="Off";
    settings.exposurePreset ="Off";
    settings.whiteBalanceGainR = 1.0;
    settings.whiteBalanceGainB = 1.0;
	
}
//------------------------------------------------------------
void ofApp::omx_updates(){
	
		videoGrabber.setSharpness(50);
		videoGrabber.setBrightness(50);
		videoGrabber.setContrast(50);
		videoGrabber.setSaturation(-100);
	
}
*/
