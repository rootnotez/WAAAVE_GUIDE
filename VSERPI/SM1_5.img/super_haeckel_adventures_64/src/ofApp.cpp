



#include "ofApp.h"


#include <iostream>

float ff=1.01;
float xw=1.01;
float yw=1.01;
float jj=1.01;
float kk=1.01;
float ll=1;
float tt=1;





float c1=0.0;
float c2=0.0;
float c3=0.0;
float c4=0.0;
float c5=0.0;
float c6=0.0;
float c7=0.0;
float c8=0.0;
float c9=0.0;
float c10=0.0;
float c11=0.0;
float c12=0.0;
float c13=0.0;
float c14=0.0;
float c15=.0;
float c16=.0;


//keyboard controls
//probbly shift all of these to a gui
float ss=1;
float dd=1;

float gg=1;
float hh=0;

float ee=1;
float pp=1;







float theta=0;





ofPolyline superformula;


float a=1.0;
float b=1.0;
float m1=1.0;
float m2=1.0;
float n1=1.0;
float n2=1.0;
float n3=1.0;

float theta_m1;
float theta_m2;
float theta_n1;
float theta_n2;


//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetVerticalSync(true);
	ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
    /**MIDIBIX***/
    
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
    
    /*******/
    
    ofHideCursor();
   
    
    
    

}

