#pragma once

#include "ofMain.h"
#include "Particle.h"

#define ParticleSize 500

class ParticleEmitter : public ofBaseApp{
private:
    int centerX;
    int centerY;
    ofPoint origin;
    float rotation;
    ofColor startColor, endColor;
    pType type;
    
public:
    void setup(ofPoint origin, int maxSpeed, int maxSize, int maxAge, ofColor _startColor, ofColor _endColor);
    void update(float maxSpeed, int maxSize, int maxAge);
    void setForces(float _gravity, float _wind, float _attraction, ofVec2f _turbSpeed, ofVec2f _turbAmt);
    void draw(int x, int y, pType _type);
    void setOrigin(ofPoint _origin);
    void setColors(ofColor _startColor, ofColor _endColor);
    
    Particle* p[ParticleSize];
};



