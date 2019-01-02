#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
    string lastMessage;
    
};
