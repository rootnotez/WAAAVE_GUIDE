#pragma once

#include "ofMain.h"

#define ROOT_THREE 1.73205080757

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
	
	//globals	
	int inputWidth=640;
	int inputHeight=480;

	int outputWidth;
	int outputHeight;

	//video inputs
	void inputSetup();
	void inputUpdate();
	void inputTest();
	ofVideoGrabber input1;

	//framebuffers
	void framebufferSetup();
	ofFbo framebuffer1;
	ofFbo framebuffer2;
	ofFbo framebuffer3;

	//shaders
	ofShader shader1;
	
};
