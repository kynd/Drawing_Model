#include "ofMain.h"
#include "ofApp.h"
#include "const.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(BUFF_WIDTH * 0.75, BUFF_HEIGHT * 0.75);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
