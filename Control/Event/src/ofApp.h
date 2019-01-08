#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "TriggerEvent.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //void newFloat(float & f);
    //void newInt(int & i);
    
    void triggerOn(bool & b);
    void triggerOff(bool & b);
    
    TriggerEvent eventObject;
    
    string floatMsg;
    string intMsg;
    string expireMsg;
    
    bool enabled;
    
};
