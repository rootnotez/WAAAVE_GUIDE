
#include "GuiApp.h"

#include "iostream"

#define MIDI_MAGIC 63.50f
#define PARAMETER_THRESHOLD .035f

const int arrayLength=16;
float midiCC[arrayLength];
bool coutMidiSwitch=0;

const int pastFramesSize=120;

float sliderWidth=80;
float yPosAdjust=0;

bool debugOn=true;

//testing out the node closing thingy
static int nodeToClose=-1;
static int currentNode=-1;

void GuiApp::setup(){
	
	ofBackground(0);

	gui.setup();
	midiSetup();
	allArrayClear();
	
}

//--------------------------------------------------------------

void GuiApp::allArrayClear(){
//should we clear all the midiGui switches here too?/ probably...
	for(int i=0;i<PARAMETER_ARRAY_LENGTH;i++){
		//BLOCK1
		
		//input adjust and mix
		ch1Adjust[i]=0.0f;
		ch1AdjustMidiActive[i]=0;
		

		
		
	}

}

//--------------------------------------------------------------
void GuiApp::update(){
	midibiz();
}

//--------------------------------------------------------------
//maps midi messages in to parameters of each gui
//something to think about: do we want to keep all of the paramters at -1 to 1 in here?
//if we want to be able to scale things in and out then we would want to have coefficient arrays
//as well, and bring the coefficient arrays into here to test

//what to do here: inMessage[] maps to midiCC[]
void GuiApp::midi2Gui(bool midiActive[], float params[], bool midiSwitch) {
	//so lets test the midi2gui thing;
	if (midiSwitch == 1) {
		//test for potentiometer latching

		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			if (abs(midiCC[i] - params[i]) < PARAMETER_THRESHOLD) {
				midiActive[i] = 1;
			}
		}

		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			if (midiActive[i] == 1) {
				params[i] = midiCC[i];
				if( abs(params[i])<.008 ){params[i]=0.0;}//zero shit out
				//might want to 
			}
		}


	}//endifMIDIGUI TRUE
	if (midiSwitch == 0) {
		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			midiActive[i] = 0;
		}
	}//endifMIDIGUI FALSE
}

