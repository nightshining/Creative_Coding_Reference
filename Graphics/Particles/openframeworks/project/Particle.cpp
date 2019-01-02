//
//  Particle.cpp
//  particleEngine1
//
//  Created by Mary Scahill on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Particle.h"

Particle::Particle(ofPoint origin, int _maxSpeed, int _maxSize, int _maxAge, ofColor _startColor, ofColor _endColor){

    startColor = _startColor;
    endColor = _endColor;
    currentColor = _startColor;
    
    pt = origin;
    prevPt = origin;
    offset.x = ofRandomf(); //this just randomizes the initial position so the "thrust" doesnt go in the same direction
    offset.y = ofRandomf();
    offset.z = ofRandomf();
    
    velocity.set(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1) );
    
    gravity.set(0, ofRandom(-1,1));
    gravity.set(0, gravity.y*(0.1*radius));
    wind.set(ofRandom(-1,1), 0);
    turbAmt.set(ofRandom(0,15), ofRandom(0,15));
    turbSpeed.set(5, 5);
    isDragging = false;

	radius = ofRandom(3,_maxSize);
    age = 0;
    dead = false;
    maxAge = ofRandom(0,_maxAge)+50;
    rotation.x = ofRandom(360);
    rotation.y = ofRandom(360);
    rotation.z = ofRandom(360);
    randomSeed = ofRandom(500000);
    
    attractionStrength = 0; //just set negative to make it repulsion..

}

void Particle::update(int _particleID, ofPoint attractPoint, float _maxVelocity){

    //could use particleID to further randomize the particles,
    
    prevPt = pt; //save last point for lines mode
    
    age++; //age the particle
    
    computeFriction(); //compute friction of our moving body
    //computeAttraction(attractPoint);
    
    applyForce(computeAttraction(attractPoint));
    //wind.x = wind.x + turbAmt.y*ofSignedNoise(turbSpeed.y*ofGetElapsedTimef()+randomSeed);
    applyForce(wind);
    //gravity.y = gravity.y +turbAmt.x*ofSignedNoise(turbSpeed.x*ofGetElapsedTimef()+randomSeed);
    //cout<<1000*turbAmt.x*ofSignedNoise(turbSpeed.x*ofGetElapsedTimef()+randomSeed)<<endl;
    applyForce(gravity);
    applyForce(friction); //compute and accumulate all of our forces on acceleration
    
    velocity = velocity + acceleration; //change speed based on acceleration
    velocity.limit(_maxVelocity); //make sure we don't go too fast...
    
    pt = pt + velocity; //increment position
    //pt.z = pt.z + velocity.z;
    
    
    //Edge checking
    
    int maxSpeed = _maxVelocity; //in either direction
    if (pt.x-radius<=0) {
        pt.x = 0+radius;
        velocity.x = -velocity.x;
        velocity.x = ofClamp(velocity.x, -maxSpeed, maxSpeed);
    }
    if (pt.x+radius >= ofGetWidth()) {
        pt.x = ofGetWidth()-radius; 
        velocity.x = -velocity.x;
        velocity.x = ofClamp(velocity.x, -maxSpeed, maxSpeed);
    }
    
    if (pt.y-radius<=0) {
        pt.y = 0+radius; 
        velocity.y = -velocity.y;
        velocity.y = ofClamp(velocity.y, -maxSpeed, maxSpeed);
    }
    if (pt.y+radius >= ofGetHeight()) {
        pt.y = ofGetHeight()-radius; 
        velocity.y = -velocity.y;
        velocity.y = ofClamp(velocity.y, -maxSpeed, maxSpeed);
    }
    
    acceleration.set(0, 0); //reset acceleration so it does not accumulate
    
    //color.set(255, ofMap(age, 0, maxAge, 255,0), ofMap(age, 0, maxAge, 255,0), ofMap(age, 0, maxAge, 255,0)); //this changes color over life
    
    currentColor = startColor*(1-(age/maxAge)) + endColor*(age/maxAge); //interpolate between the two colors...this seems to interpolate slower than the next line
    //currentColor = startColor.lerp(endColor, age/maxAge);
    
    if (age >= maxAge) dead = true;
    
    rotation.x = rotation.x + 5*(age/maxAge); //this set of statements makes things spin faster as they age...as age approaches max age, the value gets closer to 1, but starts close to 0
    rotation.y = rotation.y + 8*(age/maxAge);
    rotation.z = rotation.z + 3*(age/maxAge);
    
    radius = radius - 0.5*(age/maxAge); //this makes them smaller as they age
    radius = ofClamp(radius, 0, 500);
    
}

