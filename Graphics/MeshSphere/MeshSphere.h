#include "ofMain.h"

class Sphere {
    
    
    ofVec3f pos;
    ofMesh mesh;
    
//--------------------------------------------------------------
void setup(){
    
    ofBackground(ofColor::black);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    const float size = 100;
    const float alpha = 0.08;
    
    const int total = 5000;
    const float azimuth = 128.0 * PI / total;
    const float inclination = PI / total;
    const float radius = 160.0f;
    
    ofVec3f center = ofVec3f(ofGetWidth()*0.5, ofGetHeight()*0.5, 0.0);
    
    for (int i = 0; i < total; ++i) {
        
        float x = radius * sin( inclination * i ) * cos( azimuth * i );
        float y = radius * cos( inclination * i );
        float z = radius * sin( inclination * i ) * sin( azimuth * i );
        
        ofVec3f vec = ofVec3f(x,y,z);
        mesh.addVertex(vec);
        ofFloatColor c = ofFloatColor::whiteSmoke;
        c.a = ofMap(i, 0, total, 50, 255, true);
        mesh.addColor(c);
        
    }
    
    
    pos = ofVec3f(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
}


//--------------------------------------------------------------
void draw(){
    
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(pos);
    float t = ofGetElapsedTimef() * 10.0f;
    ofRotateX(t);
    ofRotateY(t);
    ofRotateZ(t);
    mesh.draw();
    ofPopMatrix();
    ofPopStyle();
    
    
}
    
}

