#include "ofApp.h"
#include "Poco/RegularExpression.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    maxHistory = 100; //Higher val smoother data
    
    flexVals.assign(maxHistory, 0.0);
    
    message = "";
    messageBuffer = "";
    
    // serial.setup("/dev/tty.usbserial-A702VZA8", 9600); //mouse input
    
    const string arduinoId = "/dev/tty.usbmodem1411"; //Open Terminal and type: ls /dev/tty.* //
    serial.setup(arduinoId, 9600);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (serial.available() > 0)
    {
        // we will keep reading until nothing is left
        while (serial.available() > 0)
        {
            // we'll put the incoming bytes into bytesReturned
            serial.readBytes(bytesReturned, NUM_BYTES);
            
            // if we find the splitter we put all the buffered messages
            //   in the final message, stop listening for more data and
            //   notify a possible listener
            // else we just keep filling the buffer with incoming bytes.
            if (*bytesReturned == '\n')
            {
                message = messageBuffer;
                messageBuffer = "";
                
                break;
            }
            else
            {
                if (*bytesReturned != '\r')
                    messageBuffer += *bytesReturned;
            }
            //cout << "  messageBuffer: " << messageBuffer << "\n";
        }
        
        // clear the message buffer
        memset(bytesReturned, 0, NUM_BYTES);
    }
    
    //cout << "Uno Output: " << message << endl;
    
    vector<string> input = ofSplitString(message, ",");
    
    
    flexVals.push_back(ofToInt(message));
    rawFlexVal = ofToInt(input.at(0));
    
    
    
    //Erase Vector Raw
    
    if (flexVals.size() > maxHistory) {
        
        flexVals.erase(flexVals.begin(), flexVals.begin()+1);
    }
    
    //Fill smooth vector for graph
    
    smoothFlexVals.push_back(smoothData(flexVals));
    
    
    if ( smoothFlexVals.size() > maxHistory ) {
        
        smoothFlexVals.erase(smoothFlexVals.begin(), smoothFlexVals.begin() + 1);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("Sensor Value: ", 20,20);
    
    int graphPosX = ofGetWidth() * .10;
    int graphPosY = ofGetHeight() * .10;
    int flexMinVal = -50;
    int flexMaxVal = 250;
    ofColor graphC = ofColor(50,230,200, 200);
    
    //Draw Raw Graph
    drawGraph(ofPoint(graphPosX, graphPosY), flexMinVal, flexMaxVal, flexVals, graphC);
    
    //Draw Smooth Graph
    int yOffSet = 250;
    drawGraph(ofPoint(graphPosX, graphPosY + yOffSet), flexMinVal, flexMaxVal, smoothFlexVals, graphC);
    
}

void ofApp::drawGraph(ofPoint pt, int max, int min, vector<int> values, ofColor color){
    
    ofPushMatrix();
    ofFill();
    ofSetColor(color);
    ofTranslate(pt.x, pt.y);
    
    int graphHeight = 200;
    int graphWidth = ofGetWidth() * .75;
    
    int gridNum = 5;
    int scaledMin = ofMap(min, min, max, 0, graphHeight);
    int scaledMax = ofMap(max, min, max, 0, graphHeight);
    
    for (int i = 0; i < gridNum; i++) {
        
        ofSetColor(255);
        ofLine(0, ofMap(i, 0, gridNum, scaledMin, scaledMax), graphWidth, ofMap(i, 0, gridNum, scaledMin, scaledMax));
        ofDrawBitmapString(ofToString(ofMap(i, 0, gridNum, min, max)), 0,ofMap(i, 0, gridNum, scaledMin, scaledMax));
    }
    
    //Value Shape//
    //average max history size of vector
    float avgVal;
    
    ofBeginShape();
    ofSetColor(color);
    
    for (int i = 0; i < maxHistory; i++){
        
        if( i == 0 ) ofVertex(i, graphHeight);
        
        ofVertex(i, ofMap(values[i], min, max, 0, graphHeight, true));
        
        avgVal = avgVal + values[i];
        
        if( i == maxHistory -1 ){
            
            ofVertex(i, graphHeight);
            ofDrawBitmapString(ofToString(values[i]), i,ofMap(values[i], min, max, 0, graphHeight,true));
            
        }
    }
    
    avgVal = avgVal / values.size();
    
    ofEndShape(false);
    
    //Average Value line
    ofSetColor(ofColor::hotPink);
    ofLine(0,ofMap(avgVal, min, max, 0, graphHeight,true) , maxHistory, ofMap(avgVal, min, max, 0, graphHeight,true));
    ofPopMatrix();
}

int ofApp::smoothData(vector<int> inputData) {
    
    float averageVal;
    
    for (int i = 0; i < maxHistory; i++)
    {
        averageVal += inputData[i];
        
    }
    
    averageVal = averageVal / inputData.size();
    
    return averageVal;
}
