#include "ofApp.h"




float cloudRadius = 500;		//Cloud cloudRadiusuis parameter
float cloudVel = 0.1;		//Cloud points cloudVelocity parameter


const int total = 300;		//Number of cloud points

//Offsets for Perlin noise calculation for points
float tx[total], ty[total], tz[total];
ofVec2f p[total]; //Cloud's points positions
int pRadius[total];


float time0 = 0;		//Time value, used for dt computing


//--------------------------------------------------------------
void ofApp::setup(){
    
    //Initialize points offsets by random numbers
    
    for ( int j = 0; j < total; j++ ) {
        
        tx[j] = ofRandom( 0, 1000 );
        ty[j] = ofRandom( 0, 1000 );
        
        pRadius[j] = ofRandom(1, 3);

    }
    


}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Update particles using spectrum values
    
    //Computing dt as a time between the last
    //and the current calling of update()
    
    float time = ofGetElapsedTimef();
    float dt = time - time0;
    dt = ofClamp( dt, 0.0, 0.1 );
    time0 = time; //Store the current time
    
    //Update cloudRadius and cloudVel from mouse input

    cloudRadius = ofMap( ofGetMouseX(), 0, ofGetWidth(), 400, 800, true );
    cloudVel = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0.05, 0.5 );
    
    //Update particles positions
    
    for (int j = 0; j < total; j++) {
        
        tx[j] += cloudVel * dt;	//move offset
        ty[j] += cloudVel * dt;	//move offset

        
        //Calculate Perlin's noise in [-1, 1] and
        //multiply on cloudRadius
        p[j].x = ofSignedNoise( tx[j] ) * cloudRadius;
        p[j].y = ofSignedNoise( ty[j] ) * cloudRadius;

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground( ofColor::black );	//Set up the background


    
    //Draw cloud
    
    //Move center of coordinate system to the screen center
    ofPushMatrix();
    ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
    
    ofColor c = ofColor::whiteSmoke;
    
    //Draw points
    ofSetColor( c );
    ofFill();
    
    for (int i = 0; i < total; i++) {
        
        //ofDrawCircle( p[i], pRadius[i]);
        ofSetSphereResolution(5);
        ofDrawSphere(p[i], pRadius[i]);
    }
    
    //Draw lines between near points
    float dist = 30;	//Threshold parameter of distance
    
    for (int j = 0; j < total; j++) {
    
        for (int k = j + 1; k < total; k++) {
            
            float pDist = ofDist( p[j].x, p[j].y, p[k].x, p[k].y );
            
            if ( pDist < dist ) {
                
                ofSetLineWidth(ofRandom(0.5));
                float alpha = j;
                ofSetColor( c,  j);
                ofDrawLine( p[j], p[k] );
            }
        }
    }
    
    //Restore coordinate system
    ofPopMatrix();



}

