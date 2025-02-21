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

#define TAU 6.283185307f

#define MIDI_MAGIC 63.0f

#define CONTROL_THRESHOLD .025f

//0 is picaputre, 1 is usbinput
bool inputswitch=1;
int hdAspectRatioSwitch=0;

bool feedbackOnOffSwitch=0;
float az = 1.0;
float sx = 0;
float dc = 0;

int fb0_delayamount=0;

//dummy variables for midi control

float c1=0.0;
float c2=0.0;

int width=0;
int height=0;

const int controlSize=17;

float control1[controlSize];
string control1Names[controlSize];
float control1Coefficient[controlSize];
float control1CoefficientDry[controlSize];
float control1Output[controlSize];

bool control1MidiActive[controlSize];

bool toroidSwitch=0;
bool mirrorSwitch=0;

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
		control1Names[i]="control1_"+ofToString(i);	
		control1MidiActive[i]=0;
	}
	
	control1Coefficient[0]=.2;
	control1Coefficient[1]=.2;
	control1Coefficient[2]=.2;
	control1Coefficient[3]=.2;
	
	control1Coefficient[4]=.1;
	control1Coefficient[5]=.1;
	control1Coefficient[6]=1;
	control1Coefficient[7]=1;
	
	control1Coefficient[8]=.1;
	control1Coefficient[9]=.1;
	control1Coefficient[10]=.1;
	
	control1Coefficient[11]=TAU;
	control1Coefficient[12]=TAU;
	control1Coefficient[13]=TAU;
	control1Coefficient[14]=24.0;
	control1Coefficient[15]=1.0;
	
	control1CoefficientDry[0]=2;
	control1CoefficientDry[1]=2;
	control1CoefficientDry[2]=2;
	control1CoefficientDry[3]=2;
	
	control1CoefficientDry[4]=1;
	control1CoefficientDry[5]=1;
	control1CoefficientDry[6]=1;
	control1CoefficientDry[7]=1;
	
	control1CoefficientDry[8]=1;
	control1CoefficientDry[9]=1;
	control1CoefficientDry[10]=1;
	
	control1CoefficientDry[11]=TAU;
	control1CoefficientDry[12]=TAU;
	control1CoefficientDry[13]=TAU;
	control1CoefficientDry[14]=24.0;
	control1CoefficientDry[15]=1.0;
	
	
	ofNoFill();
	
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
//--------------------------------------------------------------
void ofApp::allocateAndDeclareSundries(){
	framebuffer0.allocate(width,height);
	framebuffer0.begin();
	ofClear(0,0,0,255);
	framebuffer0.end();
	
	framebuffer1.allocate(width,height);
	framebuffer1.begin();
	ofClear(0,0,0,255);
	framebuffer1.end();
	
	framebuffer2.allocate(width,height);
	framebuffer2.begin();
	ofClear(0,0,0,255);
	framebuffer2.end();
	
	aspectFixFb.allocate(width,height);
	aspectFixFb.begin();
	ofClear(0,0,0,255);
	aspectFixFb.end();
}
//--------------------------------------------------------------
void ofApp::update() {
	inputUpdate();
	midiBiz();
	
	//add coefficients
	for(int i=0;i<controlSize;i++){
		if(feedbackOnOffSwitch==1){
			control1Output[i]=control1[i]*control1Coefficient[i];
		}
		if(feedbackOnOffSwitch==0){
			control1Output[i]=control1[i]*control1CoefficientDry[i];
		}	
	}
	
	//something weird with spiral amount...
	control1Output[4]=control1Coefficient[4]*(.00001f+1.0f/control1Coefficient[4]-control1[4]);
	control1Output[15]=1.0-control1[15];
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

	//rotations
	//framebuffer1.begin();
	
	//framebuffer1.end();

	framebuffer2.begin();
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	ofRotateXRad(control1Output[11]);
	ofRotateYRad(control1Output[12]);
	ofRotateZRad(control1Output[13]);
	if(feedbackOnOffSwitch==1){
		framebuffer0.draw(-ofGetWidth()/2,-ofGetHeight()/2);
		ofPushMatrix();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRotateZRad(ofGetElapsedTimef()*.91);
		ofSetColor(127+127*sin(ofGetElapsedTimef()*1.31),127+sin(ofGetElapsedTimef()*1.13),127-sin(ofGetElapsedTimef()*.91));
		ofDrawRectangle(0,0,ofGetHeight()/6,ofGetHeight()/6);
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofPopMatrix();	
	}	
	if(feedbackOnOffSwitch==0){
		ofClear(0,0,0,255);
		if(inputswitch==0){
			//videoGrabber.draw(ofGetWidth()/2,ofGetHeight()/2);
		}
		if(inputswitch==1){
			if(hdAspectRatioSwitch==0){
				input1.draw(-ofGetWidth()/2,-ofGetHeight()/2);
			}
			if(hdAspectRatioSwitch==1){
				aspectFixFb.draw(-ofGetWidth()/2,-ofGetHeight()/2,640,480);
			}
		}
	}
	ofPopMatrix();
	framebuffer2.end();
	
	
	framebuffer0.begin();
	ofClear(0,0,0,255);
	shaderGeometry.begin();
	
	//ofSetRectMode(OF_RECTMODE_CORNER);
	
	framebuffer2.draw(0,0);
	for(int i=0;i<controlSize;i++){
		shaderGeometry.setUniform1f(control1Names[i],control1Output[i]);
	}
	
	//booleans
	shaderGeometry.setUniform1i("toroidSwitch",toroidSwitch);
	shaderGeometry.setUniform1i("mirrorSwitch",mirrorSwitch);
	
	shaderGeometry.end();
	
	framebuffer0.end();
	
	framebuffer0.draw(0,0,720,480);
	
	
	
	
	
	framebuffer1.begin();
	ofClear(0,0,0,255);
	framebuffer1.end();
	
	
	//i use this block of code to print out like useful information for debugging various things and/or just to keep the 
	//framerate displayed to make sure i'm not losing any frames while testing out new features.  uncomment the ofDrawBitmap etc etc
	//to print the stuff out on screen
    ofSetColor(255);
    string msg="fps="+ofToString(ofGetFrameRate(),2);
    // ofDrawBitmapString(msg,10,10);
  
   /*
   for(int i=0;i<controlSize;i++){
	 cout<<control1Names[i]<<" = "<<control1[i]<<endl;	
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
	while(midiMessages.size() > maxMessages) {
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
                
                
                //add midi latching code here "control1MidiActive"
                if(message.control>15 && message.control<24){
                    control1[message.control-16]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    //cout << "message.control "<<message.control-16<< endl;
                    //cout << "message.value"<< message.value<< endl;
                }
                
                if(message.control>119 && message.control<128){
                    control1[message.control-120+8]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    //cout << "message.control "<<message.control-120+8<< endl;
                }
                
                
                if(message.control==20){
					control1[4]=message.value/127.0f;	
				}
                
                //some controls need to be unipolar
                if(message.control==126){
					control1[14]=message.value/127.0f;	
				}
				
				if(message.control==127){
					control1[15]=message.value/127.0f;	
				}
    
				//booleans
				//toroid
				if(message.control==43){
					if(message.value==127){
						toroidSwitch=1;
					}
					if(message.value==0){
						toroidSwitch=0;
					}
				}
				//miror
				if(message.control==44){
					if(message.value==127){
						mirrorSwitch=1;
					}
					if(message.value==0){
						mirrorSwitch=0;
					}
				}
				//hd aspect
				if(message.control==62){					
                    if(message.value==127){
                         hdAspectRatioSwitch=1;
                    }                    
                    if(message.value==0){
						hdAspectRatioSwitch=0;
                    }
                }
                //feedback on off
				if(message.control==61){					
                    if(message.value==127){
                         feedbackOnOffSwitch=1;
                    }                    
                    if(message.value==0){
						feedbackOnOffSwitch=0;
                    }
                }
				//reset switch
				if(message.control==59){
					for(int i=0;i<controlSize;i++){
						control1[i]=0.0;
					}
				}
              
            }
            else if(message.status == MIDI_PITCH_BEND) {/*text << "\tval: " << message.value;*/}
			else { /*text << "\tpitch: " << message.pitch;*/ }
		}
	}
	
	//midiMessages.clear();
		
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

