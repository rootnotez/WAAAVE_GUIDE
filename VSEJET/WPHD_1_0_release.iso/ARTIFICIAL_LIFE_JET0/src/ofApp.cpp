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

//0 is picaputre, 1 is usbinput
bool inputswitch=1;

bool internal_feedback_switch0=0;
bool internal_feedback_switch1=0;

int hdmi_aspect_ratio_switch=0;

bool osc0_mod_switch=0;
int osc0_axis_switch=0;

int osc0_shape=0;
int osc0_m_shape=0;

float osc0_rotate=0;
float osc0_rate=.1;

float osc0_m_rotate=0;
float osc0_m_rate=.1;

float osc1_rotate=0;
float osc1_rate=.1;

float osc1_m_rotate=0;
float osc1_m_rate=.1;

bool osc1_mod_switch=0;
int osc1_axis_switch=0;

int osc1_shape=0;
int osc1_m_shape=0;

bool draw_switch=0;

int overflow_switch=0;

int width=1280;
int height=720;


int osc_m_rate_switch=0;

int osc0_pm_rm_switch=0;
int osc1_pm_rm_switch=0;

bool osc_cam_pm_switch=0;

int osc_rgbp_switch=0;
//p_lock biz
//maximum total size of the plock array
const int p_lock_size=240;

bool p_lock_record_switch=0;

bool p_lock_erase=0;

//maximum number of p_locks available...maybe there can be one for every knob
//for whatever wacky reason the last member of this array of arrays has a glitch
//so i guess just make an extra array and forget about it for now
const int p_lock_number=61;

//so how we will organize the p_locks is in multidimensional arrays
//to access the data at timestep x for p_lock 2 (remember counting from 0) we use p_lock[2][x]
float p_lock[p_lock_number][p_lock_size];


//smoothing parameters(i think for all of these we can array both the arrays and the floats
//for now let us just try 1 smoothing parameter for everything.
float p_lock_smooth=.5;


//and then lets try an array of floats for storing the smoothed values
float p_lock_smoothed[p_lock_number];


//turn on and off writing to the array
bool p_lock_0_switch=1;

//global counter for all the locks
int p_lock_increment=0;

//midi latching
int midiActiveFloat[p_lock_number];

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofBackground(0);
    ofHideCursor();
	midiSetup();
	fbDeclareAndAllocate();
	
	//shadersbiz
    shader_osc0.load("shadersGL4/shader_osc0");
    shader_osc1.load("shadersGL4/shader_osc1");

    //omx_settings();  
    inputSetup();
    pLockInitialize();
    
}
//--------------------------------------------------------------
void ofApp::update() {
	midibiz();
	inputUpdate();
	pLockUpdate();
}
//--------------------------------------------------------------
void ofApp::pLockUpdate(){
	for(int i=0;i<p_lock_number;i++){
        p_lock_smoothed[i]=p_lock[i][p_lock_increment]*(1.0f-p_lock_smooth)+p_lock_smoothed[i]*p_lock_smooth;
        if(abs(p_lock_smoothed[i])<.001){p_lock_smoothed[i]=0;}
    }
}

