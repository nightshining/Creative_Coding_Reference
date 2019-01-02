#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ofxGui.h"



class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
    ofEasyCam camera;


    
    ofImage scratch;
    
    ofLight pointLight;
    ofMaterial material;
    
    ofFbo fbo1;
    
    //float maxParticleSpeed, maxParticleAge, maxParticleSize;
    
    ofxPanel gui;
    ofParameter<int> maxParticleSpeed;
    ofParameter<int> maxParticleAge;
	ofParameter<int> maxParticleSize;
    ofParameter<bool> addBlend;
    ofParameter<float> gravity, wind, attraction;
    ofParameter<float> fadeAmt;
    ofParameter<bool> pointLightSwitch;
    ofParameter<bool> AlphaBlendSwitch;
    ofParameter<bool> cameraSwitch;
    ofParameter<bool> trailEnable;
    ofParameter<int> particleType;
    ofParameter<float> turbSpeedX, turbSpeedY, turbAmtX, turbAmtY;
    
    float colorCount;
    
    ParticleEmitter emitter;
    
};
