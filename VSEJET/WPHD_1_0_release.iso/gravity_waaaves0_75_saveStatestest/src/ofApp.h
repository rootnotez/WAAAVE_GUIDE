#pragma once

#include "ofMain.h"
#include "GuiApp.h"

#define ROOT_THREE 1.73205080757

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		
		
		shared_ptr<GuiApp> gui;
	
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
	ofVideoGrabber input2;

	//framebuffers
	void framebufferSetup();
	ofFbo framebuffer1;
	ofFbo framebuffer2;
	ofFbo framebuffer3;

	//shaders
	ofShader shader1;
	ofShader shader2;
	ofShader shader3;
	
	
	//COEFFICIENTS
	//mix and key coefficients
	float mixAmountC=2.0;
	float keyC=1.0;//use for r g b value
	float keyThresholdC=ROOT_THREE+.001;
	
	//BLOCK 1
	
	//ch1 adjust coefficients
	float ch1XDisplaceC=-640.0;//make x negative for better intuitive controls
	float ch1YDisplaceC=480.0;
	float ch1ZDisplaceC=1.0;
	float ch1RotateC=PI;
	float ch1PosterizeC=15.0;
	float ch1KaleidoscopeAmountC=21;
	float ch1KaleidoscopeSliceC=PI;
	
	float ch1FilterRadiusC=9.0;
	float ch1SharpenAmountC=1.0;
	
	//ch2 adjust coefficients
	float ch2XDisplaceC=-640.0;//make x negative for better intuitive controls
	float ch2YDisplaceC=480.0;
	float ch2ZDisplaceC=1.0;
	float ch2RotateC=PI;
	float ch2PosterizeC=15.0;
	float ch2KaleidoscopeAmountC=21;
	float ch2KaleidoscopeSliceC=PI;
	float ch2FilterRadiusC=9.0;
	float ch2SharpenAmountC=1.0;
	
	//fb1 geo1 coefficiens
	float fb1XDisplaceC=-80;
	float fb1YDisplaceC=80;
	float fb1ZDisplaceC=.5;
	float fb1RotateC=PI;
	float fb1ShearMatrix1C=.25;
	float fb1ShearMatrix2C=-.25;
	float fb1ShearMatrix3C=.25;
	float fb1ShearMatrix4C=.25;
	float fb1KaleidoscopeAmountC=21;
	float fb1KaleidoscopeSliceC=PI;
	
	//fb1 color coefficients
	float fb1HueOffsetC=.25;
	float fb1SaturationOffsetC=.25;
	float fb1BrightOffsetC=.25;
	float fb1HueAttenuateC=.25;
	float fb1SaturationAttenuateC=.25;
	float fb1BrightAttenuateC=.25;
	float fb1HuePowmapC=.1;
	float fb1SaturationPowmapC=.1;
	float fb1BrightPowmapC=.1;			
	float fb1HueShaperC=1.0;
	float fb1PosterizeC=15.0;
	
	//fb1 filters coefficients
	float fb1FilterRadiusC=9.0;
	float fb1SharpenAmountC=.6;
	float fb1TemporalFilterAmountC=2.0;
	
	
	//BLOCK 2
			
	//block2Input adjust coefficients
	float block2InputXDisplaceC=-640.0;//make x negative for better intuitive controls
	float block2InputYDisplaceC=480.0;
	float block2InputZDisplaceC=1.0;
	float block2InputRotateC=PI;
	float block2InputPosterizeC=15.0;
	float block2InputKaleidoscopeAmountC=21;
	float block2InputKaleidoscopeSliceC=PI;
	float block2InputFilterRadiusC=9.0;
	float block2InputSharpenAmountC=1.0;
	
	//fb2 geo1 coefficiens
	float fb2XDisplaceC=-80;
	float fb2YDisplaceC=80;
	float fb2ZDisplaceC=.5;
	float fb2RotateC=PI;
	float fb2ShearMatrix1C=.25;
	float fb2ShearMatrix2C=-.25;
	float fb2ShearMatrix3C=.25;
	float fb2ShearMatrix4C=.25;
	float fb2KaleidoscopeAmountC=21;
	float fb2KaleidoscopeSliceC=PI;
	
	//fb2 color coefficients
	float fb2HueOffsetC=.25;
	float fb2SaturationOffsetC=.25;
	float fb2BrightOffsetC=.25;
	float fb2HueAttenuateC=.25;
	float fb2SaturationAttenuateC=.25;
	float fb2BrightAttenuateC=.25;
	float fb2HuePowmapC=.1;
	float fb2SaturationPowmapC=.1;
	float fb2BrightPowmapC=.1;			
	float fb2HueShaperC=1.0;
	float fb2PosterizeC=15.0;
	
	//fb2 filters coefficients
	float fb2FilterRadiusC=9.0;
	float fb2SharpenAmountC=.6;
	float fb2TemporalFilterAmountC=2.0;
	
	//BLOCK3
	
	//block1 geo1 coefficiens
	float block1XDisplaceC=-1280;
	float block1YDisplaceC=720;
	float block1ZDisplaceC=1.0;
	float block1RotateC=PI;
	float block1ShearMatrix1C=1;
	float block1ShearMatrix2C=-1;
	float block1ShearMatrix3C=1;
	float block1ShearMatrix4C=1;
	float block1KaleidoscopeAmountC=21;
	float block1KaleidoscopeSliceC=PI;
	
	//block1 filters coefficients
	float block1FilterRadiusC=9.0;
	float block1SharpenAmountC=1.0;
	float block1TemporalFilterAmountC=2.0;
	float block1DitherC=15.0;
	
	//block2 geo1 coefficiens
	float block2XDisplaceC=-1280;
	float block2YDisplaceC=720;
	float block2ZDisplaceC=1.0;
	float block2RotateC=PI;
	float block2ShearMatrix1C=1;
	float block2ShearMatrix2C=-1;
	float block2ShearMatrix3C=1;
	float block2ShearMatrix4C=1;
	float block2KaleidoscopeAmountC=21;
	float block2KaleidoscopeSliceC=PI;
	
	//block2 filters coefficients
	float block2FilterRadiusC=9.0;
	float block2SharpenAmountC=1.0;
	float block2TemporalFilterAmountC=2.0;
	float block2DitherC=15.0;
	
	//mix coefficients
	float matrixMixC=6.0;
	
	
	
	//lfos
	float lfo(float amp, float rate,int shape);
	void lfoUpdate();
	float lfoRateC=.15;
	
	//BLOCK 1
	float ch1XDisplaceTheta=0;
	float ch1YDisplaceTheta=0;
	float ch1ZDisplaceTheta=0;
	float ch1RotateTheta=0;
	float ch1HueAttenuateTheta=0;
	float ch1SaturationAttenuateTheta=0;
	float ch1BrightAttenuateTheta=0;
	float ch1KaleidoscopeSliceTheta=0;
	
	float ch2MixAmountTheta=0;
	float ch2KeyThresholdTheta=0;
	float ch2KeySoftTheta=0;
	
	float ch2XDisplaceTheta=0;
	float ch2YDisplaceTheta=0;
	float ch2ZDisplaceTheta=0;
	float ch2RotateTheta=0;
	float ch2HueAttenuateTheta=0;
	float ch2SaturationAttenuateTheta=0;
	float ch2BrightAttenuateTheta=0;
	float ch2KaleidoscopeSliceTheta=0;
	
	float fb1MixAmountTheta=0;
	float fb1KeyThresholdTheta=0;
	float fb1KeySoftTheta=0;
	
	float fb1XDisplaceTheta=0;
	float fb1YDisplaceTheta=0;
	float fb1ZDisplaceTheta=0;
	float fb1RotateTheta=0;
	
	float fb1ShearMatrix1Theta=0;
	float fb1ShearMatrix2Theta=0;
	float fb1ShearMatrix3Theta=0;
	float fb1ShearMatrix4Theta=0;
	float fb1KaleidoscopeSliceTheta=0;
	
	float fb1HueAttenuateTheta=0;
	float fb1SaturationAttenuateTheta=0;
	float fb1BrightAttenuateTheta=0;
	
	
	//BLOCK 2
	float block2InputXDisplaceTheta=0;
	float block2InputYDisplaceTheta=0;
	float block2InputZDisplaceTheta=0;
	float block2InputRotateTheta=0;
	float block2InputHueAttenuateTheta=0;
	float block2InputSaturationAttenuateTheta=0;
	float block2InputBrightAttenuateTheta=0;
	float block2InputKaleidoscopeSliceTheta=0;
	
	float fb2MixAmountTheta=0;
	float fb2KeyThresholdTheta=0;
	float fb2KeySoftTheta=0;
	
	float fb2XDisplaceTheta=0;
	float fb2YDisplaceTheta=0;
	float fb2ZDisplaceTheta=0;
	float fb2RotateTheta=0;
	
	float fb2ShearMatrix1Theta=0;
	float fb2ShearMatrix2Theta=0;
	float fb2ShearMatrix3Theta=0;
	float fb2ShearMatrix4Theta=0;
	float fb2KaleidoscopeSliceTheta=0;
	
	float fb2HueAttenuateTheta=0;
	float fb2SaturationAttenuateTheta=0;
	float fb2BrightAttenuateTheta=0;
	
    //BLOCK 3	
	
	//block1 geo
	float block1XDisplaceTheta=0;
	float block1YDisplaceTheta=0;
	float block1ZDisplaceTheta=0;
	float block1RotateTheta=0;
	
	float block1ShearMatrix1Theta=0;
	float block1ShearMatrix2Theta=0;
	float block1ShearMatrix3Theta=0;
	float block1ShearMatrix4Theta=0;
	float block1KaleidoscopeSliceTheta=0;
	
	//block1 colorize
	float block1ColorizeHueBand1Theta=0;
	float block1ColorizeSaturationBand1Theta=0;
	float block1ColorizeBrightBand1Theta=0;
	float block1ColorizeHueBand2Theta=0;
	float block1ColorizeSaturationBand2Theta=0;
	float block1ColorizeBrightBand2Theta=0;
	float block1ColorizeHueBand3Theta=0;
	float block1ColorizeSaturationBand3Theta=0;
	float block1ColorizeBrightBand3Theta=0;
	float block1ColorizeHueBand4Theta=0;
	float block1ColorizeSaturationBand4Theta=0;
	float block1ColorizeBrightBand4Theta=0;
	float block1ColorizeHueBand5Theta=0;
	float block1ColorizeSaturationBand5Theta=0;
	float block1ColorizeBrightBand5Theta=0;
	
	//block2 geo
	float block2XDisplaceTheta=0;
	float block2YDisplaceTheta=0;
	float block2ZDisplaceTheta=0;
	float block2RotateTheta=0;
	
	float block2ShearMatrix1Theta=0;
	float block2ShearMatrix2Theta=0;
	float block2ShearMatrix3Theta=0;
	float block2ShearMatrix4Theta=0;
	float block2KaleidoscopeSliceTheta=0;
	
	//block2 colorize
	float block2ColorizeHueBand1Theta=0;
	float block2ColorizeSaturationBand1Theta=0;
	float block2ColorizeBrightBand1Theta=0;
	float block2ColorizeHueBand2Theta=0;
	float block2ColorizeSaturationBand2Theta=0;
	float block2ColorizeBrightBand2Theta=0;
	float block2ColorizeHueBand3Theta=0;
	float block2ColorizeSaturationBand3Theta=0;
	float block2ColorizeBrightBand3Theta=0;
	float block2ColorizeHueBand4Theta=0;
	float block2ColorizeSaturationBand4Theta=0;
	float block2ColorizeBrightBand4Theta=0;
	float block2ColorizeHueBand5Theta=0;
	float block2ColorizeSaturationBand5Theta=0;
	float block2ColorizeBrightBand5Theta=0;
	
	
	//matrix mix
	float matrixMixBgRedIntoFgRedTheta=0;
	float matrixMixBgGreenIntoFgRedTheta=0;
	float matrixMixBgBlueIntoFgRedTheta=0;
	
	float matrixMixBgRedIntoFgGreenTheta=0;
	float matrixMixBgGreenIntoFgGreenTheta=0;
	float matrixMixBgBlueIntoFgGreenTheta=0;
	
	float matrixMixBgRedIntoFgBlueTheta=0;
	float matrixMixBgGreenIntoFgBlueTheta=0;
	float matrixMixBgBlueIntoFgBlueTheta=0;
	
	//final mix
	float finalMixAmountTheta=0;
	float finalKeyThresholdTheta=0;
	float finalKeySoftTheta=0;
	
	//hypercube
	void hypercube_draw();
    
    float hypercube_theta=0;
    float hypercube_phi=0;
    float hypercube_r=0.0;
    
    float hypercube_x[8];
    float hypercube_y[8];
    float hypercube_z[8];
    
    float hypercube_color_theta=0;
    
    //line
    void line_draw();
    float line_theta=0;
    float line_phi=0;
    float line_eta=0;

	//sevenStar
	void sevenStar1Setup();
	void sevenStar1Draw();

	//try to add this to .h
	//sevenstar1 biz
	static const int reps = 7;
	ofVec2f points[reps];
	//i don't think this would be every time? but should double check
	//this one increments 3 = floor[7/2] to 8 reps
	static const int reps1 = reps + 1;
	ofVec2f points1[reps1];

	ofVec2f position1;
	float increment1 = 0;
	int index1 = 0;

	float acceleration1 = .002;
	float threshold = .125;

	//this one increments 2, will work for any odd star
	ofVec2f points2[reps];
	ofVec2f position2;
	float increment2 = 0;
	int index2 = 0;

	float acceleration2 = .00125;

	float thetaHue1;
	float thetaHue2;
	float thetaSaturation1;
	float thetaChaos;

	float hueInc1 = .021257;
	float hueInc2 = .083713;
	float saturationInc1 = .00612374;
	float chaosInc = .0001;

	//lissaBall
	void drawSpiralEllipse();

	float spiralTheta1 = 0;
	float spiralRadius1 = 0;

	float radius1Inc = .75;
	float spiralTheta1Inc = .07;

	float spiralTheta2 = 0;
	float spiralRadius2 = 0;

	float radius2Inc = .55;
	float spiralTheta2Inc = .08;

	float spiralTheta3 = 0;
	float spiralRadius3 = 0;

	float radius3Inc = .65;
	float spiralTheta3Inc = .05;
};
