#include "NormalParticle.h"
NormalParticle::NormalParticle(ofVec3f origin, ofVec3f vel, ofMesh* dot){
    pt = origin;
    pos = pt;
    velocity = vel;
    age = 0;
    dead = false;
    shape = dot;
}
//------
void NormalParticle::update(int particleID){
    //velocity = velocity + acceleration; //change speed based on acceleration
    //velocity.limit(maxVelocity); //make sure we don't go too fast...
    //pt = pt + velocity; //increment position
    
    age++;

    if(age > 15){
        dead = true;
    }
    
    if(!dead){
        velocity -= velocity/20.0;
        pos+=velocity;
    }

}

void NormalParticle::draw(){
    
    ofLine(pt.x, pt.y, pt.z, pos.x, pos.y, pos.z);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y, pos.z);
    shape->draw();
    ofPopMatrix();

}


//---------
void NormalParticle::setNewColor(ofColor newColor){
    currentColor = newColor;
}
//---------
ofColor NormalParticle::getCurrentColor(){
    return currentColor;
}

