#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0);
    
    enabled = false;
    
    ofAddListener(eventObject.triggerOn,  this, &ofApp::triggerOn );
    ofAddListener(eventObject.triggerOff, this, &ofApp::triggerOff);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawBitmapString(floatMsg,20,20);
    ofDrawBitmapString(intMsg,20,40);
    ofDrawBitmapString("click to enable/disable events",20,60);
}

void ofApp::triggerOn(bool & b){
    //floatMsg     = "newFloat event:  " + ofToString(f);
    
    cout << "Trigger On: " << b << endl;
}

//--------------------------------------------------------------
void ofApp::triggerOff(bool & b){
    //intMsg         = "newInt   event:  " + ofToString(i);
    cout << "Trigger Off: " << b << endl;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(enabled)
        eventObject.disable();
    else
        eventObject.enable();
    
    enabled=!enabled;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
