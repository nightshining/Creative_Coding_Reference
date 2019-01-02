#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    lastMessage = "";
    
    sender.setup("localhost", 9000);
    receiver.setup(9000);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        auto address = m.getAddress();
        
        if (address == "/treadmill") {
            auto string = m.getArgAsString(0);
            ofxJSON json(string);
            lastMessage = json.getRawString();
        }
    }
    
    // Send out some random data
    ofxJSON root, json;
    
    for (int i = 0; i < 16; i++) {
        ofxJSON data;
        string id = ofToString(i);
        
        data["speed"] = ofRandom(6, 20);
        data["distance"] = ofRandom(100, 200);
        json[id] = data;
    }
    root["data"] = json;
    
    ofxOscMessage msg;
    msg.setAddress("/treadmill");
    msg.addStringArg(root.getRawString(false));
    sender.sendMessage(msg, false);
    
}
