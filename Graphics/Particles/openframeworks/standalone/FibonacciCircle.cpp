//
//  FibonacciCircle.cpp
//  visualTests
//
//  Created by dantheman on 4/2/14.
//
//

#include "FibonacciCircle.h"

FibonacciCircle::FibonacciCircle(ofPoint origin, float radius, float _maxRadius, ofColor _startColor, ofPoint velocity, float kRate, float cutOff, bool kill){
    
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
    this->kill = kill;
    mTouch = 0;
    
}
//------
void FibonacciCircle::update(int particleID){
    //velocity = velocity + acceleration; //change speed based on acceleration
    //velocity.limit(maxVelocity); //make sure we don't go too fast...
    //pt = pt + velocity; //increment position
    
    pt.x = prevPt.x; //+ (sin(fmod(ofGetElapsedTimef(),60))*0.016*age+30*ofSignedNoise(age))*sin(0.05*age); //increment position
    pt.y = prevPt.y; //+(cos(fmod(ofGetElapsedTimef(),60))*0.016*age+30*ofSignedNoise(age))*cos(0.05*age); //increment position
    age++;
    
    
    if((radius >= maxRadius || (particleID > 125)) && kill){
        dead = true;
    }
    if((radius < maxRadius && age > 500) && kill){
        dead = true;
    }
    
    
    if(!dead){
        float diff = maxRadius-radius;
//        float diffInvert = reverse - minRadius;
        //if(diff > maxRadius*0.125 && age < 100){
        float ratio = 1 - 1/(diff+1);
//        float ratioInvert = 1/(diffInvert+1);
        float foo = (ratio*age*velocity.x)/kRate;
//        float fooInvert = (ratioInvert*age*(velocity.x))/kRate;
        
//        reverse -= abs(radius-fooInvert)/kRate;
        radius += abs(radius-foo)/kRate;
        
//        reverse = ofClamp(reverse, 0, maxRadius);
        radius = ofClamp(radius, 0, maxRadius*1.75);
        //        }else{
        //            float newR = radius + ofMap(radius, minRadius, maxRadius*0.125, 50, 5, true) + ofMap(radius, maxRadius*.1, maxRadius, 0, 50, true) ;
        //            float newDiff = newR+velocity.x - radius;
        //            radius = ofClamp(radius+newDiff/kRate, 0, 2000);
        //}
    }
}

void FibonacciCircle::setTouch(float touch){
    mTouch = touch;
}

void FibonacciCircle::draw(){
    
    ofPushMatrix();
    ofSetCircleResolution(45);
    ofSetLineWidth(6);
    ofTranslate(pt);
    //ofRotate(90);
    //ofRotate(ofMap(radius, 0, maxRadius, 0, 360));
    //ofRotateY(abs(ofMap(radius, 0, maxRadius, -180, 180)));
//    ofFill();
//////    ofSetColor(MD_BLACK, ofMap(radius, maxRadius, minRadius, 100, 10));
//////    ofCircle(0, 0, reverse);
//    ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius/2, 25, 0));
//    ofCircle(0, 0-radius, radius);
//    ofCircle(0, 0+radius, radius);
    ofRotate(mTouch*ofMap(radius, 0, maxRadius, 0, 360));
    ofNoFill();
    ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, 0, maxRadius, 250, 0));
    ofCircle(0, 0-radius, radius);
    ofCircle(0, 0+radius, radius);

    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.77);
    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.66);
    //        ofSetColor(currentColor.r,currentColor.g, currentColor.b, ofMap(radius, minRadius, maxRadius, 125, 255));
    //    ofCircle(0, 0, radius*0.33);
    ofPopMatrix();
}

int FibonacciCircle::getFibonacci(int index){
    int foo = (pow((1+sqrt(5)), index) - pow((1-sqrt(5)), index))/(pow(2.0,index) * sqrt(5));
    return foo;
}
//---------
void FibonacciCircle::setNewColor(ofColor newColor){
    currentColor = newColor;
}
//---------
ofColor FibonacciCircle::getCurrentColor(){
    return currentColor;
}

