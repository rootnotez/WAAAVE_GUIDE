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
#include "ofxImGui.h"

#define PARAMETER_ARRAY_LENGTH 16

class GuiApp: public ofBaseApp, public ofxMidiListener {
public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	
	
	/**midi!**/
	void midibiz();
	void midiSetup();
	void newMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10;

	/**gui**/
	ofxImGui::Gui gui;

	/*Arrays & midi 2 gui*/
	void allArrayClear();
	void midi2Gui(bool midiActive[], float params[], bool midiSwitch);
	
	//reset
	void resetAll();
	void allButtonsClear();

	
	
	
	//ch1 parameters
	int ch1InputSelect=0; //0 is input1, 1 is input2

	
	//ch1 midi syncing & parameter bizness
	bool ch1AdjustMidiGui=0;
	bool ch1AdjustReset=0;
	float ch1Adjust[PARAMETER_ARRAY_LENGTH];
	bool ch1AdjustMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool ch1HMirror=0;

};

