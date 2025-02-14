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

//0 is sd aspect ratio
//use definitely with all of the VSERPI devices 
//and anything else doing like 480i/p over hdmi
//1 is corner cropping to fill the screen-fix corner cropping to center
int hdAspectRatioSwitch=0;
ofFbo aspect_fix_fbo;

float az = 1.0;
float sx = 0;
float dc = 0;

//dummy variables for midi control

int width=0;
int height=0;

const int controlSize=17;

float control0[controlSize];
float control1[controlSize];
float control2[controlSize];
float control3[controlSize];
string control0Names[controlSize];
string control1Names[controlSize];
string control2Names[controlSize];
string control3Names[controlSize];
bool midiActiveFloat0[controlSize];
bool midiActiveFloat1[controlSize];
bool midiActiveFloat2[controlSize];
bool midiActiveFloat3[controlSize];

const int lfoSize=9;
float hueLfoOutput[lfoSize];
float hueLfoRate[lfoSize];
float brightLfoOutput[lfoSize];
float brightLfoRate[lfoSize];

//0 is hue saturation
//1 is bright saturation
//2 is hue lfos
//3 is bright lfos
int controlSwitch=0;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofBackground(0);
    ofHideCursor();
	width=1280;
	height=720;
	inputSetup();
	allocateAndDeclareSundries();
	shaderColorize.load("shadersGL4/shader_colorize");
	midiSetup();
	controlSetup();
}
//--------------------------------------------------------------
void ofApp::update() {
	inputUpdate();
	midiBiz();
	lfoUpdate();
	//cout<<"hueLfoOutput[0] = "<<hueLfoOutput[0]<<endl;
}
//--------------------------------------------------------------
void ofApp::draw() {

	framebuffer0.begin();
	shaderColorize.begin();	
	
	aspect_fix_fbo.draw(0,0);
	
	for(int i=0;i<controlSize;i++){
		shaderColorize.setUniform1f(control0Names[i],control0[i]);
		//cout<<control0Names[i]<<"  "<<control0[i]<<endl;
		if(i>7){
			shaderColorize.setUniform1f(control1Names[i],2.0f*control1[i]);
		}
		if(i<8){
			shaderColorize.setUniform1f("hueLfo"+ofToString(i),hueLfoOutput[i]);
			shaderColorize.setUniform1f("brightLfo"+ofToString(i),2.0f*brightLfoOutput[i]);
		}
	}
	
	shaderColorize.end();
	framebuffer0.end();
	
	framebuffer0.draw(0,0,1280,720);
	
	//i use this block of code to print out like useful information for debugging various things and/or just to keep the 
	//framerate displayed to make sure i'm not losing any frames while testing out new features.  uncomment the ofDrawBitmap etc etc
	//to print the stuff out on screen
    ofSetColor(255);
    string msg="fps="+ofToString(ofGetFrameRate(),2);
    // ofDrawBitmapString(msg,10,10);
  
    /*
    for(int i=0;i<controlSize;i++){
	  cout<<control0[i]<<endl;	
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
	midiIn.openPort(0);
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
//---------------------------------------------------------
void ofApp::clearMidiActiveFloat0(){
	for(int i=0;i<controlSize;i++){
		midiActiveFloat0[i]=0;
	}
}
//---------------------------------------------------------
void ofApp::clearMidiActiveFloat1(){
	for(int i=0;i<controlSize;i++){
		midiActiveFloat1[i]=0;
	}
}
//---------------------------------------------------------
void ofApp::clearMidiActiveFloat2(){
	for(int i=0;i<controlSize;i++){
		midiActiveFloat2[i]=0;
	}
}
//---------------------------------------------------------
void ofApp::clearMidiActiveFloat3(){
	for(int i=0;i<controlSize;i++){
		midiActiveFloat3[i]=0;
	}
}
//-------------------------------------------------------
float ofApp::oscillator(float rate,float amp){
	//unipolar sine wave
	//return amp*(1.0f+sin(rate))*.5;
	//unipolar saw
	//return amp*( fmod(rate/6.18f,1.0) );
	//bipolar saw
	//return amp*(ofMap(fmod(rate/6.18f,1.0),0.0,1.0,-1.0,1.0));
	//unipolar triangle
	return amp*abs((ofMap(fmod(rate/6.18f,1.0),0.0,1.0,-1.0,1.0)));
}
//--------------------------------------------------------
void ofApp::lfoUpdate(){
	/** try to fix the way the lfo spazzes out when rate is being changed**/
	//HUELFO
	float lag=.5+sx;
	for(int i=0;i<lfoSize;i++){
		hueLfoRate[i]=lag*(3.0f*ofGetElapsedTimef()*control2[i])+(1.0f-lag)*hueLfoRate[i];
		hueLfoOutput[i]=lag*oscillator(hueLfoRate[i],control2[i+8])+(1.0f-lag)*hueLfoOutput[i];
		
		brightLfoRate[i]=lag*(3.0f*ofGetElapsedTimef()*control3[i])+(1.0f-lag)*brightLfoRate[i];
		brightLfoOutput[i]=lag*oscillator(brightLfoRate[i],control3[i+8])+(1.0f-lag)*brightLfoOutput[i];
		//cout<<"brightLfoOutput["<<i<<"] = "<<brightLfoOutput[i]<<endl;
	}
}
//----------------------------------------------------------
void ofApp::midiBiz(){
                
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
	
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
				
				if(message.control==43){
					if(message.value==127){
						controlSwitch=1;
						clearMidiActiveFloat0();
						clearMidiActiveFloat2();
						clearMidiActiveFloat3();
					}
					if(message.value==0){
						controlSwitch=0;
						clearMidiActiveFloat1();
					}
				}
				if(message.control==44){
					if(message.value==127){
						controlSwitch=2;
						clearMidiActiveFloat0();
						clearMidiActiveFloat1();
						clearMidiActiveFloat3();
					}
					if(message.value==0){
						controlSwitch=0;
						clearMidiActiveFloat2();
					}
				}
				if(message.control==42){
					if(message.value==127){
						controlSwitch=3;
						clearMidiActiveFloat0();
						clearMidiActiveFloat1();
						clearMidiActiveFloat2();
					}
					if(message.value==0){
						controlSwitch=0;
						clearMidiActiveFloat3();
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
                if(message.control>15 && message.control<24){
				    if(controlSwitch==0){
						if(abs(message.value/127.0f-control0[message.control-16])<CONTROL_THRESHOLD){
							midiActiveFloat0[message.control-16]=TRUE;
						}
						if(midiActiveFloat0[message.control-16]==1){
							control0[message.control-16]=message.value/127.0f;
						}
					}
					if(controlSwitch==2){
						if(abs(message.value/127.0f-control2[message.control-16])<CONTROL_THRESHOLD){
							midiActiveFloat2[message.control-16]=TRUE;
						}
						if(midiActiveFloat2[message.control-16]==1){
							control2[message.control-16]=message.value/127.0f;
						}
					}
					if(controlSwitch==3){
						if(abs(message.value/127.0f-control3[message.control-16])<CONTROL_THRESHOLD){
							midiActiveFloat3[message.control-16]=TRUE;
						}
						if(midiActiveFloat3[message.control-16]==1){
							control3[message.control-16]=message.value/127.0f;
						}
					}
                }
                if(message.control>119 && message.control<128){
					if(controlSwitch==0){
						if(abs(message.value/127.0f-control0[message.control-120+8])<CONTROL_THRESHOLD){
								midiActiveFloat0[message.control-120+8]=TRUE;
						}
						if(midiActiveFloat0[message.control-120+8]==1){
							control0[message.control-120+8]=message.value/127.0f;
						}
					}
					if(controlSwitch==1){
						if(abs(message.value/127.0f-control1[message.control-120+8])<CONTROL_THRESHOLD){
								midiActiveFloat1[message.control-120+8]=TRUE;
						}
						if(midiActiveFloat1[message.control-120+8]==1){
							control1[message.control-120+8]=message.value/127.0f;
						}
					}
					if(controlSwitch==2){
						if(abs(message.value/127.0f-control2[message.control-120+8])<CONTROL_THRESHOLD){
								midiActiveFloat2[message.control-120+8]=TRUE;
						}
						if(midiActiveFloat2[message.control-120+8]==1){
							control2[message.control-120+8]=message.value/127.0f;
						}
					}
					if(controlSwitch==3){
						if(abs(message.value/127.0f-control3[message.control-120+8])<CONTROL_THRESHOLD){
								midiActiveFloat3[message.control-120+8]=TRUE;
						}
						if(midiActiveFloat3[message.control-120+8]==1){
							control3[message.control-120+8]=message.value/127.0f;
						}
					}
                }
                if(message.control==58){
					for(int i=0;i<controlSize;i++){
						control0[i]=0.0;
						control1[i]=0.0;
						control2[i]=0.0;
						midiActiveFloat0[i]=0;
						midiActiveFloat1[i]=0;
						midiActiveFloat2[i]=0;
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
    if (key == 's') {sx += .01;}//cout<<".25+sx = "<<.25+sx<<endl;}
    if (key == 'x') {sx -= .01;}//cout<<".25+sx = "<<.25+sx<<endl;}
    
    //fb0 y displace
    if (key == 'd') {dc += .0001;}
    if (key == 'c') {dc -= .0001;}
        
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}
//-------------------------------------------------------------
void ofApp::controlSetup(){
	for(int i=0;i<controlSize;i++){
		control0[i]=0.0;
		midiActiveFloat0[i]=0;
		control1[i]=0.0;
		midiActiveFloat1[i]=0;
		control2[i]=0.0;
		midiActiveFloat2[i]=0;
		if(i<8){
			control0Names[i]="saturation"+ofToString(i);
			control2Names[i]="hueLfoAdder"+ofToString(i);
			control3Names[i]="brightLfoAdder"+ofToString(i);
			hueLfoOutput[i]=0;
			hueLfoRate[i]=0;
			brightLfoOutput[i]=0;
			brightLfoRate[i]=0;
		}
		if(i>=8){
			control0Names[i]="hue"+ofToString(i-8);
			control1Names[i]="bright"+ofToString(i-8);
			control2Names[i]="hueLfoAmp"+ofToString(i-8);
			control3Names[i]="brightLfoAmp"+ofToString(i-8);
		}
	}
}
//--------------------------------------------------------------
void ofApp::inputSetup(){

	input1.setDesiredFrameRate(30);
	input1.initGrabber(640,480);
	/*	
	if(hdAspectRatioSwitch==1){
		aspect_fix_fbo.begin();
		input1.draw(0,0,853,480);
		aspect_fix_fbo.end();		
	}
	*/
}
//--------------------------------------------------------------
void ofApp::allocateAndDeclareSundries(){
	framebuffer0.allocate(width,height);
	framebuffer0.begin();
	ofClear(0,0,0,255);
	framebuffer0.end();
	
	aspect_fix_fbo.allocate(width,height);
	aspect_fix_fbo.begin();
	ofClear(0,0,0,255);
	aspect_fix_fbo.end();
}
//--------------------------------------------------------------
void ofApp::inputUpdate(){

	input1.update();

	//corner crop and stretch to preserve hd aspect ratio
	/*
	if(hdAspectRatioSwitch==1){
		aspect_fix_fbo.begin();
		input1.draw(-106,0,853,480);
		aspect_fix_fbo.end();		
	}
	*/
	if(hdAspectRatioSwitch==0){
		aspect_fix_fbo.begin();
			ofPushMatrix();
			ofTranslate(0,-120);
			input1.draw(0,0,1280,960);
			ofPopMatrix();
		aspect_fix_fbo.end();
		
	}
	
	if(hdAspectRatioSwitch==1){
			aspect_fix_fbo.begin();
			input1.draw(0,0,1280,720);
			aspect_fix_fbo.end();		
	}
}

