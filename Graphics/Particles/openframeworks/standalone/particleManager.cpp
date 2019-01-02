//
//  particleManager.cpp
//  booth_UI_graphics
//
//  Created by fakelove on 3/11/14.
//
//

#include "particleManager.h"
#include "constants.h"

//--------------------------------------------------------------
void particleManager::setup(int _nParticles, int _trailLength){
    //setup particles
    framerateMult = 1.0;
    
    
    nParticles = _nParticles;
    trailLength = _trailLength;
    
    for (int i = 0; i < nParticles; i++) {
        
        mainParticle * newP = new mainParticle;
        newP->setAttractPoints(&orbitOrigin);
        newP->trailLength = trailLength;
        
        particles.push_back(newP);
    }
    
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->reset();
//        cout << i << "num particles " << particles[i]->points.size() << endl;
    }
    
    //init params
    
    minDist = 30;
    maxDist = 400;
    attractScale = 0.004;
    wanderScale = 0.1;
    
    tScale = 0.0;
    complexity = 16;
    noiseScale = 1.0;
    smoothing = 0.1;
    breakoutScale = 0.0;
    
    orbitOrigin.set(0, 0);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    grid.loadImage(ofToDataPath("logo/220px-Grid_illusion.svg.png"));
    texX = 220;
    texY = 220;
}


//--------------------------------------------------------------
void particleManager::update(){
    framerateMult = 60.0f/(1.0f/ofGetLastFrameTime());
    
    float angle = ofGetElapsedTimef()*speed + initialAngle;
    float r = radius;
    orbitOrigin.x = xorig + r * cos(angle);
    orbitOrigin.y = yorig + r * -sin(angle);

    //updateParticles...
    for(unsigned int i = 0; i < particles.size(); i++){
        particles[i]->update(framerateMult,
                            attractScale, wanderScale,
                            minDist, maxDist,
                            tScale, complexity, noiseScale, smoothing);
    }
}

//--------------------------------------------------------------
void particleManager::draw(ofColor meshCol, float alpha){
    
    mesh.clear();
    
    int width = nParticles;
    int height = trailLength;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mesh.addVertex(ofVec2f(particles[j]->points[i]));

            float pct = (float)i / height;
            ofFloatColor vertCol = ofFloatColor(MD_WHITE) * pct + ofFloatColor(meshCol) * (1-pct);
            vertCol.a = alpha;
            mesh.addColor(vertCol);
        }
    }
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mesh.addIndex(x+y*width);       // 0
            mesh.addIndex((x+1)+y*width);     // 1
            mesh.addIndex(x+(y+1)*width);     // 10
            
            mesh.addIndex((x+1)+y*width);     // 1
            mesh.addIndex((x+1)+(y+1)*width);   // 11
            mesh.addIndex(x+(y+1)*width);     // 10
        }
    }
//    ofPushStyle();
//
//    for (int i = 0; i < nParticles; i++) {
//            ofSetColor(255, i*50, 250 - i*40);
//        ofCircle(particles[i]->points[particles[i]->points.size()-1], 5);
//    }
//    ofPopStyle();
    



    mesh.draw();

    
//    ofSetColor(255, 0, 0);
//    ofCircle(orbitOrigin, 5);
    
}


