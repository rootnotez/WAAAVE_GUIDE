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
	
	void midiSetup();
	void midibiz();
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of
	
	ofShader shader_osc0;
    ofShader shader_osc1;
    
    //thes buffers we store the oscs
    void fbDeclareAndAllocate();
    void fbUpdate();
    ofFbo fb_osc0;
    ofFbo fb_osc1;
    ofFbo aspect_fix_fbo;
    
    //these are for pingpong
    ofFbo fb_osc0_pp;
    ofFbo fb_osc1_pp;
	
	ofVideoGrabber cam1;
	
	void inputSetup();
	void inputUpdate();
	
	void pLockInitialize();
	void pLockUpdate();
    
};
