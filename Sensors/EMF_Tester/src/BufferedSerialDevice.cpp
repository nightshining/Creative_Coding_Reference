

#include "BufferedSerialDevice.h"


void BufferedSerialDevice::setup(int setSmoothing)
{
    
    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    
    ofLogNotice("BufferedSerialDevice::setup") << "Connected Devices: ";
    
    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("BufferedSerialDevice::setup") << "\t" << devicesInfo[i];
    }
    
    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 9600);
        
        if(success)
        {
            device.registerAllEvents(this);
            
            ofLogNotice("BufferedSerialDevice::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("BufferedSerialDevice::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("BufferedSerialDevice::setup") << "No devices connected.";
    }
    
    maxHistory = setSmoothing; //higher variable is smoother data
    rawX.resize(maxHistory);
    smoothX.resize(maxHistory);
    
}

void BufferedSerialDevice::exit()
{
    device.unregisterAllEvents(this);
}


void BufferedSerialDevice::onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args)
{
    // Buffers will show up here when the marker character is found.
    //SerialMessage message(args.getBuffer().toString(), "", 500);
    //serialMessages.push_back(message);
    
    
    //vector<string> input = ofSplitString(args.getBuffer().toString(), ",");
    
    //if (  input.size() == 4) {
        
        //modulus wraps int so if counter goes over 4 it goes back to 0
        //cout << input.at(counter%4) << endl;
        
      //  float tempX = ofToFloat(input.at(1));
        
        //rawX.push_back(tempX);
        
    //}
    
    //Make Vector//
    float tempX = ofToFloat(args.getBuffer().toString());
    rawX.push_back(tempX);
    
    
    
    //Erase
    if (rawX.size() > maxHistory) {
        
        rawX.erase(rawX.begin(), rawX.begin() + 1);
        
    }
    
    
}

void BufferedSerialDevice::onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    // SerialMessage message(args.getBuffer().toString(),
    //  args.getException().displayText(),
    //  500);
    // serialMessages.push_back(message);
}

float BufferedSerialDevice::smoothData(vector<float> inputData) {
    
    float averageVal;
    
    for (int i = 0; i < maxHistory; i++)
    {
        averageVal += inputData[i];
        
    }
    
    averageVal = averageVal / inputData.size();
    
    return averageVal;
}

//--------------------------------------------------------------
void BufferedSerialDevice::update(){
    
    
    
    //Set the Gyro Vec2f to smooth values
    bool clamp = true;
    float tempX = ofMap(smoothData(rawX), 0, 1023, 0.0, 1.0, clamp);
    
    serialXSet = tempX;
    
    //Fill smooth vector for graph
    smoothX.push_back(smoothData(rawX));
    
    
    if ( smoothX.size() > maxHistory ) {
        
        smoothX.erase(smoothX.begin(), smoothX.begin() + 1);
        
    }
    
    
}

float BufferedSerialDevice::getSerialX() {
    
    return serialXSet;
}


//--------------------------------------------------------------
void BufferedSerialDevice::debug(){
    

    ofSetColor(ofColor::whiteSmoke,255);
    
    ofDrawBitmapString("Normalized X: " + ofToString(getSerialX()), ofGetWidth() * .70, ofGetHeight() * .10);
    
    
    drawGraph("Raw X Value", ofPoint(ofGetWidth() * .10, ofGetHeight() * .20), 0, 1023, rawX);
    
    drawGraph("Smooth X Value", ofPoint(ofGetWidth() * .10, ofGetHeight() * .60), 0, 1023, smoothX);
    
    
}

void BufferedSerialDevice::drawGraph(string label, ofPoint pt, int max, int min, vector<float> values){
    
    ofDrawBitmapString(label, pt.x + 50, pt.y);
    
    ofPushMatrix();
    {
        ofFill();
        ofSetColor(255,255,255,127);
        ofTranslate(pt.x, pt.y);
        ofBeginShape();
        
        int graphHeight = 200;
        
        int gridNum = 5;
        int scaledMin = ofMap(min, min, max, 0, graphHeight);
        int scaledMax = ofMap(max, min, max, 0, graphHeight);
        
        int graphWidth = 5;
        
        
        ofPushStyle();
        //ofSetColor(ofColor::turquoise);
        for (int i = 0; i < maxHistory; i++){
            
            if( i == 0 ) ofVertex(i, graphHeight);
            
            ofVertex(i * graphWidth, ofMap(values[i], min, max, 0, graphHeight, true));
            
            if( i == maxHistory -1 ){
                ofVertex(i * graphWidth, graphHeight);
                ofDrawBitmapString(ofToString(values[i]), i,ofMap(values[i], min, max, 0, graphHeight,true));
            }
        }
        ofPopStyle();
        
        ofEndShape(false);
        ofSetColor(ofColor::green);
        for (int i = 0; i < gridNum; i++) {
            
            ofDrawLine(0, ofMap(i, 0, gridNum, scaledMin, scaledMax), maxHistory * graphWidth, ofMap(i, 0, gridNum, scaledMin, scaledMax));
            ofDrawBitmapString(ofToString(ofMap(i, 0, gridNum, min, max)), 0,ofMap(i, 0, gridNum, scaledMin, scaledMax));
        }
        
        
    }
    ofPopMatrix();
}
