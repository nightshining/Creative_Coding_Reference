#pragma once
#include "ofMain.h"
#include "constants.h"

class FibonacciCircle {
    
private:
    float mTouch;
    ofVec3f offset;
    float radius;
    float reverse;
    float age;
    float maxAge;
    ofVec3f speed;
    ofVec3f rotation;
    ofPoint pt;
    ofPoint prevPt;
    ofVec3f velocity;
    ofVec3f acceleration;
    float kRate;
    float minRadius;
    float maxVelocity;
    float maxRadius;
    float cutOff;
    bool kill;
public:
    FibonacciCircle(ofPoint origin, float radius, float _maxRadius, ofColor _startColor, ofPoint velocity = ofPoint(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)), float kRate = 15, float cutOff = 0.125, bool kill = true);
    
    void draw();
    void update(int _particleID);
    void setTouch(float touch);
    bool dead;
    void setNewColor(ofColor newColor);
    ofColor getCurrentColor();
    ofColor currentColor;
    float lerpTimer;
    int getFibonacci(int index);
    
};