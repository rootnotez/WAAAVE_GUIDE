#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

#define ROOT_THREE 1.73205080757



class ofApp : public ofBaseApp, public ofxMidiListener {
	
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 2; //< max number of messages to keep track of
	
	void midiSetup();
	void midiBiz();
	
	void controlSetup();
	
	void clearMidiActiveFloat0();
	void clearMidiActiveFloat1();
	void clearMidiActiveFloat2();
	void clearMidiActiveFloat3();
	
	float oscillator(float rate,float amp);
	void lfoUpdate();
	
	void allocateAndDeclareSundries();
	void inputSetup();
	void inputUpdate();
	
	ofShader shaderColorize;
	
    ofFbo framebuffer0;
    
    ofVideoGrabber input1;
    
};
