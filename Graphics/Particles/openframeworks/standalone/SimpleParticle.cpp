#include "SimpleParticle.h"
SimpleParticle::SimpleParticle(ofPoint origin, float radius, float _maxRadius, ofColor _startColor, ofPoint velocity, float kRate, float cutOff, bool kill){
    
    this->currentColor = _startColor;
    pt = origin;// + ofPoint(ofRandom(-2.5,2.5), ofRandom(-2.5,2.5));
    prevPt = origin;
    
    offset.x = ofRandomf(); //this just randomizes the initial position so the "thrust" doesnt go in the same direction
    offset.y = ofRandomf();
    offset.z = ofRandomf();
    
    this->velocity = velocity;
    this->kRate = kRate;
	this->radius = radius;
    minRadius = radius;
    age = 0;
    dead = false;
    maxRadius = _maxRadius;
    reverse = maxRadius/2;
    kill = true;
    
}
//------
void SimpleParticle::update(int particleID){
    //velocity = velocity + acceleration; //change speed based on acceleration
    //velocity.limit(maxVelocity); //make sure we don't go too fast...
    //pt = pt + velocity; //increment position
    
    pt.x = prevPt.x; //+ (sin(fmod(ofGetElapsedTimef(),60))*0.016*age+30*ofSignedNoise(age))*sin(0.05*age); //increment position
    pt.y = prevPt.y; //+(cos(fmod(ofGetElapsedTimef(),60))*0.016*age+30*ofSignedNoise(age))*cos(0.05*age); //increment position
    age++;
    
    
    if((radius >= maxRadius/2.) && kill){
        dead = true;
    }
    if(age > 200){
        dead = true;
    }
    
    
    if(!dead){
        float diff = maxRadius-radius;
        float diffInvert = reverse - minRadius;
        //if(diff > maxRadius*0.125 && age < 100){
        float ratio = 1 - 1/(diff+1);
        float foo = (ratio*age*velocity.x)/kRate;
        radius += abs(radius-foo)/kRate;
        
       
       
        
        //        }else{
        //            float newR = radius + ofMap(radius, minRadius, maxRadius*0.125, 50, 5, true) + ofMap(radius, maxRadius*.1, maxRadius, 0, 50, true) ;
        //            float newDiff = newR+velocity.x - radius;
        //            radius = ofClamp(radius+newDiff/kRate, 0, 2000);
        //}
    }
    
    
    
}

void SimpleParticle::draw(){
    ofEnableAlphaBlending();
    ofPushMatrix();
    ofPushStyle();
    ofSetCircleResolution(6);
    ofTranslate(pt);
    ofRotate(90);

    ofNoFill();
    ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius/2, 100, 25));
    ofCircle(0, 0, maxRadius - radius);
    
    
    ofNoFill();
    ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius/2, 255, 25));
    ofCircle(0, 0, radius);
    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.77);
    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.66);
    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.33);
    ofPopStyle();
    ofPopMatrix();
    ofDisableAlphaBlending();
}


//---------
void SimpleParticle::setNewColor(ofColor newColor){
    currentColor = newColor;
}
//---------
ofColor SimpleParticle::getCurrentColor(){
    return currentColor;
}

