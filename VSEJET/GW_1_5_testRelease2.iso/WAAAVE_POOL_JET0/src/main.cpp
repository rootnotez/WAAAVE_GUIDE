#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	//for proper shader running we might need to
	//explicitly set shaders here using
	//.setGLVersion(int major, int minor)
	//do we want to try and create different settings for each window??
	ofGLFWWindowSettings settings;
	
	settings.setGLVersion(4,6);

	//OUTPUT WINDOW
	
	settings.setSize(1280, 720);
	//make sure to change this for releases
	settings.setPosition(glm::vec2(1280,0));
	//make sure to change this when releaseing!
	//settind different positions for development mode b/c i like the larger screen
	//settings.setPosition(glm::vec2(1920,0));
	settings.decorated=false;
	//settings.decorated=true;
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	
	
	
	shared_ptr<ofApp> mainApp(new ofApp);

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