void Particle::draw(pType _type){
    type = _type; //should this inherit from above on init or just take the command from draw?
    ofSetColor(currentColor);
    switch (type) {
        case SPHERE:
            ofPushMatrix();
            ofTranslate(pt);
            //ofSphere(0,0, radius-radius*(age/maxAge));
            ofCircle(0,0, radius-radius*(age/maxAge));
            ofPopMatrix();
            break;
        case TRIANGLE:
            ofFill();
            ofPushMatrix();
            ofTranslate(pt);
            ofRotateX(rotation.x);
            ofRotateY(rotation.y);
            ofRotateZ(rotation.z);
            ofTriangle(0, 0, radius/2, radius, -radius/2, radius);
            ofPopMatrix();
            break;
        case CUBE:
            ofFill();
            ofPushMatrix();
            ofTranslate(pt);
            ofRotateX(rotation.x);
            ofRotateY(rotation.y);
            ofRotateZ(rotation.z);
            ofBox(0, 0, 0, radius);
            ofPopMatrix();
            break;
        case LINES:
            ofSetLineWidth(2);
            ofLine(pt,prevPt);
            break;
        case MESHER:
            ofPoint temp;
            temp = pt;
            meshPts.push_back(temp);
            if (meshPts.size() > 15){
                meshPts.erase(meshPts.begin());
            }
            
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            for(int i = 0; i < meshPts.size(); i++) {
                //ofColor cur(255, 255, 0, ofMap(i, 0, 15, 0, 255));
                mesh.addColor(currentColor);
                mesh.addVertex(meshPts[i] - ofVec3f(1, 0, 0));
                mesh.addColor(currentColor);
                mesh.addVertex(meshPts[i] + ofVec3f(1, 0, 0));
            }
            mesh.draw();
            break;
        /*default:
            glEnable(GL_POINT_SMOOTH);
            glBegin(GL_POINTS);
            glPointSize(5);
            glVertex2f(0.0, 0.0);
            glEnd();
            break;*/
    }
}

void Particle::applyForce(ofVec3f force){
    acceleration = acceleration + (force/radius); //scale the force's influence depending on its size
}

void Particle::computeFriction(){
    //compute friction
    float c = 0.4; //friction amount
    friction = -velocity; //friction is the opposite of velocity
    friction = friction.normalize();
    friction = friction*c;
}

ofPoint Particle::computeAttraction(ofPoint attractor){
    ofPoint force;
    float magnitude;
    float mass = 60;
    force = attractor - pt; //attraction vector...subtract the mover from the attractor to get direction
    magnitude = force.length();
    magnitude = ofClamp(magnitude, 2,25); //arbitrary values
    force = force.normalize(); //get direction of vector
  //gravity constant...increase to get more attraction
    float strength = (attractionStrength*mass * radius)/(magnitude * magnitude);
    force = force * strength;
    return force;
}

ofPoint Particle::getPoint(){
    return pt;
}

float Particle::getMass(){
    return radius;
}

bool Particle::isInside(ofRectangle dragBox) {
    if (dragBox.inside(pt)){
        return true; 
    } else {
        return false;
    }
}

bool Particle::bIsDead(){
    return dead;
}

void Particle::setWind(float _wind){
    wind.x = _wind;
}

void Particle::setGravity(float _gravity){
    gravity.y = _gravity;
}

void Particle::setAttraction(float _attraction){
    attractionStrength = _attraction;
}

void Particle::setTurbAmt(ofVec2f _turbAmt){
    turbAmt = _turbAmt;
}

void Particle::setTurbSpeed(ofVec2f _turbSpeed){
    turbSpeed = _turbSpeed;
}