//--------------------------------------------------------------
void GuiApp::draw(){

	int debugAdjust=0;
	
	if(debugOn==true){
		debugAdjust=40;
	}
	float windowWidthThird=320.0;	
	float windowWidthHalf=420;
	

	auto mainSettings = ofxImGui::Settings();
	//change header colors
    ImGui::StyleColorsDark();

	gui.begin();
	
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGuiWindowFlags window_flags=0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	//window_flags |= ImGuiWindowFlags_NoResize;
	
	
	//strangely enough, when i switched to ImGui::Begin from ImGui::BeginWindow, that seemed to really
	//bonk up the fontGlobalScale thing...
	io.FontGlobalScale=2.0f;
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	

	//ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(.8f,1.0f,.15f));
	
	bool value=true;
	bool* p_open =&value;
	
	
	ImGui::SetNextWindowSize(ImVec2(1280,720-debugAdjust),ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0,0),ImGuiCond_Once);

	if( ImGui::Begin("*--++--++--++--++--++--++--++--G*R*A*V*I*T*Y**W*A*A*A*V*E*S v 1.0 --++--++--++--++--++--++--*", p_open ,window_flags)   ) {
		ImGui::PushItemWidth(windowWidthHalf);
        if (ImGui::BeginTabBar("GLOBALTAB"))
        {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(.8f, 0.5f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(.8f, 0.6f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(.8f, 0.7f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(.8f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(.8f, 0.5f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(.8f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(.8f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, (ImVec4)ImColor::HSV(.8f, 0.3f, 0.2f));
			ImGui::PushStyleColor(ImGuiCol_Text,(ImVec4)ImColor::HSV(.2f,.25f,1.0f));
			
			ImGui::PushStyleColor(ImGuiCol_Tab, (ImVec4)ImColor::HSV(.8f,.5f,.5f));
			ImGui::PushStyleColor(ImGuiCol_TabActive, (ImVec4)ImColor::HSV(.8f,.9f,.9f));
			ImGui::PushStyleColor(ImGuiCol_TabHovered, (ImVec4)ImColor::HSV(.8f,.7f,.7f));
				
			
			if (ImGui::BeginTabItem("BLOCK_1")){
					
				if (ImGui::BeginTabBar("BLOCK1_subfolders"))
				{
					
					if (ImGui::BeginTabItem("ch1 adjust")){
						const char* items0[] = { "input1","input2" };
						static int item_ch1InputSelect = 0;
						ImGui::Combo("input   ##ch1", &item_ch1InputSelect, items0, IM_ARRAYSIZE(items0));
						ch1InputSelect=item_ch1InputSelect;
						
						ImGui::SameLine();
						ImGui::Checkbox("midi/gui      ##ch1Adjust", &ch1AdjustMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset   ##ch1Adjust",&ch1AdjustReset);
						if (ch1AdjustReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								ch1Adjust[i] = 0.0f;
								ch1AdjustMidiActive[i] = 0;
							}
							ch1AdjustReset = 0;
							
						}
						midi2Gui(ch1AdjustMidiActive, ch1Adjust, ch1AdjustMidiGui);
						
						ImGui::Separator();
						ImGui::SliderFloat("x <->   ##ch1", &ch1Adjust[0], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("y <->   ##ch1", &ch1Adjust[1], -1.0f, 1.0f);
						
						
						ImGui::Separator();
						ImGui::Checkbox("h mirror        ##ch1",&ch1HMirror);
							
						
						ImGui::EndTabItem();
					}
					
					
					if (ImGui::BeginTabItem("this tab has nodes")){		
						//this is how to make nodes auto close
						if(nodeToClose==0)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("example node 1"))
						{
							if(currentNode==0)
							{
								ImGui::Text("here is example node 1");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=0;
							}
							ImGui::TreePop();
						}
						ImGui::Separator();
						if(nodeToClose==1)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("example node 2"))
						{
							if(currentNode==1)
							{
								ImGui::Text("here is example node 2");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=1;
							}
							ImGui::TreePop();
						}
									
						ImGui::EndTabItem();
					}
	
					ImGui::EndTabBar();
				}
				
				ImGui::EndTabItem();
				
			}//end block1tabItem
			
			
		    ImGui::PopStyleColor(12);

        	ImGui::EndTabBar();
        	
        }//end global tab
		
		ImGui::PopItemWidth();	
	}
	//ImGui::PopStyleColor(1);
	
	//ImGui::PopItemWidth();
	
	ImGui::End();

	gui.end();
}

//--------------------------------------------------------------
void GuiApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void GuiApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void GuiApp::keyPressed(int key) {
	/*
    if (key == 'a') {tweakHue += .01; cout<<"hue = "<<tweakHue<<endl;}
    if (key == 'z') {tweakHue -= .01; cout<<"hue = "<<tweakHue<<endl;}
    
    if (key == 's') {tweakSat += .01; cout<<"sat = "<<tweakSat<<endl;}
    if (key == 'x') {tweakSat -= .01; cout<<"sat = "<<tweakSat<<endl;}
    */
   
    //if(key=='0'){coutMidiSwitch=!coutMidiSwitch;}
    
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key) {
}
//--------------------------------------------------------------
void GuiApp::midiSetup(){
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual 		port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
	
}
//--------------------------------------------------------------
void GuiApp::midibiz(){
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
	
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                
                //How to Midi Map
                //uncomment the line that says cout<<message control etc
                //run the code and look down in the console
                //when u move a knob on yr controller keep track of the number that shows up
                //that is the cc value of the knob
                //then go down to the part labled 'MIDIMAPZONE'
                //and change the numbers for each if message.control== statement to the values
                //on yr controller
                
                if(coutMidiSwitch==1){
               		//cout << "message.control"<< message.control<< endl;
                	//cout << "message.value"<< message.value<< endl;
                }
				
				if(message.control>15 && message.control<24){
                    midiCC[message.control-16]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    if(coutMidiSwitch==1){
                    cout << "midiCC[message.control-16] "<<midiCC[message.control-16]<< endl;
                    cout << "message.value"<< message.value<< endl;
                    }
                }
                
                if(message.control>119 && message.control<128){
                    midiCC[message.control-120+8]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    if(coutMidiSwitch==1){
                    cout << "midiCC[message.control-120+8] "<<midiCC[message.control-120+8]<< endl;
                    cout << "message.value"<< message.value<< endl;
                    }
                }
				
                /* the nanostudio kontrols
                //c1 maps to fb0 hue attenuation
                if(message.control==20){
                    c1=(message.value-63.0)/63.0;
                   //  c1=(message.value)/127.00;
                    
                }
                
   				}
                */
             
			}//endifmessagestatus==
		}//endifmessagestatus<
	}//endfori	
}//endmidibiz
//-----------------------------------------------------------------------------------
void GuiApp::resetAll(){

}

