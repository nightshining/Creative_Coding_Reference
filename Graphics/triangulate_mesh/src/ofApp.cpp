#include "ofApp.h"

using namespace ofxCv;
using namespace cv;


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    ofSetLineWidth(0.001);
    
    cam.setup(640, 480);
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    //contourFinder.setInvert(true); // find black instead of white
    
    
    threshold = 10;
    trackHs = false;

    count = 0;

//    centerPoints.resize(5);
//    for(int i = 0; i < centerPoints.size(); i++){
//        centerPoints[i] = ofVec3f(0,0,0);
//    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    cam.update();
    if(cam.isFrameNew()) {
        contourFinder.setTargetColor(targetColor, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
    }
  

    // update voronoi
    if(pts.size() != count){
        count = pts.size();
        //triangulation.reset(); // mesh clear

    }
    
    

    

    
    for (int i = 0; i < pts.size(); i++){
        ofPoint p (contourFinder.getCenter(i).x,contourFinder.getCenter(i).y);
        pts[i] = p;
        
        vector<ofVec3f>& verts = triangulation.triangleMesh.getVertices();
        verts[i] = pts[i];

    }
    
    //for(unsigned int i = 0; i < verts.size(); i++){
        
        //        ofFloatColor c = ofColor::turquoise;
        //        c.a = i * 0.5;
        //        mesh.addColor(c);
        
        //verts[i] = pts[i] / liquidness * amplitude;
        //verts[i] = pts[i];
    //}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    cam.draw(0, 0);
    

    
    contourFinder.draw();
    
    ofPushMatrix();
    ofTranslate(8, 75);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(-3, -3, 64+6, 64+6);
    ofSetColor(targetColor);
    ofDrawRectangle(0, 0, 64, 64);
    ofPopMatrix();
    
    
    ofSetColor(255,0,0);
    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
  
    
    if(count < 1) return; /* IMPORTANT */
    
    

    for(unsigned int i = 0; i < pts.size(); ++i) {
        ofPushMatrix();
            ofFill();
            ofDrawCircle(pts[i].x, pts[i].y, 4);
        ofPopMatrix();
    }
    
    ofPushMatrix();
        ofNoFill();
        triangulation.draw();
    ofPopMatrix();
    
    
}
    


    


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        triangulation.reset();
    }
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
    
    pts.clear();
    triangulation.reset();
    targetColor = cam.getPixels().getColor(x, y);
    
    for (int i = 0; i < contourFinder.getContours().size(); i++){
        ofPoint p (contourFinder.getCenter(i).x,contourFinder.getCenter(i).y);
        pts.push_back(p);
        triangulation.addPoint(pts[i]);
    }
    
    triangulation.triangulate();

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
   // triangulation.triangulate();


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
