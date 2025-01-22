#include "ofApp.h"
//globals


//to do next 8-16-23
//shader defaults

const int pastFramesSize=120;
ofFbo pastFrames1[pastFramesSize];
ofFbo pastFrames2[pastFramesSize];
int pastFramesOffset=0;
unsigned int pastFramesCount=0;


ofTexture dummyTex;
//testing variables
int testSwitch1=1;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);	
	ofBackground(0);
	ofHideCursor();
	
	outputWidth=1280;
	outputHeight=720;	

	inputSetup();
	
	framebufferSetup();
	
	//keep this last in setup for easier debugging
	shader1.load("shadersGL4/shader1");
	
	dummyTex.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);


}

//--------------------------------------------------------------
void ofApp::update(){

	inputUpdate();

}


//--------------------------------------------------------------
void ofApp::draw(){

	framebuffer1.begin();
	shader1.begin();
	
	dummyTex.draw(0,0);
	
	shader1.setUniformTexture("input1Tex", input1.getTexture(), 1);
	
	shader1.setUniform1f("width",ofGetWidth());
	shader1.setUniform1f("height",ofGetHeight());
	shader1.end();
	
	inputTest();
	framebuffer1.end();

	framebuffer1.draw(0,0);

	//inputTest();
	//clear the framebuffers
	framebuffer1.begin();
	ofClear(0,0,0,255);
	framebuffer1.end();	

}
//--------------------------------------------------------------
void ofApp::inputSetup(){
	//i guess we might just be 
	//stuck at sd inputs!
	//lets just get to work and
	//if we get the chance to fix this later
	//then do so
	input1.listDevices();
	//input1.setVerbose(true);
	input1.setDeviceID(0);
	input1.setDesiredFrameRate(30);
	//input1.setPixelFormat(OF_PIXELS_NATIVE);
	input1.initGrabber(640,480);
}

//--------------------------------------------------------------
void ofApp::inputUpdate(){
	input1.update();

}


//--------------------------------------------------------------
void ofApp::inputTest(){
	
	if(testSwitch1==1){
		input1.draw(0,0);
	}
	if(testSwitch1==2){
		//input2.draw(0,0);
	}
	
}

//---------------------------------------------------------
void ofApp::framebufferSetup(){
	framebuffer1.allocate(outputWidth,outputHeight);
	framebuffer2.allocate(outputWidth,outputHeight);
	framebuffer3.allocate(outputWidth,outputHeight);

	framebuffer1.begin();
	ofClear(0,0,0,255);
	framebuffer1.end();
	
	framebuffer2.begin();
	ofClear(0,0,0,255);
	framebuffer2.end();
	
	framebuffer3.begin();
	ofClear(0,0,0,255);
	framebuffer3.end();
	
	 for(int i=0;i<pastFramesSize;i++){
        pastFrames1[i].allocate(ofGetWidth(),ofGetHeight());
        pastFrames2[i].allocate(ofGetWidth(),ofGetHeight());
        
        pastFrames1[i].begin();
        ofClear(0,0,0,255);
        pastFrames1[i].end();
        
        pastFrames2[i].begin();
        ofClear(0,0,0,255);
        pastFrames2[i].end();
    }
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='1'){testSwitch1=1;}
	if(key=='2'){testSwitch1=2;}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

