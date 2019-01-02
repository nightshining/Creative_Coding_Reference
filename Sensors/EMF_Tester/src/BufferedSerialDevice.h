


#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


class BufferedSerialDevice
{
public:
    void setup(int setSmoothing);
    void update();
    void debug();
    
    void exit();
    float getSerialX();
    
    void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
    void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
    
    ofx::IO::BufferedSerialDevice device;
    
    
    private :
    
    int maxHistory;
    vector<float> rawX;
    vector<float> smoothX;
    
    float serialXSet;
    
    
    float smoothData(vector<float> inputData);
    
    //View Data
    void drawGraph(string label, ofPoint pt, int max, int min, vector<float> values);
    
    
};
