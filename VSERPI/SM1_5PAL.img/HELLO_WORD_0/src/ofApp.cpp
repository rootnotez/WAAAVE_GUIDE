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
float az = 1.0;
float sx = 0;
float dc = 0;

//dummy variables for midi control

float c1=0.0;
float c2=0.0;

int width=0;
int height=0;

const int controlSize=17;

float control1[controlSize];

bool midiActiveFloat[controlSize];

ofTrueTypeFont myFont;

string globalTestString;
const int margin=16;
const int fontSize=16;
const int arraySize=24;
int arrayPointer=0;
string stringArray[arraySize];

/*idea: we have fixed number of strings in an array that fill the screen 
 * this number of strings is based on the const fontSize
 * each time that we exceed the width of the screen we start over from
 * a new string and increase a pointer.  need to make sure that backspacing
 * also decrements the pointer if we are there
 */

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofBackground(0);
    ofHideCursor();
	
	//width=640;
	//height=480;
	/*
	input1.initGrabber(width,height);
	
	framebuffer0.allocate(width,height);
	framebuffer0.begin();
	ofClear(0,0,0,255);
	framebuffer0.end();
	
	shaderGeometry.load("shadersES2/shaderGeometry");
	* * */
	midiSetup();
	
	for(int i=0;i<controlSize;i++){
		control1[i]=0.0;
		midiActiveFloat[i]=0;
	}
	control1[3]=-1.0;
	//ADD MORE FONTS HERE
	myFont.load("fonts/ocrb10.ttf",fontSize);
	
	for(int i=0;i<arraySize;i++){
		//stringArray[i]="yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy";
		stringArray[i]="";
	}
	
}

//--------------------------------------------------------------
void ofApp::update() {
	//input1.update();
	midiBiz();
}

//--------------------------------------------------------------
void ofApp::draw() {
	string test;
	test="henlo word";
	//ofColor textColor;
	//textColor.fromHsb(control1[0]*255.0f,control1[1]*255.0f,control1[2]*255.0f);
	
	float textRed=127.0f*control1[0]+127.0f;
	float textGreen=127.0f*control1[1]+127.0f;
	float textBlue=127.0f*control1[2]+127.0f;
	float textAlpha=255.0f-255*(.5*(control1[3]+.5));
	ofSetColor(textRed,textGreen,textBlue,textAlpha);
	
	
	//myFont.drawString(globalTestString,myFont.getSize(),myFont.getSize());
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	float xDisplace=ofGetWidth()/2*control1[8];
	float yDisplace=ofGetHeight()/2*control1[9];
	float zDisplace=400.0f*control1[10];
	float rotateX=6.18*control1[11];
	float rotateY=6.18*control1[12];
	float rotateZ=6.18*control1[13];
	ofTranslate(xDisplace,yDisplace,zDisplace);
	ofRotateXRad(rotateX);
	ofRotateYRad(rotateY);
	ofRotateZRad(rotateZ);
	ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
	
	for(int i=0;i<arraySize;i++){
		int yPosition=(i+1)*(myFont.getSize()+margin);
		int xPosition=myFont.getSize()+margin;
		myFont.drawString(stringArray[i],xPosition,yPosition);
	}
	
	ofPopMatrix();
	/*
    ofSetColor(255);
    string msg="fps="+ofToString(ofGetFrameRate(),2);
    // ofDrawBitmapString(msg,10,10);
  
    
    for(int i=0;i<controlSize;i++){
	  cout<<control1[i]<<endl;	
    }
    */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	if(key==8 && stringArray[arrayPointer].size()>1){
		globalTestString=globalTestString.substr(0,globalTestString.size()-1);
		//stringArray[arrayPointer]=stringArray[arrayPointer].substr(0,stringArray[arrayPointer].size()-1);
		stringArray[arrayPointer].erase(stringArray[arrayPointer].size()-1);
		stringArray[arrayPointer].resize(stringArray[arrayPointer].size()-1);
		cout<<stringArray[arrayPointer].size()<<endl;
		//cout<<globalTestString.size()<<endl;
	}
	if(key==8 && stringArray[arrayPointer].size()==0 && arrayPointer>0){
		//cout<<"hey testing string is ==0"<<endl;
		arrayPointer--;
		arrayPointer=ofClamp(arrayPointer,0,arraySize-1);
		
	}
	if(key==8 && stringArray[arrayPointer].size()<0 && arrayPointer<=0){
		arrayPointer=0;
		//cout<<"stop it"<<endl;
	}
	if(key==13){
		arrayPointer++;
		arrayPointer=ofClamp(arrayPointer,0,arraySize-1);
	}
	else{
		/*
		if(myFont.stringWidth(globalTestString)>ofGetWidth()/2-margin){
			globalTestString.append(newLine);
			cout<<"yeah"<<endl;
		}
		* */
		globalTestString.append(1, (char)key);
		stringArray[arrayPointer].append(1, (char)key);
    }    
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
                
                if(message.control>15 && message.control<24){
					if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-control1[message.control-16])<CONTROL_THRESHOLD){
							midiActiveFloat[message.control-16]=TRUE;
					}
					if(midiActiveFloat[message.control-16]==1){
						control1[message.control-16]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
					}
					/*
					cout<<"midiActiveFloat[0] = "<<midiActiveFloat[0]<<endl;
					cout<<"message.value = "<<message.value<<endl;
					cout<<"control1[0] = ="<<control1[0]<<endl;
					*/ 	
                }
                
                if(message.control>119 && message.control<128){
					if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-control1[message.control-120+8])<CONTROL_THRESHOLD){
							midiActiveFloat[message.control-120+8]=TRUE;
					}
					if(midiActiveFloat[message.control-120+8]==1){
						control1[message.control-120+8]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    }
                }
                if(message.control==58){
					for(int i=0;i<controlSize;i++){
						control1[i]=0.0;
						midiActiveFloat[i]=0;
					}
				}
            }
		}
	}	
}

//----------------------------------------------------------



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------

