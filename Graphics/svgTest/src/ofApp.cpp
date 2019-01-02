#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(255);
    object.setup("tri.svg");
    object.setColor(ofColor(0,200,50));
    //object.disableOutline();
    object.enableOutline();
    object.setLineWidth(0.10);
    object.setOutlineFill(false);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    object.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    object.draw();
    
    ofSetColor(255,0,0);
    ofDrawCircle(object.getLastPos(), 5);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    object.setScale(5000, 1.0,1.0); // always set scale
    object.setPosition(3000, ofVec2f(0,0), ofVec2f(0,0));
    object.setRotate(1000,0,0);
    object.setOutlinePlay(1000, 0.0f, 1.0f);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
