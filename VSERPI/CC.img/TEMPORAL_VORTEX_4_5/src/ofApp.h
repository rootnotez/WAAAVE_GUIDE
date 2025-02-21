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
	
    float time_osc(float frequency,int shape,int osc_id,int x, int y);
    ofVec2f rotation(ofVec2f coord,float theta);
	
	void newMidiMessage(ofxMidiMessage& eventArgs);
	void midiSetup();
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of
	void midibiz();
	
	/*
	void omx_settings();
	void omx_updates();
	ofxOMXCameraSettings settings;
    ofxOMXVideoGrabber videoGrabber;
	*/
	
	void allocateAndDeclareSundries();
	
	void time_displace();

	ofShader shader_blur;
	void inputSetup();
    ofVideoGrabber input1;
    void inputUpdate();
    
    void p_lockSetup();
    void p_lockUpdate();
    
    //noise oscillator
    ofImage osc0_noise_image;
    ofImage osc1_noise_image;
    ofImage perlin_noise(float theta, float resolution, ofImage noise_image);
   
    
};
