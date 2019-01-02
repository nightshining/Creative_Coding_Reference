#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableAlphaBlending();
  
    
    pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));

    
    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(240.f, 240.f, 240.f));
	pointLight.setPointLight();
       
    scratch.loadImage("of.png");
    //light.setPosition(200, 200, 200);
    
    gui.setup("Panel");
    maxParticleSpeed.set("Speed", 10, 0,50);
    maxParticleSize.set("Size", 50, 0.0, 200.0);
    maxParticleAge.set("Age", 50, 0.0, 4000.0);
    addBlend.set("AddBlend", false);
    AlphaBlendSwitch.set("AlphaBlend", false);
    pointLightSwitch.set("PointLight", true);
    cameraSwitch.set("Camera", false);
    trailEnable.set("Trail Enable", true);
    gravity.set("Gravity", 0, -30, 30);
    wind.set("Wind", 0, -30, 30);
    attraction.set("Attraction", 0, -30, 30);
    particleType.set("Type", 2, 0, 4);
    
    gui.add(maxParticleSpeed);
    gui.add(maxParticleSize);
    gui.add(maxParticleAge);
    gui.add(addBlend);
    gui.add(AlphaBlendSwitch);
    gui.add(pointLightSwitch);
    gui.add(cameraSwitch);
    gui.add(trailEnable);
    gui.add(gravity);
    gui.add(wind);
    gui.add(attraction);
    gui.add(fadeAmt);
    gui.add(particleType);
    gui.loadFromFile("settings.xml");
    
    
//    gui.add(turbAmtX.setup("Turb Amt X", 1, 0, 3));
//    gui.add(turbAmtY.setup("Turb Amt Y", 1, 0, 3));
//    gui.add(turbSpeedX.setup("Turb Speed X", 1, 0, 60));
//    gui.add(turbSpeedY.setup("Turb Speed Y", 1, 0, 60));
    
    emitter.setup(ofPoint(ofGetWidth()/2, ofGetHeight()/2), maxParticleSpeed, maxParticleSize, maxParticleAge, ofColor(80,120,255,255),ofColor(0,255,0,0));

	material.setShininess( 120 );
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    //camera.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    
    fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    ofFbo::Settings s;
    s.width			= ofGetWidth();
    s.height			= ofGetHeight();
    s.internalformat   = GL_RGBA;
    s.useDepth			= true;
    // and assigning this values to the fbo like this:
    fbo1.allocate(s);
    
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();
    colorCount = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // radius of the sphere //
	float radius		= 180.f;
	ofPoint center;
    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x, 
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y, 
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    //pointLight.setPosition(ofPoint(ofGetMouseX(), ofGetMouseY()));
    
    ofSetWindowTitle("FPS: " + ofToString(ofGetFrameRate()));
    emitter.update(maxParticleSpeed, maxParticleSize, maxParticleAge);
    emitter.setOrigin(ofPoint(ofGetMouseX(), ofGetMouseY()));
    
   // gravity = gravity + turbAmtX*ofSignedNoise(turbSpeedX*ofGetElapsedTimef()+6859);
    //wind = wind +turbAmtY*ofSignedNoise(turbSpeedY*ofGetElapsedTimef()+8697);
    emitter.setForces(gravity, wind, attraction, ofVec2f(turbAmtX, turbAmtY), ofVec2f(turbSpeedX, turbSpeedY));
    
    ofColor colorStart, colorEnd;
    
    colorCount = (colorCount + 1);
    colorCount = fmod(colorCount, 255);
    colorStart.setHsb(colorCount, 255,255);
    colorEnd.setHsb(255-colorCount, 255,255);

    ofRect(400, 400, 200, 200);
    emitter.setColors(ofColor(colorStart), ofColor(colorEnd));

}

//--------------------------------------------------------------
void testApp::draw(){

    

    ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
    
    if (trailEnable) {
        glDisable(GL_DEPTH_TEST);
        ofEnableAlphaBlending();
        fbo1.begin(); 
        ofFill();
        ofSetColor(0,0,0, fadeAmt);
        ofRect(0,0,ofGetWidth(),ofGetHeight());
    }


    if(cameraSwitch) camera.begin();
    
    if(AlphaBlendSwitch) ofEnableAlphaBlending();
    if(pointLightSwitch) ofEnableLighting(); 
    if(pointLightSwitch) material.begin(); //this gives the boxes shininess
    if(pointLightSwitch) pointLight.enable();

    ofPushMatrix();
    if(addBlend) ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    if (particleType== 0) {
        emitter.draw(-ofGetWidth()/2,-ofGetHeight()/2, SPHERE);
    }
    else if (particleType== 1) {
        emitter.draw(-ofGetWidth()/2,-ofGetHeight()/2, CUBE);
    }
    else if (particleType == 2) {
        emitter.draw(-ofGetWidth()/2,-ofGetHeight()/2, LINES);
    }
    else if (particleType == 3) {
        emitter.draw(-ofGetWidth()/2,-ofGetHeight()/2, TRIANGLE);
    }
    else if (particleType == 4) {
        emitter.draw(-ofGetWidth()/2,-ofGetHeight()/2, MESHER);
    }


    ofPopMatrix();

    if(pointLightSwitch) material.end();
    if(pointLightSwitch) pointLight.disable();
    if(pointLightSwitch) ofDisableLighting();
    
    if(cameraSwitch) camera.end();
    
    if (trailEnable) {
        fbo1.end();
    }
    
    ofSetColor(255);
    
    ofPushMatrix();
    if(trailEnable) fbo1.draw(0, 0);
    ofPopMatrix();
    
    ofSetColor(255);
    glDisable(GL_DEPTH_TEST);
    if(AlphaBlendSwitch) ofDisableAlphaBlending();//must be disabled for gui to draw correctly
    ofDisableLighting(); //must be disabled for gui to draw correctly
    ofEnableArbTex();
    gui.draw();
    

 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}