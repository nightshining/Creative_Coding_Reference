
#include <iostream>
#include "ParticleEmitter.h"

void ParticleEmitter::setup(ofPoint _origin, int maxSpeed, int maxSize, int maxAge, ofColor _startColor, ofColor _endColor){
    ofSetFrameRate(100);
    ofBackground(0,0,0);
    rotation = 0;
    origin = _origin;
    startColor = _startColor;
    endColor = _endColor;
    for(int i=0; i<ParticleSize; i++) p[i] = new Particle(origin, maxSpeed, maxSize, maxAge, startColor, endColor); 
}

void ParticleEmitter::update(float maxSpeed, int maxSize, int maxAge){
    

    for(int i=0; i<ParticleSize; i++) {
        p[i]->update(i, origin, maxSpeed);
        if (p[i]->dead==true) {
            delete p[i];
            p[i] = new Particle(origin, maxSpeed, maxSize, maxAge, startColor, endColor);
        }
    }    

}

void ParticleEmitter::draw(int x, int y, pType _type){
    //ofPushMatrix();
   // ofTranslate(x, y);
   // ofRotate(rotation);
    
    for(int i=5; i<ParticleSize; i++){
        ofSetColor(0);
        ofSetLineWidth(0.1);
        //ofLine(p[i]->pt, p[i-1]->pt);
        p[i]->draw(_type);
        
        
        //PLEXUS STUFF
        /*
        //THIS IS SLOW..HOLY SHIT...NO MORE THAN 200 PARTICLES
        for (int j=0; j<ParticleSize; j++) {
            if (p[i]->getPoint().distanceSquared(p[j]->getPoint())<(50*50)) {
                ofSetColor(ofMap(p[i]->getPoint().distanceSquared(p[j]->getPoint()), 0, 50*50, 255, 0));
                ofLine(p[i]->getPoint(), p[j]->getPoint());
            }
        }*/
        
        /*if(ofDist(p[i]->getPoint().x, p[i]->getPoint().y, p[i-1]->getPoint().x, p[i-1]->getPoint().y )<200){
            ofLine(p[i]->getPoint(), p[i-1]->getPoint());
            ofLine(p[i-1]->getPoint(), p[i-2]->getPoint());
            ofLine(p[i-2]->getPoint(), p[i-3]->getPoint());
            ofLine(p[i-3]->getPoint(), p[i-4]->getPoint());
        }*/
        
        
    }
    //ofPopMatrix();
}

void ParticleEmitter::setForces(float _gravity, float _wind, float attraction, ofVec2f _turbSpeed, ofVec2f _turbAmt){
    
    //these could be in update...but that will start to get really complex...so lets break out the pieces into 
    for(int i=0; i<ParticleSize; i++) {
        p[i]->setWind(_wind); 
        p[i]->setGravity(_gravity);
        p[i]->setAttraction(attraction);
        p[i]->setTurbSpeed(_turbSpeed);
        p[i]->setTurbAmt(_turbAmt);
    }
}

void ParticleEmitter::setOrigin(ofPoint _origin){
    origin = _origin;
}
void ParticleEmitter::setColors(ofColor _startColor, ofColor _endColor){
    startColor = _startColor;
    endColor = _endColor;
}