//--------------------------------------------------------------
void ofApp::update() {
    midibiz();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
  
    ofBackground(0);
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofColor color;
    //color.setHsb(255*(c3),,1.0);
    
    ofSetColor(255);
    
    
    
    
    //map some parameters
    
    /*
    theta_m1+=.01*c5;
    theta_m2+=.01*c6;
    theta_n1+=.01*c7;
    theta_n2+=.01*c8;
    
    m1=10*(1.0+c9+c13*(sin(theta_m1)));
    m2=10*(1.0+c10+c14*(sin(theta_m2)));
    
    n1=10*(c11+c15*(sin(theta_n1)));
    n2=10*(c12+c16*(sin(theta_n2)));
    
    n3=.1+(c2*2);
    */
    
    theta_m1+=.005*c5;
    theta_m2+=.005*c6;
    theta_n1+=.005*c7;
    theta_n2+=.005*c8;
        
        
    for(float i=0;i<15;i++){
        float r=ofGetWidth()/8.0*(c1+.05)+i*20*c4;
        
        
        
       
        float ii=i*c3*.1;
        m1=10*(1.0+c9+c13*(sin(theta_m1))+ii);
        m2=10*(1.0+c10+c14*(sin(theta_m2))+ii);
        
        n1=10*(c11+c15*(sin(theta_n1))+ii);
        n2=10*(c12+c16*(sin(theta_n2))+ii);
        
        n3=.1+(c2*2);

        
        for(float t=0.0; t<=6.3;t+=.05){
        
            float superf=pow(pow(abs(cos(m1*t/4)/(a)),n1)+pow(abs(sin(m2*t/4)/b),n2) , .1*n3);
            float x=r*cos(t)*superf;
            float y=r*sin(t)*superf;
        
            //ofDrawRectangle(x,y,10,10);
        
        
            //superformula.lineTo(x,y);
            superformula.curveTo(x,y);
            //path_superf.curveTo(x,y);
        }//endtfor
        superformula.close();
        superformula.draw();
        
        superformula.clear();
    }//endifor
   
    
    
    ofPopMatrix();
	
    
    
    
    
    
   
    
    




/********endaudiodrawbiz****/
   
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
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    
    
   
    //if(key=='q'){sw1==0;}
    
    if(key=='s'){ss+=0.001;}
    if(key=='x'){ss-=0.001;}
    
    if(key=='d'){dd+=0.01;}
    if(key=='c'){dd-=0.01;}
    
    if(key=='f'){ff+=0.1;}
    if(key=='v'){ff-=0.1;}
    
    if(key=='g'){xw+=0.01;}
    if(key=='b'){xw-=0.01;}
    if(key=='h'){yw+=0.01;}
    if(key=='n'){yw-=0.01;}
    
    
    if(key=='j'){jj+=0.1;}
    if(key=='m'){jj-=0.1;}
    if(key=='k'){kk+=0.1;}
    if(key==','){kk-=0.1;}
    
    if(key=='l'){ll+=0.01;}
    if(key=='.'){ll-=0.01;}
    
    if(key=='t'){tt+=0.01;}
    if(key=='y'){tt-=0.01;}
    
    if(key=='e'){ee+=0.1;}
    if(key=='r'){ee-=0.1;}
    
    
    
    
    
   
}
//-------------------------------
void ofApp::midibiz(){

    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        
        ofxMidiMessage &message = midiMessages[i];
        

        //cout << "envcount="<< envcount<< endl;
        
        if(message.status < MIDI_SYSEX) {
            //text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                //  cout << "message.control"<< message.control<< endl;
                //  cout << "message.value"<< message.value<< endl;
                
                
                /*
                 if(message.control==20){
                 c1=(message.value-63.0)/63.0;
                 //c1=(message.value)/127.0;
                 
                 }
                 
                 if(message.control==21){
                 c2=(message.value-63.0)/63.0;
                 
                 //  c2=(message.value)/127.0;
                 
                 }
                 
                 if(message.control==22){
                 c3=(message.value-63.0)/63.00;
                 
                 }
                 
                 if(message.control==23){
                 c4=(message.value-63)/63.00;
                 
                 }
                 
                 if(message.control==24){
                 c5=(message.value)/127.00;
                 
                 }
                 if(message.control==25){
                 c6=(message.value)/127.0;
                 
                 }
                 
                 
                 if(message.control==26){
                 c7=(message.value-63.0)/63.0;
                 
                 }
                 if(message.control==27){
                 c8=(message.value-63.0)/63.0;
                 
                 }
                 */
                
                //nanokontrol2 controls
                if(message.control==16){
                    //  c1=(message.value-63.0)/63.0;
                    c1=(message.value)/127.00;
                    
                }
                
                
                if(message.control==17){
                     c2=(message.value-63.0)/63.0;
                    //c2=(message.value)/127.00;
                    
                }
                
                
                if(message.control==18){
                    c3=(message.value-63.0)/63.00;
                    //  c3=(message.value)/127.00;
                }
                
                
                if(message.control==19){
                    c4=(message.value-63.0)/63.00;
                    // c4=(message.value)/127.00;
                    
                }
                
                
                if(message.control==20){
                    //c5=(message.value-63.0)/63.00;
                      c5=(message.value)/127.00;
                    
                }
                
                
                if(message.control==21){
                    //c6=(message.value-63.0)/63.0;
                     c6=(message.value)/127.00;
                }
                
                
                if(message.control==22){
                   // c7=(message.value-63.0)/63.0;
                       c7=(message.value)/127.00;
                }
                
                
                if(message.control==23){
                    // c8=(message.value-63.0)/63.00;
                    c8=(message.value)/127.0;
                    
                }
                
                if(message.control==120){
                    c9=(message.value-63.0)/63.0;
                    //c9=(message.value)/127.00;
                    
                }
                
                if(message.control==121){
                    c10=(message.value-63.0)/63.0;
                    //c10=(message.value)/127.00;
                    
                }
                
                if(message.control==122){
                    c11=(message.value-63.0)/63.00;
                    //c11=(message.value)/127.00;
                }
                
                
                if(message.control==123){
                     c12=(message.value-63.0)/63.00;
                    //c12=(message.value)/127.00;
                    
                }
                
                if(message.control==124){
                    //c13=(message.value-63.0)/63.00;
                    c13=(message.value)/127.00;
                    
                }
                
                if(message.control==125){
                    //c14=(message.value-63.0)/63.0;
                    c14=(message.value)/127.00;
                }
                
                if(message.control==126){
                    //c15=(message.value-63.0)/63.0;
                    c15=(message.value)/127.00;
                }
                
                if(message.control==127){
                    //c16=(message.value-63.0)/63.00;
                    c16=(message.value)/127.0;
                    
                }
                
                
                
                //text << "\tctl: " << message.control;
                //ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                //	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
            }
            
            
            //text << " "; // pad for delta print
        }//
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

