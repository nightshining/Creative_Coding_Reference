//
//  particleManager.h
//  booth_UI_graphics
//
//  Created by fakelove on 3/11/14.
//
//

#pragma once

#include "mainParticle.h"




class particleManager {
public:
    void setup(int _nParticles, int _trailLength);
    void update();
    void draw(ofColor meshCol, float alpha);
    
    vector<mainParticle*> particles;
    
    float minDist, maxDist;
    float attractScale, wanderScale;
    float tScale;
    float complexity;
    float noiseScale;
    float smoothing;
    float breakoutScale;
    
    ofMesh mesh;
    
    int nParticles;
    int trailLength;
    
    ofPoint orbitOrigin;
    float xorig;
    float yorig;
    float radius;
    float speed;
    float initialAngle;
    float direction;
    
    ofImage grid;
    
    float texX, texY;
    
    float framerateMult;
};