#pragma once
#include "ofMain.h"
#include "constants.h"

class NormalParticle {
    
private:
    
    float age;
    ofVec3f speed;
    ofVec3f velocity;
    ofVec3f acceleration;
    ofVec3f pt;
    ofVec3f pos;
    ofMesh* shape;
    bool kill;
public:
    NormalParticle(ofVec3f origin, ofVec3f vel,  ofMesh* dot);
    
    void draw();
    void update(int _particleID);
    bool dead;
    void setNewColor(ofColor newColor);
    ofColor getCurrentColor();
    ofColor currentColor;
    float lerpTimer;
    
    
};