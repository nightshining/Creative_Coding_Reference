
#include "DMXLighting.h"
DMXLighting::DMXLighting(){
    
}
//-------
DMXLighting::~DMXLighting(){
    
}
//---------
void DMXLighting::setup(commType type, string _hostname, string _hostname2, int port, bool dualSend){
    pixel.allocate(1, 1, 4); //we only need one pixel!
    
    bIsDualSend = dualSend;
    
    if(type==OSC){
        oscSend.setup(_hostname, port);
        cout<<"First OSC:" + _hostname<<endl;
        hostname1 = _hostname;
        isOsc = true;
        isDMX = false;
        if (bIsDualSend) {
            cout<<"Is dual sender:" + _hostname2<<endl;
            oscSend2.setup(_hostname2, port);
            hostname2 = _hostname2;
        }
    }
    
    if(type==DMX){
        ofSetLogLevel(OF_LOG_NOTICE);
        hostname1 = _hostname;
        hostname2 = "";
        dmx.connect(_hostname);
        isOsc = false;
        isDMX = true;
    }
    
    offsetRed =0;
    offsetGreen = 0;
    offsetBlue = 0;
    
    ofSetLogLevel(OF_LOG_SILENT);
    fadeFurnitureRamp = 1;
    fadeRamp = 1;
    colorFlip = false;
    colorFurnitureFlip = false;
    
}
//---------
void DMXLighting::update(ofTexture &fbo, int x, int y){
    //grab the pixel at the current x/y position and read it into the pixel's single allocated pixel
    fbo.bind();
    //the Y may be inverted because of FBO coordinates
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel.getPixels()); //this may need to be GL_RGB if your FBO/texture isn't RGBA
    fbo.unbind();
    
    if (isOsc) {
        int red = ofMap(currentColor.r, 0, 255, 0, 100, true);
        int green = ofMap(currentColor.g, 0, 255, 0, 100, true);
        int blue = ofMap(currentColor.b, 0, 255, 0, 100, true);
        
        
        ofxOscMessage r;
        r.setAddress("/send");
        r.addIntArg(red);
        r.addIntArg(green);
        r.addIntArg(blue);
        if (bIsDualSend) {
            oscSend2.sendMessage(r);
            oscSend.sendMessage(r);
        }else{
            oscSend.sendMessage(r);
        }
    }
    
    if(isDMX){
        dmx.setLevel(1, 210); //picks RGB mode for dmx
        dmx.setLevel(2, ofMap(pixel.getColor(0, 0).r + offsetRed, 0, 255, 0, 255));
        dmx.setLevel(3, ofMap(pixel.getColor(0, 0).g + offsetGreen, 0, 255, 0, 255));
        dmx.setLevel(4, ofMap(pixel.getColor(0, 0).b + offsetBlue, 0, 255, 0, 255));
        
        dmx.update();
    }
}
bool DMXLighting::getDMXStatus(){
    return dmx.isConnected();
}
string DMXLighting::getDMXAddress(){
    if (isDMX) {
        return hostname1;
    }else{
        return "";
    }
    
}
string DMXLighting::getOSCIP1(){
    if(isOsc){
        return hostname1;
    }else{
        return "";
    }
}
string DMXLighting::getOSCIP2(){
    if(isOsc){
        return hostname2;
    }else{
        return "";
    }
}


//-----------
void DMXLighting::updateDMX(ofColor color, int DMXchannel){

    
    prevColor.lerp(color, 0.25);
    currentColor.lerp(prevColor, 0.33);
        //currentColor = color;
        //       // cout<<"SEND COLOR"<< color<<endl;
//        if(colorFlip){
//            fadeRamp=fadeRamp - 0.16;
//            currentColor = prevColor.lerp(prevColor2, fadeRamp);
//            cout<<"DMX:" <<fadeRamp<<endl;
//        }else{
//            fadeRamp=ofClamp(fadeRamp - 0.16, 0, 1); 
//            currentColor = prevColor2.lerp(prevColor, fadeRamp);
//           // cout<<fadeRamp<<endl;
//        }
    dmx.setLevel(DMXchannel, 210); //picks RGB mode for dmx on color strip
    dmx.setLevel(DMXchannel+1, ofClamp(currentColor.r + offsetRed, 0, 255)); //RGB is just channel +1,2,3
    dmx.setLevel(DMXchannel+2, ofClamp(currentColor.g + offsetGreen, 0, 255));
    dmx.setLevel(DMXchannel+3, ofClamp(currentColor.b + offsetBlue, 0, 255));
    dmx.update();
        
//        if(ofGetFrameNum()%60){
//            prevColor = color;
//            fadeRamp = 1;
//            colorFlip = !colorFlip;
//            if(!colorFlip)
//                prevColor2 = color;
//                        
//        }
//        if(ofGetFrameNum()%120){
//            prevColor2 =color;
//            fadeRamp = 1;
//            colorFlip = false;
//        }
//    }
}
//-----------
void DMXLighting::updateOSC(ofColor color){
 
    cout<<prevColor<<ofGetFrameNum()<<endl;
    cout<<currentColor<<endl;
        prevColor.lerp(color, 0.25);
        currentColor.lerp(prevColor, 0.33);


        //    currentColor = prevColor.lerp(currentColor, 0.5);
        
        //    redRunningAvg = (ofMap(currentColor.r + offsetRed, 0, 255,0,100,true) + redRunningAvg)/2;
        //    blueRunningAvg = (ofMap(currentColor.b + offsetRed, 0, 255,0,100,true) + blueRunningAvg)/2;
        //    greenRunningAvg = (ofMap(currentColor.g + offsetRed, 0, 255,0,100,true) + greenRunningAvg)/2;
        
        int red = ofMap(currentColor.r, 0, 255, 0, 100, true);
        int green = ofMap(currentColor.g, 0, 255, 0, 100, true);
        int blue = ofMap(currentColor.b, 0, 255, 0, 100, true);
        
        
        ofxOscMessage r;
        r.setAddress("/send");
        r.addIntArg(red);
        r.addIntArg(green);
        r.addIntArg(blue);
        oscSend.sendMessage(r);

       // cout<<"send: "<<ofGetFrameNum()<< " " << currentColor <<endl;
        if (bIsDualSend) {
            oscSend2.sendMessage(r);
        }
    
}
//-----------
void DMXLighting::drawCapturedColor(int x, int y){
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255);
    ofRect(0, 0, 60, 60);
    ofSetColor(pixel.getColor(0, 0).r, pixel.getColor(0, 0).g, pixel.getColor(0, 0).b);
    ofRect(5, 5, 50, 50);
    ofPopMatrix();
}
//-------------------
ofColor DMXLighting::getCurrentColor(){
    return pixel.getColor(0, 0);
}

void DMXLighting::setColorOffsets(int r, int g, int b){
    offsetRed = r;
    offsetGreen = g;
    offsetBlue = b;
}