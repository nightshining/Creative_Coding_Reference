#pragma once

#include "ofMain.h"
#define NUM_BYTES 1

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    
    vector<int> flexVals;
    
    ofSerial serial;
    
    void drawGraph(ofPoint pt, int max, int min, vector<int> values, ofColor color);
    
    int maxHistory;
    
    int rawFlexVal;
    
    int smoothData(vector<int> inputData);
    
    vector<int> smoothFlexVals;
    
    string		serMessage;
    
    string			messageBuffer;
    unsigned char	bytesReturned[NUM_BYTES];
    bool			continuousRead;
    bool			bWriteByte;
    
    string message;
    
    
    
};