//--------------------------------------------------------------
void ofApp::inputUpdate(){
	
	cam1.update();
	/*
		
		if(hdmi_aspect_ratio_switch==1){
			aspect_fix_fbo.begin();
			cam1.draw(0,0,426,240);
			aspect_fix_fbo.end();
		}
	*/
	
	if(hdmi_aspect_ratio_switch==0){
		aspect_fix_fbo.begin();
			ofPushMatrix();
			ofTranslate(0,-120);
			cam1.draw(0,0,1280,960);
			ofPopMatrix();
		aspect_fix_fbo.end();
		
	}
	
	if(hdmi_aspect_ratio_switch==1){
			aspect_fix_fbo.begin();
			cam1.draw(0,0,1280,720);
			aspect_fix_fbo.end();		
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	/**controls**/
	float osc0_pm_scale=.01;
	float osc0_rm_scale=10;
	float osc0_cutoff=.25;

	if(osc0_pm_rm_switch==0){
		osc0_pm_scale=.01;
		osc0_rm_scale=10;
		osc0_cutoff=.25;
	}
	if(osc0_pm_rm_switch==3){
		osc0_pm_scale=.05;
		osc0_rm_scale=10;
		osc0_cutoff=.05;
	}

	float osc1_pm_scale=.01;
	float osc1_rm_scale=10;
	float osc1_cutoff=.25;
	
	if(osc1_pm_rm_switch==0){
		osc1_pm_scale=.01;
		osc1_rm_scale=10;
		osc1_cutoff=.25;
	}
	
	if(osc1_pm_rm_switch==3){
		osc1_pm_scale=.05;
		osc1_rm_scale=10;
		osc1_cutoff=.05;
	}
	ofSetColor(255);
    float osc_frequency_scale=.05;  
    float osc_rate_scale=.15;   
    float angle_scale=3.14;   
    float modulation_rotate_scale=5.0;   
    float spiral_scale=ofGetWidth()*.000025f;    
    float cam_pm_scale=20.0;    
    float osc_rate_mod_scale=.15;    
    float osc_rotate_scale=.01;    
    float oscRgbOffsetScale=1.0;
    
    /**shader**/
    
    //cam1.draw(0,0);
    
    
    fb_osc0.begin();
    aspect_fix_fbo.draw(0,0);
    
    shader_osc0.begin();
    fb_osc1_pp.draw(0,0);
    if(internal_feedback_switch0==0){
    	shader_osc0.setUniformTexture("cam1", aspect_fix_fbo.getTexture(),1);
    }
    if(internal_feedback_switch0==1){
		shader_osc0.setUniformTexture("cam1", fb_osc0_pp.getTexture(),1);
    }

    osc0_rate+=osc_rate_scale*p_lock_smoothed[0]+sin(osc1_rate)*p_lock_smoothed[7]*osc_rate_mod_scale;
    osc0_m_rate+=osc_rate_scale*p_lock_smoothed[16]+sin(osc1_m_rate)*p_lock_smoothed[23]*osc_rate_mod_scale;
    
    osc0_rotate+=osc_rotate_scale*p_lock_smoothed[33]; 
    osc0_m_rotate+=osc_rotate_scale*p_lock_smoothed[39];
        
    shader_osc0.setUniform1f("osc0_rate",osc0_rate);
    shader_osc0.setUniform1f("osc0_amp",p_lock_smoothed[8]);
    shader_osc0.setUniform1f("osc0_frequency",p_lock_smoothed[1]*osc_frequency_scale);
    shader_osc0.setUniform1f("osc0_angle",p_lock_smoothed[9]*angle_scale);
    shader_osc0.setUniform1f("osc0_rm",osc0_rm_scale*p_lock_smoothed[2]);
    shader_osc0.setUniform1f("osc0_pm",osc0_pm_scale*p_lock_smoothed[10]);    
    shader_osc0.setUniform1f("osc0_rotate",fmod(osc0_rotate,2.0f*PI)); 
    shader_osc0.setUniform1f("osc0_spiral",p_lock_smoothed[32]*spiral_scale);
    shader_osc0.setUniform1f("osc0_modulation_rotate",p_lock_smoothed[34]*modulation_rotate_scale);   
    shader_osc0.setUniform1f("osc0_m_rate",osc0_m_rate);
    shader_osc0.setUniform1f("osc0_m_amp",p_lock_smoothed[24]);
    shader_osc0.setUniform1f("osc0_m_frequency",p_lock_smoothed[17]*osc_frequency_scale);
    shader_osc0.setUniform1f("osc0_m_angle",p_lock_smoothed[25]*angle_scale);
    shader_osc0.setUniform1f("osc0_m_rm",p_lock_smoothed[18]*osc0_rm_scale);
    shader_osc0.setUniform1f("osc0_m_pm",p_lock_smoothed[26]*osc0_pm_scale);    
    shader_osc0.setUniform1f("osc0_m_rotate",fmod(osc0_m_rotate,2.0f*PI));
    shader_osc0.setUniform1f("osc0_m_spiral",p_lock_smoothed[38]*spiral_scale);
    shader_osc0.setUniform1f("osc0_m_modulation_rotate",p_lock_smoothed[40]*modulation_rotate_scale);    
    shader_osc0.setUniform1f("osc0_cam1_pm",p_lock_smoothed[6]*cam_pm_scale);   
    shader_osc0.setUniform1f("osc0_m_cam1_pm",p_lock_smoothed[22]*cam_pm_scale);
    shader_osc0.setUniform1f("osc0_feedback_filter",p_lock_smoothed[6]*.75);    
    shader_osc0.setUniform1f("osc0_r_offset",p_lock_smoothed[44]*oscRgbOffsetScale);
    shader_osc0.setUniform1f("osc0_g_offset",p_lock_smoothed[45]*oscRgbOffsetScale);
    shader_osc0.setUniform1f("osc0_b_offset",p_lock_smoothed[46]*oscRgbOffsetScale);
    shader_osc0.setUniform1f("osc0_powmod",p_lock_smoothed[47]);
    //new PWM biz
    shader_osc0.setUniform1f("osc0_width",p_lock_smoothed[53]);
    shader_osc0.setUniform1f("osc0_pwm",p_lock_smoothed[54]);
    shader_osc0.setUniform1f("osc0_m_width",p_lock_smoothed[55]);
    shader_osc0.setUniform1f("osc0_m_pwm",p_lock_smoothed[56]*2.0f);
    shader_osc0.setUniform1f("osc0_cutoff",osc0_cutoff);

    shader_osc0.setUniform1i("osc0_shape",osc0_shape);  
    shader_osc0.setUniform1i("osc0_m_shape",osc0_m_shape);

    shader_osc0.setUniform1f("width",ofGetWidth());
    shader_osc0.setUniform1f("height",ofGetHeight());
    
    shader_osc0.setUniform1i("osc0_overflow_switch",overflow_switch);
    
    shader_osc0.setUniform1i("internal_feedback_switch0", internal_feedback_switch0);
    shader_osc0.end();
    
    fb_osc0.end();



    //osc1
    
    
    fb_osc1.begin(); 
    shader_osc1.begin();
    
    fb_osc0_pp.draw(0,0);

    if(internal_feedback_switch1==0){
		shader_osc1.setUniformTexture("cam1", aspect_fix_fbo.getTexture(),3);
    } 
    if(internal_feedback_switch1==1){
		shader_osc1.setUniformTexture("cam1", fb_osc1_pp.getTexture(),3);
    }

	osc1_rate+=osc_rate_scale*p_lock_smoothed[3]+sin(osc0_rate)*p_lock_smoothed[15]*osc_rate_mod_scale;
    osc1_m_rate+=osc_rate_scale*p_lock_smoothed[19]+sin(osc0_m_rate)*p_lock_smoothed[31]*osc_rate_mod_scale;
    
    osc1_rotate+=osc_rotate_scale*p_lock_smoothed[36];
    osc1_m_rotate+=osc_rotate_scale*p_lock_smoothed[42];
    
    shader_osc1.setUniform1f("osc1_rate",osc1_rate);
    shader_osc1.setUniform1f("osc1_amp",p_lock_smoothed[11]);
    shader_osc1.setUniform1f("osc1_frequency",p_lock_smoothed[4]*osc_frequency_scale);
    shader_osc1.setUniform1f("osc1_angle",p_lock_smoothed[12]*angle_scale);
    shader_osc1.setUniform1f("osc1_rm",osc1_rm_scale*p_lock_smoothed[5]);
    shader_osc1.setUniform1f("osc1_pm",osc1_pm_scale*p_lock_smoothed[13]);  
    shader_osc1.setUniform1f("osc1_rotate",fmod(osc1_rotate,2.0f*PI));
    shader_osc1.setUniform1f("osc1_spiral",p_lock_smoothed[35]*spiral_scale);
    shader_osc1.setUniform1f("osc1_modulation_rotate",p_lock_smoothed[37]*modulation_rotate_scale); 
    shader_osc1.setUniform1f("osc1_m_rate",osc1_m_rate);
    shader_osc1.setUniform1f("osc1_m_amp",p_lock_smoothed[27]);
    shader_osc1.setUniform1f("osc1_m_frequency",p_lock_smoothed[20]*osc_frequency_scale);
    shader_osc1.setUniform1f("osc1_m_angle",p_lock_smoothed[28]*angle_scale);
    shader_osc1.setUniform1f("osc1_m_rm",p_lock_smoothed[21]*osc1_rm_scale);
    shader_osc1.setUniform1f("osc1_m_pm",p_lock_smoothed[29]*2.0f*osc1_pm_scale);
	shader_osc1.setUniform1f("osc1_cam1_pm",p_lock_smoothed[14]*cam_pm_scale);
	shader_osc1.setUniform1f("osc1_m_cam1_pm",p_lock_smoothed[30]*cam_pm_scale);
	shader_osc1.setUniform1f("osc1_m_rotate",fmod(osc1_m_rotate,2.0f*PI));
	shader_osc1.setUniform1f("osc1_m_spiral",p_lock_smoothed[41]*spiral_scale);
    shader_osc1.setUniform1f("osc1_m_modulation_rotate",p_lock_smoothed[43]*modulation_rotate_scale);
    shader_osc1.setUniform1f("osc1_feedback_filter",p_lock_smoothed[14]*.75);
	shader_osc1.setUniform1f("osc1_cutoff",osc1_cutoff);

    //change names to color bands
    shader_osc1.setUniform1f("osc1_r_offset",p_lock_smoothed[48]);
    shader_osc1.setUniform1f("osc1_g_offset",p_lock_smoothed[49]);
    shader_osc1.setUniform1f("osc1_b_offset",p_lock_smoothed[50]);
    shader_osc1.setUniform1f("osc1_powmod",p_lock_smoothed[51]);
	//new PWM biz
    shader_osc1.setUniform1f("osc1_width",p_lock_smoothed[57]);
    shader_osc1.setUniform1f("osc1_pwm",p_lock_smoothed[58]);
    shader_osc1.setUniform1f("osc1_m_width",p_lock_smoothed[59]);
    shader_osc1.setUniform1f("osc1_m_pwm",p_lock_smoothed[60]*2.0f);
	
    shader_osc1.setUniform1i("osc1_shape",osc1_shape);
    shader_osc1.setUniform1i("osc1_m_shape",osc1_m_shape);
    
    shader_osc1.setUniform1f("width",ofGetWidth());
    shader_osc1.setUniform1f("height",ofGetHeight());
    
    shader_osc1.setUniform1i("osc1_overflow_switch",overflow_switch);
    shader_osc1.setUniform1i("internal_feedback_switch1", internal_feedback_switch1);
    
    shader_osc1.end();
    fb_osc1.end();
  
  
  
  
    if(draw_switch==0){
        fb_osc0.draw(0,0);
    }
    
    if(draw_switch==1){
        fb_osc1.draw(0,0);
    }
 
    fbUpdate();
    
    ofSetColor(255);
    string msg="fps="+ofToString(ofGetFrameRate(),2);//+" clear switch"+ofToString(clear_switch,5);//+" z="+ofToString(az,5);
    //ofDrawBitmapString(msg,10,10);
    
     if(p_lock_record_switch==1){
        p_lock_increment++;
        p_lock_increment=p_lock_increment%p_lock_size;
    }
}
//-------------------------------------------------------------
void ofApp::fbUpdate(){
	//don't actually need all of these buffers around\?  can instead
    //just feed the fb direct into each one and then clear the buffer in between each feedback draw
    //lets fix this this time around

    fb_osc0_pp.begin();
    fb_osc0.draw(0,0);
    fb_osc0_pp.end();
    
    fb_osc0.begin();
    ofClear(0,0,0,255);
    fb_osc0.end();
    
    fb_osc1_pp.begin();
    fb_osc1.draw(0,0);
    fb_osc1_pp.end();
    
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1.end();
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {	
	if(key=='1'){osc0_pm_rm_switch=0; osc1_pm_rm_switch=0;}
	if(key=='2'){osc0_pm_rm_switch=1; osc1_pm_rm_switch=1;}	
	if(key=='3'){osc0_pm_rm_switch=2; osc1_pm_rm_switch=2;}	
	if(key=='4'){osc0_pm_rm_switch=3; osc1_pm_rm_switch=3;}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	
}

//--------------------------------------------------------
void ofApp::pLockInitialize(){
	//do some initializing
    for(int i=0;i<p_lock_size;i++){
		p_lock[1][i]=.5;
		p_lock[8][i]=1.0;
		
		p_lock[17][i]=.5;
		p_lock[24][i]=1.0;
		
		p_lock[4][i]=.5;
		p_lock[11][i]=1.0;
		
		p_lock[20][i]=.5;
		p_lock[27][i]=1.0;
		
		midiActiveFloat[i]=0;
	}
}

//---------------------------------------------------------
void ofApp::fbDeclareAndAllocate(){
	fb_osc0.allocate(width,height);
    fb_osc0.begin();
    ofClear(0,0,0,255);
    fb_osc0.end();
    
    fb_osc1.allocate(width,height);
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1.end();
    
    fb_osc0_pp.allocate(width,height);
    fb_osc0_pp.begin();
    ofClear(0,0,0,255);
    fb_osc0_pp.end();
    
    fb_osc1_pp.allocate(width,height);
    fb_osc1.begin();
    ofClear(0,0,0,255);
    fb_osc1_pp.end();
    
    aspect_fix_fbo.allocate(width,height);
    aspect_fix_fbo.begin();
    ofClear(0,0,0,255);
    aspect_fix_fbo.end();
}

//-----------------------------------------------------------
void ofApp:: midiSetup(){
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
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
//------------------------------------------------------------
void ofApp::inputSetup(){
	if(inputswitch==0){
		//videoGrabber.setup(settings);
	}
	if(inputswitch==1){
		cam1.setDesiredFrameRate(30);
		cam1.initGrabber(640,480);
	}
}

//--------------------------------------------------------------
//---------------------
void ofApp:: midibiz(){
    
    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        
        ofxMidiMessage &message = midiMessages[i];
        
        
        //cout << "envcount="<< envcount<< endl;
        
        if(message.status < MIDI_SYSEX) {
            //text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                //  cout << "message.control"<< message.control<< endl;
                //  cout << "message.value"<< message.value<< endl;
                
                if(message.control==45){
					if(message.value==127){
						p_lock_record_switch=1;
						for(int i=0;i<p_lock_number;i++){
							p_lock_smoothed[i]=0;
							for(int j=0;j<p_lock_size;j++){    
								p_lock[i][j]=p_lock[i][p_lock_increment];
                            }
						}	
					}
					if(message.value==0){
						p_lock_record_switch=0;
					}
				}
                //swap cam input pm for internal feedback pm
                if(message.control==43){
                    if(message.value==127){
                        internal_feedback_switch0=1;
                    } 
                    if(message.value==0){
                        internal_feedback_switch0=0;                        
                    }
                } 
                if(message.control==44){
                    if(message.value==127){
                        internal_feedback_switch1=1;
                    } 
                    if(message.value==0){
                        internal_feedback_switch1=0;
                    }
                }
                //osc rgbp switches  4.5: these are now colorizer switches
                if(message.control==38){
                    if(message.value==127){
                        osc_rgbp_switch=1;
                    }
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }
                if(message.control==54){
                    if(message.value==127){
                        osc_rgbp_switch=2;
                    }
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }               
                if(message.control==70){
                    if(message.value==127){
                        osc_rgbp_switch=3;
                    }                    
                    if(message.value==0){
                        osc_rgbp_switch=0;
                    }
                }                
                //rm/pm scaling switches
				//osc0	
				//if osc0_pm_rm_switch=1 then width control is on
                 if(message.control==34){
                    if(message.value==127){
                         osc0_pm_rm_switch=1;
                    }                   
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                }
                //if osc0_pm_rm_switch=2 then osc1PWM is on
                if(message.control==50){
                    if(message.value==127){
                         osc0_pm_rm_switch=2;
                    }                    
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                 }               
                 if(message.control==66){
                    if(message.value==127){
                         osc0_pm_rm_switch=3;
                    }                   
                    if(message.value==0){
                         osc0_pm_rm_switch=0;
                    }
                }                
                //osc1	
                 if(message.control==37){
                    if(message.value==127){
                         osc1_pm_rm_switch=1;
                    }                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                }               
                if(message.control==53){
                    if(message.value==127){
                         osc1_pm_rm_switch=2;
                    }                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                 }               
                 if(message.control==69){
                    if(message.value==127){
                         osc1_pm_rm_switch=3;
                    }                    
                    if(message.value==0){
                         osc1_pm_rm_switch=0;
                    }
                }
                //overflow switches
                if(message.control==60){
                    if(message.value==127){
                        overflow_switch=1;
                    }
                    
                    if(message.value==0){
                        overflow_switch=0;
                    }
                }                
                if(message.control==61){
                    if(message.value==127){
                        overflow_switch=2;
                    }                    
                    if(message.value==0){
                        overflow_switch=0;
                    }
                }                
                if(message.control==62){					
                    if(message.value==127){
                         hdmi_aspect_ratio_switch=1;
                        //overflow_switch=3;
                    }                    
                    if(message.value==0){
						hdmi_aspect_ratio_switch=0;
                        //overflow_switch=0;
                    }
                }
                if(message.control==46){
                    if(message.value==127){
                        draw_switch=1;
                    }                    
                    if(message.value==0){
                        draw_switch=0;
                    }
                }
                if(message.control==32){
                    if(message.value==127){
                        osc0_mod_switch=1;
                        for(int i=0;i<3;i++){
							midiActiveFloat[i]=0;
						}
                    }                    
                    if(message.value==0){
                        osc0_mod_switch=0;
                         for(int i=16;i<19;i++){
							midiActiveFloat[i]=0;
						}
                    }
                }                
                if(message.control==35){
                    if(message.value==127){
                        osc1_mod_switch=1;                        
                    }                    
                    if(message.value==0){
                        osc1_mod_switch=0;                        
                    }
                }
                //osc0 axis switches
                if(message.control==33){
                    if(message.value==127){
                        osc0_axis_switch=1;                       
                    }                   
                    if(message.value==0){
                       osc0_axis_switch=0;                       
                    }
                }               
                if(message.control==49){
                    if(message.value==127){
                        osc0_axis_switch=2;                        
                    }                   
                    if(message.value==0){
                        osc0_axis_switch=0;                       
                    }
                }                
                if(message.control==65){
                    if(message.value==127){
                        osc0_axis_switch=3;
                    }                   
                    if(message.value==0){
                        osc0_axis_switch=0;
                    }
                }               
                //osc1_m axis switches
                if(message.control==36){
                    if(message.value==127){
                        osc1_axis_switch=1;
                    }
                    if(message.value==0){
                        osc1_axis_switch=0;
                    }
                }
                if(message.control==52){
                    if(message.value==127){
                        osc1_axis_switch=2; 
                    }
                    if(message.value==0){
                        osc1_axis_switch=0;
                    }
                }
                if(message.control==68){
                    if(message.value==127){
                        osc1_axis_switch=3;
                    }
                    if(message.value==0){
                        osc1_axis_switch=0; 
                    }
                }
                //shapes
                //osc0
                if(message.control==48){
                    if(osc0_mod_switch==0){
                        if(message.value==127){
                            osc0_shape=1;
                        }
                        if(message.value==0){
                            osc0_shape=0;
                        }
                    }
                    if(osc0_mod_switch==1){
                        if(message.value==127){
                            osc0_m_shape=1; 
                        }
                        if(message.value==0){
                            osc0_m_shape=0;
                        }
                    }
                }
                if(message.control==64){
                    if(osc0_mod_switch==0){
                        if(message.value==127){
                            osc0_shape=2;  
                        } 
                        if(message.value==0){
                            osc0_shape=0;
                        }
                    } 
                    if(osc0_mod_switch==1){
                        if(message.value==127){
                            osc0_m_shape=2;                            
                        }                        
                        if(message.value==0){
                            osc0_m_shape=0;                            
                        }
                    }
                }
                //osc1
                if(message.control==51){
                    if(osc1_mod_switch==0){
                        if(message.value==127){
                            osc1_shape=1;                            
                        }                        
                        if(message.value==0){
                            osc1_shape=0;
                        }
                    }
                    if(osc1_mod_switch==1){
                        if(message.value==127){
                            osc1_m_shape=1;   
                        }
                        if(message.value==0){
                            osc1_m_shape=0;           
                        }
                    }
                }
                if(message.control==67){
                    if(osc1_mod_switch==0){
                        if(message.value==127){
                            osc1_shape=2;   
                        }
                        if(message.value==0){
                            osc1_shape=0;       
                        }
                    }
                    if(osc1_mod_switch==1){
                        if(message.value==127){
                            osc1_m_shape=2;
                        }    
                        if(message.value==0){
                            osc1_m_shape=0;           
                        }
                    }
                }
				//osc_rate_swithce //cam pm switches				
				if(message.control==39){
					if(message.value==127){
						osc_m_rate_switch=1;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				}               
                if(message.control==55){
					if(message.value==127){
						osc_m_rate_switch=2;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				 }				
				  if(message.control==71){
					if(message.value==127){
						osc_m_rate_switch=3;
					}
					if(message.value==0){
						osc_m_rate_switch=0;
					}
				}                
                //nanokontrol2 controls
                if(message.control==16){
                    if(osc0_mod_switch==0){
						midiActiveFloat[16]=0;
						/*
						cout<<"diff = "<<abs(p_lock[0][p_lock_increment]-(message.value-MIDI_MAGIC)/MIDI_MAGIC)<<endl;
						cout<<"message value = "<<message.value<<endl;
						cout<<"midiActiveFloat[0] = "<<midiActiveFloat[0]<<endl;
						*/
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[0][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[0]=1;
						} 
                        if(midiActiveFloat[0]==1){
							p_lock[0][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                    if(osc0_mod_switch==1){
						midiActiveFloat[0]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[16][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[16]=1;
						} 
                        if(midiActiveFloat[16]==1){
							p_lock[16][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                }
                if(message.control==17){  
                    if(osc0_mod_switch==0){
						midiActiveFloat[17]=0;
                        if(abs(message.value/127.0f-p_lock[1][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[1]=1;
						}
						if(midiActiveFloat[1]==1){ 
							p_lock[1][p_lock_increment]=(message.value)/127.0f;
						}
                    }
                    
                    if(osc0_mod_switch==1){
						midiActiveFloat[1]=0;
                       if(abs(message.value/127.0f-p_lock[17][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[17]=1;
						}
						if(midiActiveFloat[17]==1){
							p_lock[17][p_lock_increment]=(message.value)/127.0f;
						}
                    }
                }  
                if(message.control==18){
                    if(osc0_mod_switch==0){
						midiActiveFloat[18]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[2][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[2]=1;
						} 
                        if(midiActiveFloat[2]==1){
							p_lock[2][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    } 
                    if(osc0_mod_switch==1){
						midiActiveFloat[2]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[18][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[18]=1;
						}
						if(midiActiveFloat[18]==1){
							p_lock[18][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                }
                if(message.control==19){
                    if(osc1_mod_switch==0){
						midiActiveFloat[19]=0;
                        if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[3][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[3]=1;
						} 
                        if(midiActiveFloat[3]==1){
							p_lock[3][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                    if(osc1_mod_switch==1){
						midiActiveFloat[3]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[19][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[19]=1;
						}
						if(midiActiveFloat[19]==1){
							p_lock[19][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                }
                if(message.control==20){
                    if(osc1_mod_switch==0){
                       midiActiveFloat[20]=0;
                        if(abs(message.value/127.0f-p_lock[4][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[4]=1;
						} 
                        if(midiActiveFloat[4]==1){
							p_lock[4][p_lock_increment]=(message.value)/127.0f;
						}
                    }
                    if(osc1_mod_switch==1){
                       midiActiveFloat[4]=0;
                        if(abs(message.value/127.0f-p_lock[20][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[20]=1;
						}
						if(midiActiveFloat[20]==1){
							p_lock[20][p_lock_increment]=(message.value)/127.0f;
						}
                    }
                }
                if(message.control==21){  
                    if(osc1_mod_switch==0){
                        midiActiveFloat[21]=0;
                        if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[5][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[5]=1;
						} 
                        if(midiActiveFloat[5]==1){
							p_lock[5][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                    if(osc1_mod_switch==1){
                    	midiActiveFloat[5]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[21][p_lock_increment])<CONTROL_THRESHOLD){
							midiActiveFloat[21]=1;
						}
						if(midiActiveFloat[21]==1){
							p_lock[21][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}  
                    }
                }
                if(message.control==22){
                    if(osc_rgbp_switch==0){
						midiActiveFloat[45]=0;
						midiActiveFloat[46]=0;
						midiActiveFloat[47]=0;
						if(abs(message.value/127.0f-p_lock[44][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[44]=1;
						} 
						if(midiActiveFloat[44]==1){
							p_lock[44][p_lock_increment]=message.value/127.0f;
						}	
                    }    
                    if(osc_rgbp_switch==1){
						midiActiveFloat[44]=0;
						midiActiveFloat[46]=0;
						midiActiveFloat[47]=0;
						if(abs(message.value/127.0f-p_lock[45][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[45]=1;
						} 
						if(midiActiveFloat[45]==1){
							p_lock[45][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_rgbp_switch==2){
						midiActiveFloat[44]=0;
						midiActiveFloat[45]=0;
						midiActiveFloat[47]=0;
						if(abs(message.value/127.0f-p_lock[46][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[46]=1;
						} 
						if(midiActiveFloat[46]==1){
							p_lock[46][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_rgbp_switch==3){
						midiActiveFloat[44]=0;
						midiActiveFloat[45]=0;
						midiActiveFloat[46]=0;
						if(abs(message.value/127.0f-p_lock[47][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[47]=1;
						} 
						if(midiActiveFloat[47]==1){
							p_lock[47][p_lock_increment]=message.value/127.0f;
						}
                    }  
                }
                
                
                if(message.control==23){
					if(osc_m_rate_switch==0){
						midiActiveFloat[22]=0;
						midiActiveFloat[23]=0;
						midiActiveFloat[6]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[7][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[7]=1;
						} 
						if(midiActiveFloat[7]==1){
							p_lock[7][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}	
                    }
                    if(osc_m_rate_switch==1){
						midiActiveFloat[22]=0;
						midiActiveFloat[7]=0;
						midiActiveFloat[6]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[23][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[23]=1;
						} 
						if(midiActiveFloat[23]==1){
							p_lock[23][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                    
                    if(osc_m_rate_switch==2){
						midiActiveFloat[23]=0;
						midiActiveFloat[7]=0;
						midiActiveFloat[22]=0;
						if(abs(message.value/127.0f-p_lock[6][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[6]=1;
						} 
						if(midiActiveFloat[6]==1){
							p_lock[6][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_m_rate_switch==3){
						midiActiveFloat[23]=0;
						midiActiveFloat[7]=0;
						midiActiveFloat[6]=0;
						if(abs(message.value/127.0f-p_lock[22][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[22]=1;
						} 
						if(midiActiveFloat[22]==1){
							p_lock[22][p_lock_increment]=message.value/127.0f;
						}	
                    }    
                }
                if(message.control==120){
                    if(osc0_mod_switch==0){
						midiActiveFloat[24]=0;
						if(abs(message.value/127.0f-p_lock[8][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[8]=1;
						} 
						if(midiActiveFloat[8]==1){
							p_lock[8][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc0_mod_switch==1){
						midiActiveFloat[8]=0;
                        if(abs(message.value/127.0f-p_lock[24][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[24]=1;
						} 
						if(midiActiveFloat[24]==1){
							p_lock[24][p_lock_increment]=message.value/127.0f;
						}
                    }    
                }
                if(message.control==121){
                    if(osc0_mod_switch==0){
						midiActiveFloat[25]=0;
						midiActiveFloat[38]=0;
						midiActiveFloat[39]=0;
						midiActiveFloat[40]=0;
						if(osc0_axis_switch==0){
							midiActiveFloat[32]=0;
							midiActiveFloat[33]=0;
							midiActiveFloat[34]=0;
							if(abs(message.value/127.0f-p_lock[9][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[9]=1;
							}
							if(midiActiveFloat[9]==1){
								p_lock[9][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc0_axis_switch==1){
							midiActiveFloat[9]=0;
							midiActiveFloat[33]=0;
							midiActiveFloat[34]=0;
							if(abs(message.value/127.0f-p_lock[32][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[32]=1;
							}
							if(midiActiveFloat[32]==1){
								p_lock[32][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc0_axis_switch==2){
							midiActiveFloat[9]=0;
							midiActiveFloat[32]=0;
							midiActiveFloat[34]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[33][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[33]=1;
							}
							if(midiActiveFloat[33]==1){
								p_lock[33][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc0_axis_switch==3){
							midiActiveFloat[9]=0;
							midiActiveFloat[33]=0;
							midiActiveFloat[32]=0;
							if(abs(message.value/127.0f-p_lock[34][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[34]=1;
							}
							if(midiActiveFloat[34]==1){
								p_lock[34][p_lock_increment]=(message.value)/127.0f;
							}
						}
					}
					if(osc0_mod_switch==1){
						midiActiveFloat[9]=0;
						midiActiveFloat[32]=0;
						midiActiveFloat[33]=0;
						midiActiveFloat[34]=0;
						if(osc0_axis_switch==0){
							midiActiveFloat[38]=0;
							midiActiveFloat[39]=0;
							midiActiveFloat[40]=0;
							if(abs(message.value/127.0f-p_lock[25][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[25]=1;
							}
							if(midiActiveFloat[25]==1){
								p_lock[25][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc0_axis_switch==1){
							midiActiveFloat[25]=0;
							midiActiveFloat[39]=0;
							midiActiveFloat[40]=0;
							if(abs(message.value/127.0f-p_lock[38][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[38]=1;
							}
							if(midiActiveFloat[38]==1){
								p_lock[38][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc0_axis_switch==2){
							midiActiveFloat[25]=0;
							midiActiveFloat[38]=0;
							midiActiveFloat[40]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[39][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[39]=1;
							}
							if(midiActiveFloat[39]==1){
								p_lock[39][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc0_axis_switch==3){
							midiActiveFloat[25]=0;
							midiActiveFloat[39]=0;
							midiActiveFloat[38]=0;
							if(abs(message.value/127.0f-p_lock[40][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[40]=1;
							}
							if(midiActiveFloat[40]==1){
								p_lock[40][p_lock_increment]=(message.value)/127.0f;
							}
						}
					}
                }
                //pm, pwm
                if(message.control==122){
                    if(osc0_mod_switch==0){
                        midiActiveFloat[26]=0;
                        midiActiveFloat[55]=0;
                        midiActiveFloat[26]=0;
                        if(osc0_pm_rm_switch==0 || osc0_pm_rm_switch==3){
							midiActiveFloat[53]=0;
							midiActiveFloat[54]=0;
							if(abs(message.value/127.0f-p_lock[10][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[10]=1;
							}
							if(midiActiveFloat[10]==1){
								p_lock[10][p_lock_increment]=(message.value)/127.0f;
							}
						}	
                        if(osc0_pm_rm_switch==1){
							midiActiveFloat[10]=0;
							midiActiveFloat[54]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[53][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[53]=1;
							}
							if(midiActiveFloat[53]==1){
								p_lock[53][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc0_pm_rm_switch==2){
							midiActiveFloat[10]=0;
							midiActiveFloat[53]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[54][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[54]=1;
							}
							if(midiActiveFloat[54]==1){
								p_lock[54][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
                    }
                    if(osc0_mod_switch==1){
                        midiActiveFloat[10]=0;
                        midiActiveFloat[53]=0;
                        midiActiveFloat[54]=0;
                        if(osc0_pm_rm_switch==0 || osc0_pm_rm_switch==3){
							midiActiveFloat[55]=0;
							midiActiveFloat[56]=0;
							if(abs(message.value/127.0f-p_lock[26][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[26]=1;
							}
							if(midiActiveFloat[26]==1){
								p_lock[26][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc0_pm_rm_switch==1){
							midiActiveFloat[26]=0;
							midiActiveFloat[56]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[55][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[55]=1;
							}
							if(midiActiveFloat[55]==1){
								p_lock[55][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc0_pm_rm_switch==2){
							midiActiveFloat[26]=0;
							midiActiveFloat[55]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[56][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[56]=1;
							}
							if(midiActiveFloat[56]==1){
								p_lock[56][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}	
                    }
                }
                //amp
                if(message.control==123){
					if(osc0_mod_switch==0){
						midiActiveFloat[27]=0;
						if(abs(message.value/127.0f-p_lock[11][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[11]=1;
						} 
						if(midiActiveFloat[11]==1){
							p_lock[11][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc0_mod_switch==1){
						midiActiveFloat[11]=0;
                        if(abs(message.value/127.0f-p_lock[24][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[27]=1;
						} 
						if(midiActiveFloat[27]==1){
							p_lock[27][p_lock_increment]=message.value/127.0f;
						}
                    } 
                }
                //osc1 axis
                if(message.control==124){
                    if(osc1_mod_switch==0){
						midiActiveFloat[28]=0;
						midiActiveFloat[41]=0;
						midiActiveFloat[42]=0;
						midiActiveFloat[43]=0;
						if(osc1_axis_switch==0){
							midiActiveFloat[35]=0;
							midiActiveFloat[36]=0;
							midiActiveFloat[37]=0;
							if(abs(message.value/127.0f-p_lock[12][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[12]=1;
							}
							if(midiActiveFloat[12]==1){
								p_lock[12][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc1_axis_switch==1){
							midiActiveFloat[12]=0;
							midiActiveFloat[36]=0;
							midiActiveFloat[37]=0;
							if(abs(message.value/127.0f-p_lock[35][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[35]=1;
							}
							if(midiActiveFloat[35]==1){
								p_lock[35][p_lock_increment]=(message.value)/127.0f;
							}
						}
						
						if(osc1_axis_switch==2){
							midiActiveFloat[12]=0;
							midiActiveFloat[35]=0;
							midiActiveFloat[35]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[36][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[36]=1;
							}
							if(midiActiveFloat[36]==1){
								p_lock[36][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc1_axis_switch==3){
							midiActiveFloat[12]=0;
							midiActiveFloat[35]=0;
							midiActiveFloat[36]=0;
							if(abs(message.value/127.0f-p_lock[37][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[37]=1;
							}
							if(midiActiveFloat[37]==1){
								p_lock[37][p_lock_increment]=(message.value)/127.0f;
							}
						}
					}
					if(osc1_mod_switch==1){
						midiActiveFloat[12]=0;
						midiActiveFloat[35]=0;
						midiActiveFloat[36]=0;
						midiActiveFloat[37]=0;
						if(osc1_axis_switch==0){
							midiActiveFloat[41]=0;
							midiActiveFloat[42]=0;
							midiActiveFloat[43]=0;
							if(abs(message.value/127.0f-p_lock[28][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[28]=1;
							}
							if(midiActiveFloat[28]==1){
								p_lock[28][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc1_axis_switch==1){
							midiActiveFloat[28]=0;
							midiActiveFloat[42]=0;
							midiActiveFloat[43]=0;
							if(abs(message.value/127.0f-p_lock[41][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[41]=1;
							}
							if(midiActiveFloat[41]==1){
								p_lock[41][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc1_axis_switch==2){
							midiActiveFloat[28]=0;
							midiActiveFloat[41]=0;
							midiActiveFloat[43]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[42][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[42]=1;
							}
							if(midiActiveFloat[42]==1){
								p_lock[39][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc1_axis_switch==3){
							midiActiveFloat[28]=0;
							midiActiveFloat[41]=0;
							midiActiveFloat[42]=0;
							if(abs(message.value/127.0f-p_lock[43][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[43]=1;
							}
							if(midiActiveFloat[43]==1){
								p_lock[43][p_lock_increment]=(message.value)/127.0f;
							}
						}
					}
                }
                //pm, pwm
                if(message.control==125){
                    if(osc1_mod_switch==0){
                        midiActiveFloat[29]=0;
                        midiActiveFloat[59]=0;
                        midiActiveFloat[60]=0;
                        if(osc1_pm_rm_switch==0 || osc1_pm_rm_switch==3){
							midiActiveFloat[57]=0;
							midiActiveFloat[58]=0;
							if(abs(message.value/127.0f-p_lock[13][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[13]=1;
							}
							if(midiActiveFloat[13]==1){
								p_lock[13][p_lock_increment]=(message.value)/127.0f;
							}
						}	
                        if(osc1_pm_rm_switch==1){
							midiActiveFloat[13]=0;
							midiActiveFloat[58]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[57][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[57]=1;
							}
							if(midiActiveFloat[57]==1){
								p_lock[57][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc1_pm_rm_switch==2){
							midiActiveFloat[13]=0;
							midiActiveFloat[57]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[58][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[58]=1;
							}
							if(midiActiveFloat[58]==1){
								p_lock[58][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
                    }
                    if(osc1_mod_switch==1){
                        midiActiveFloat[13]=0;
                        midiActiveFloat[57]=0;
                        midiActiveFloat[58]=0;
                        if(osc1_pm_rm_switch==0 || osc1_pm_rm_switch==3){
							midiActiveFloat[59]=0;
							midiActiveFloat[60]=0;
							if(abs(message.value/127.0f-p_lock[29][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[29]=1;
							}
							if(midiActiveFloat[29]==1){
								p_lock[29][p_lock_increment]=(message.value)/127.0f;
							}
						}
						if(osc1_pm_rm_switch==1){
							midiActiveFloat[29]=0;
							midiActiveFloat[60]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[59][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[59]=1;
							}
							if(midiActiveFloat[59]==1){
								p_lock[59][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}
						if(osc1_pm_rm_switch==2){
							midiActiveFloat[29]=0;
							midiActiveFloat[59]=0;
							if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[60][p_lock_increment])<CONTROL_THRESHOLD ){
								midiActiveFloat[60]=1;
							}
							if(midiActiveFloat[60]==1){
								p_lock[60][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
							}
						}	
                    } 
                }
                
                if(message.control==126){    
                    if(osc_rgbp_switch==0){
						midiActiveFloat[49]=0;
						midiActiveFloat[50]=0;
						midiActiveFloat[51]=0;
						if(abs(message.value/127.0f-p_lock[48][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[48]=1;
						} 
						if(midiActiveFloat[48]==1){
							p_lock[48][p_lock_increment]=message.value/127.0f;
						}	
                    }    
                    if(osc_rgbp_switch==1){
						midiActiveFloat[48]=0;
						midiActiveFloat[50]=0;
						midiActiveFloat[51]=0;
						if(abs(message.value/127.0f-p_lock[49][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[49]=1;
						} 
						if(midiActiveFloat[49]==1){
							p_lock[49][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_rgbp_switch==2){
						midiActiveFloat[48]=0;
						midiActiveFloat[49]=0;
						midiActiveFloat[51]=0;
						if(abs(message.value/127.0f-p_lock[50][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[50]=1;
						} 
						if(midiActiveFloat[50]==1){
							p_lock[50][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_rgbp_switch==3){
						midiActiveFloat[48]=0;
						midiActiveFloat[49]=0;
						midiActiveFloat[50]=0;
						if(abs(message.value/127.0f-p_lock[51][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[51]=1;
						} 
						if(midiActiveFloat[51]==1){
							p_lock[51][p_lock_increment]=message.value/127.0f;
						}
                    }  
                }
                
                if(message.control==127){
                    if(osc_m_rate_switch==0){
						midiActiveFloat[31]=0;
						midiActiveFloat[14]=0;
						midiActiveFloat[30]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[15][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[15]=1;
						} 
						if(midiActiveFloat[15]==1){
							p_lock[15][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}	
                    }
                    if(osc_m_rate_switch==1){
						midiActiveFloat[15]=0;
						midiActiveFloat[14]=0;
						midiActiveFloat[30]=0;
						if(abs((message.value-MIDI_MAGIC)/MIDI_MAGIC-p_lock[31][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[31]=1;
						} 
						if(midiActiveFloat[31]==1){
							p_lock[31][p_lock_increment]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
						}
                    }
                    
                    if(osc_m_rate_switch==2){
						midiActiveFloat[15]=0;
						midiActiveFloat[31]=0;
						midiActiveFloat[30]=0;
						if(abs(message.value/127.0f-p_lock[14][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[14]=1;
						} 
						if(midiActiveFloat[14]==1){
							p_lock[14][p_lock_increment]=message.value/127.0f;
						}
                    }
                    if(osc_m_rate_switch==3){
						midiActiveFloat[15]=0;
						midiActiveFloat[31]=0;
						midiActiveFloat[14]=0;
						if(abs(message.value/127.0f-p_lock[30][p_lock_increment])<CONTROL_THRESHOLD ){
							midiActiveFloat[30]=1;
						} 
						if(midiActiveFloat[30]==1){
							p_lock[30][p_lock_increment]=message.value/127.0f;
						}	
                    }
                    
                }
				if(message.control==58){
					if(message.value==127){
						for(int i=0;i<p_lock_number;i++){
							midiActiveFloat[i]=0;
							for(int j=0;j<p_lock_size;j++){
								p_lock[i][j]=0;
								
								p_lock[1][j]=.5;
								p_lock[8][j]=1.0;
						
								p_lock[17][j]=.5;
								p_lock[24][j]=1.0;
						
								p_lock[4][j]=.5;
								p_lock[11][j]=1.0;
						
								p_lock[20][j]=.5;
								p_lock[27][j]=1.0;
							}
						}
					}	
				}
            }
        }
    }
}
