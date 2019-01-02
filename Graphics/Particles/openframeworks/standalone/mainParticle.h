//
//  mainParticle.h
//  booth_UI_graphics
//
//  Created by fakelove on 3/10/14.
//
//

#pragma once
#include "ofMain.h"
//#include "auxParticle.h"


class mainParticle{
    
public:
    mainParticle();
    
    void setAttractPoints( ofPoint * attract );
    
    void reset();
    void update(float framerateMult,
                float attractScale, float wanderScale,
                float minDist, float maxDist,
                float tScale, float complexity, float noiseScale, float smoothing);
    void draw();
    
    ofVec3f getField3d(ofVec3f position, float tScale, float complexity);
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    ofPoint * attractPoint;

    vector<ofPoint> points;

    float trailLength;

};