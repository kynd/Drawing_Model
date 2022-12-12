#pragma once
#include "ofMain.h"

class VideoSaver {
public:
    VideoSaver();
    
    void save(ofFbo& fbo);
    void save(ofRectangle rect = ofRectangle(0,0,0,0));
    void saveTS(ofRectangle rect = ofRectangle(0,0,0,0));
    void setNum(int n);
private:
    void saveFile(ofRectangle rect = ofRectangle(0,0,0,0));
    int num;
    string file_name;
    ofImage img_saver;
    static int counter;
    static int baseTime;
};
