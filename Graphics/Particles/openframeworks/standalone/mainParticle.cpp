//
//  mainParticle.cpp
//  booth_UI_graphics
//
//  Created by fakelove on 3/10/14.
//
//

#include "mainParticle.h"


//------------------------------------------------------------------
mainParticle::mainParticle(){
	attractPoint = NULL;
}

//------------------------------------------------------------------
void mainParticle::setAttractPoints( ofPoint * attract ){
	attractPoint = attract;
}

//------------------------------------------------------------------
void mainParticle::reset(){

    pos = ofPoint(0,0,0);
    vel = ofPoint(0,0,0);
    frc = ofPoint(0,0,0); 
    
    for (int i = 0; i < trailLength; i++) {
        points.push_back(pos);
    }
    
	uniqueVal = ofRandom(-10000, 10000);
	
	
    
	scale = ofRandom(0.5, 1.0);
	
    drag  = ofRandom(0.90, 0.998);
    
    
}

//------------------------------------------------------------------
void mainParticle::update(float framerateMult,
                          float attractScale, float wanderScale, float minDist, float maxDist,
                          float tScale, float complexity, float noiseScale, float smoothing){

    // attraction

    ofPoint closestPt;
    int closest = -1;
    float closestDist = 9999999;

    float lenSq = ( *attractPoint-pos ).lengthSquared();
    if( lenSq < closestDist ){
        closestDist = lenSq;
    }
    
    
    
    closestPt = *attractPoint;
//    if (sin(ofGetElapsedTimef()/2) > 0.5 && mainID < 4) {
//        ofPoint noiseDisp;
//        noiseDisp.x = ofSignedNoise(uniqueVal, closestPt.y * 0.01, ofGetElapsedTimef()*0.2);
//        noiseDisp.y = ofSignedNoise(uniqueVal, closestPt.z * 0.01, ofGetElapsedTimef()*0.2);
//        noiseDisp.z = ofSignedNoise(uniqueVal, closestPt.x * 0.01, ofGetElapsedTimef()*0.2);
//        closestPt += noiseDisp * 100;
//    }
    
    
    float dist = sqrt(closestDist);
    
    //in this case we don't normalize as we want to have the force proportional to distance
    frc = closestPt - pos;
    
    vel *= drag;
    
    //lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
//    if( dist < maxDist && dist > minDist && !ofGetKeyPressed('f') ){
         vel += frc * (attractScale + (attractScale*0.5) * ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2));
//        //        }else{
//        //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
        frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
        frc.y = ofSignedNoise(uniqueVal, pos.z * 0.01, ofGetElapsedTimef()*0.2);
        frc.z = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
        vel += frc * 0.4 * wanderScale;
//    }
//
//    
    pos += vel * framerateMult;
    
//    pos = closestPt;// + frc * 0.4 * wanderScale;
    
    //update points
    if (ofGetFrameNum() % 3 ==0 ) {
        points.push_back(pos);
        points.erase(points.begin());
    }
    else {
        points[points.size()-1] = pos;
    }
//    while (points.size() > trailLength) { points.erase(points.begin()); }
    
    //add noise field
//    if (mainID > 1) {
        for (int i = 0; i < points.size(); i++){
            float pct = (float)i / trailLength;
            points[i] += getField3d(points[i], tScale, complexity) * noiseScale * pct;
        }

    
    //smoothing
    for (int i = 0; i < points.size()-1; i++){
        ofPoint vel = points[i+1] - points[i];
        points[i] += vel * smoothing * framerateMult;
    }
    
}

//------------------------------------------------------------------
void mainParticle::draw(){
//    particleTrail.draw();
}

//--------------------------------------------------------------
ofVec3f mainParticle::getField3d(ofVec3f position, float tScale, float complexity) {
//	float t = ofGetFrameNum() * tScale;
    float t = ofGetElapsedTimef() * 60 * tScale;
    float phase = TWO_PI;
    
    float normx = ofNormalize(position.x, -300, 300);
	float normy = ofNormalize(position.y, -300, 300);
    float normz = ofNormalize(position.z, -300, 300);
	float u = ofSignedNoise(t + phase, normx * complexity + phase, normy * complexity + phase, normz * complexity + phase);
	float v = ofSignedNoise(t, normx * complexity, normy * complexity, normz * complexity);
    float w = ofSignedNoise(t - phase, normx * complexity - phase, normy * complexity - phase, normz * complexity + phase);
	return ofVec3f(u, v, w);
}

