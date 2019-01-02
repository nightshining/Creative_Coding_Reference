//
//  Ball.h
//  particleEngine1
//
//  Created by Mary Scahill on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#import "ofMain.h"

enum pType { SPHERE , LINES, CUBE, TRIANGLE, MESHER };

class Particle{

private:

    ofVec3f offset;
    float radius;
    float age;
    float maxAge;
    ofVec3f speed;
    ofColor startColor, endColor, currentColor;
    ofVec3f rotation;
    ofPoint pt;
    ofPoint prevPt;
    
    bool isDragging;
    
    ofVec3f velocity;
    ofVec3f acceleration;
    ofVec3f gravity; //y force
    ofVec3f wind; //x force
    ofVec3f turbAmt; //noise for wind or gravity
    ofVec3f turbSpeed; //turb speed
    ofVec3f friction; //slow down force
    ofVec3f drag; //slow down force
    
    float attractionStrength;
    
    pType type;
    
    int randomSeed;
    vector<ofPoint> meshPts;

    
public:
    Particle(ofPoint origin, int _maxSpeed, int _maxSize, int _maxAge, ofColor _startColor, ofColor _endColor);

    void draw(pType _type);
    void update(int _particleID, ofPoint attractForce, float maxVelocity);
    ofPoint getPoint();
    void moveTo(int, int);
    ofPoint computeAttraction(ofPoint attractor);
    bool dead;
    
    bool isInside(ofRectangle dragBox);
    
    void applyForce(ofVec3f force);
    void computeFriction();
    

    bool bIsDead();
    float getMass();
    void setGravity(float _gravity);
    void setWind(float _wind);
    void setAttraction(float _attraction);
    void setTurbAmt(ofVec2f _turbAmt);
    void setTurbSpeed(ofVec2f _turbSpeed);

 };

