#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxDmx.h"
#include "ofxOsc.h"

enum commType {OSC,DMX};

class DMXLighting{
public:
    DMXLighting();
    ~DMXLighting();
    
    void setup(commType type, string _hostname, string _hostname2, int port, bool dualSend);
    void update(ofTexture &fbo, int x, int y);
    void updateDMX(ofColor color, int DMXchannel);
    void updateOSC(ofColor color);
    ofColor getCurrentColor();
    void drawCapturedColor(int x, int y);
    void setColorOffsets(int r, int g, int b);
    bool getDMXStatus();
    string getDMXAddress();
    
    string hostname1, hostname2;
    bool bIsDualSend;
    
    string getOSCIP1();
    string getOSCIP2();
    
    int offsetRed, offsetGreen, offsetBlue; //offsetValues for sending to DMX lights
    
    ofxDmx dmx;
    ofxOscSender oscSend;
    ofxOscSender oscSend2;
    
    int redRunningAvg;
    int blueRunningAvg;
    int greenRunningAvg;

private:
    ofPixels pixel;
    ofColor currentColor;
    ofColor prevColor;
    ofColor prevColor2;
    ofColor prevFurnitureColor;
    ofColor prevFurnitureColor2;
    float fadeFurnitureRamp;
    float fadeRamp;
    bool colorFlip;
    bool colorFurnitureFlip;
    bool isOsc;
    bool isDMX;
    long preSend;
};