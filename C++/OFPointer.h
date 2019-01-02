///create a vector of ofSoundPlayers that are all pointers

    vector< ofPtr<ofSoundPlayer> > sounds;
//--------------------------------------------------------------
void ofApp::setup(){

    /// Load all our sound assets that exist in folder path 'assets' ///

    ofDirectory soundDir;
    soundDir.listDir("assets");


    for (int i = 0; i < (int)soundDir.size(); i++){

        ofPtr<ofSoundPlayer> tempSound (new ofSoundPlayer());
        tempSound->loadSound(soundDir.getPath(i));
        tempSound->setLoop(false);
        tempSound->setMultiPlay(true);
        cout << "Loading Sounds: " << soundDir.getPath(i) << endl;

        sounds.push_back(tempSound);
    }



}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){


    for (auto & it : sounds) {

        if (ofGetSeconds() % 30 == 0 && it != NULL) {
        it->play();
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case 'a':
            sounds[0]->play();
            break;
        case 's':
            sounds[1]->play();
            break;
        case 'd':
            sounds[2]->play();
            break;
        case 'f':
            sounds[3]->play();
            break;
        default:
            break;
    }

}
