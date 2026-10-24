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
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
//#include "ofxOMXVideoGrabber.h"

class ofApp : public ofBaseApp, public ofxMidiListener {
	
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	/*
	void omx_settings();
	void omx_updates();
	ofxOMXCameraSettings settings;
    ofxOMXVideoGrabber videoGrabber;
	*/
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
