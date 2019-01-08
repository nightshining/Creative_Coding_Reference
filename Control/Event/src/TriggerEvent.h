
#include "ofMain.h"
#include "ofEvents.h"

class TriggerEvent{
    
public:
    
    TriggerEvent(){
        counter = 0;
    }
    
    void enable(){
        ofAddListener(ofEvents().update, this, &TriggerEvent::update);
    }
    
    void disable(){
        ofRemoveListener(ofEvents().update, this, &TriggerEvent::update);
    }
    
    void update(ofEventArgs & ){
        
        bool on = true;
        bool off = false;
        
        counter += 0.3;
        
        int intCounter = (int)counter;
        int thresh = 50;
    
        if (intCounter <= thresh) {

            ofNotifyEvent(triggerOff,off,this);

        } else if (intCounter > thresh) {

            ofNotifyEvent(triggerOn,on,this);

        }
    }
    
    ofEvent<bool> triggerOff;
    ofEvent<bool> triggerOn;
    
        
    private:
        
    float counter;
        
};
    
