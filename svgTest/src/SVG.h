#include "ofMain.h"
#include "ofxSvg.h"
#include "ofxTween.h"

class SVG {
    public:
    void enableOutline(){bDrawOutline=true;}
    void disableOutline(){bDrawOutline=false;}
    void setColor(ofColor color){c=color;}
    void setLineWidth(float w){lineWidth=w;}
    void setOutlineFill(bool toggle){bFillToggle=toggle;};
    void setOutlinePlay(unsigned lengthMs, float min, float max){ aOutline.setParameters(1,easinglinear,ofxTween::easeOut,min,max,lengthMs,0);} //0.0-1.0 full play
    void setScale(unsigned lengthMs, float min, float max){ aScale.setParameters(2,easinglinear,ofxTween::easeOut,min,max,lengthMs,0);}
    void setRotate(unsigned lengthMs, float min, float max){ aRotate.setParameters(3,easinglinear,ofxTween::easeOut,min,max,lengthMs,0);}
    void setPosition(unsigned lengthMs, ofVec2f min, ofVec2f max){
        aPositionX.setParameters(4,easinglinear,ofxTween::easeOut,min.x,max.x,lengthMs,0);
        aPositionY.setParameters(5,easinglinear,ofxTween::easeOut,min.y,max.y,lengthMs,0);
    }
    ofVec2f getLastPos(){return lastPos;}
    
    void setup(string filename){
        
        step = 0;
        pos = ofVec2f(0,0);
        r = 0;
        s = 0.0;
        lastPos = ofVec2f(0.0,0.0);
        
        svg.load(filename);
        
        for (int i = 0; i < svg.getNumPath(); i++){
            ofPath p = svg.getPathAt(i);
            // svg defaults to non zero winding which doesn't look so good as contours
            p.setPolyWindingMode(OF_POLY_WINDING_ODD);//OF_POLY_WINDING_ODD
            vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
            for(int j=0;j<(int)lines.size();j++){
                outlines.push_back(lines[j].getResampledBySpacing(1));
            }
        }
    }
    
    void update(){
        
        step = aOutline.update();
        pos.x = aPositionX.update();
        pos.y = aPositionY.update();
        r = aRotate.update();
        s = aScale.update();
        
        
        
        //        step += speed;
        //        if (step > 1) {
        //            step -= 1;
        //        }
    }
    
    void draw() {
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        ofScale(s,s,s);
        ofRotateZ(r);
        ofPushMatrix();
        ofTranslate(-svg.getWidth()/2,-svg.getHeight()/2);
        ofSetColor(c);
        ofSetLineWidth(lineWidth);

        if(bDrawOutline) {

            if (bFillToggle){
                ofFill();
            } else {
                ofNoFill();
            }
            for (int i = 0; i < (int)outlines.size(); i++){
                ofPolyline & line = outlines[i];
                int num = step * line.size();
                
                ofBeginShape();
                for (int j = 0; j < num; j++){
                    ofVertex(line[j]); // create outline
                    lastPos = line[num]; // get last pos
                }
                ofEndShape();
            }
                
        } else {
            svg.draw(ofColor(255,0,0));

        }
        ofPopMatrix();
        ofPopMatrix();
        ofPopStyle();
    }
    

    
    
  
    private:
    
    //Utility//
    ofxSVG svg;
    vector<ofPolyline> outlines;
    ofVec2f lastPos;
    
    //Style//
    bool bDrawOutline, bFillToggle;
    ofColor c;
    float lineWidth, s, r;
    ofPoint pos;
    
    
    //Animation//
    ofxTween aOutline, aScale, aRotate, aPositionX, aPositionY;
    ofxEasingLinear easinglinear;

    float step;
    bool bAnimation;

    
};
