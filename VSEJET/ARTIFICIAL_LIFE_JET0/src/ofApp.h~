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
	
	void cameraSetup(int w, int h);
	void cameraUpdate();

	//personal procedures
	void allocateFbo(int w, int h);//declare and allocate
	void clearFbo();//clear all fbo
	
	void p_lockClear();
	void p_lockUpdate();
	
	void midiSetup();
	void midibiz();
	
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of
	
	
	
	
	ofShader shader_mixer;
	ofShader shaderSharpen;
    
    
    ofFbo framebuffer0;
    ofFbo dry_framebuffer;
    ofFbo sharpenFramebuffer;
    
    
    ofVideoGrabber cam1;
    
};
