#pragma once

#include "ofMain.h"

#include "Runnable.hpp"
#include "Scenario.hpp"
#include "SketchScenario.hpp"
#include "SketchScenario02.hpp"
#include "AnimationScenario.hpp"
#include "StepScenario.hpp"
#include "VideoSaver.hpp"
#include "OrbitActor.hpp"
#include "BoxActor.hpp"
#include "SolarActor.hpp"

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
    
    //AnimationScenario runner;
    //SketchScenario runner;
    SketchScenario02 runner;
    //StepScenario runner;
    //shapeMorphActor runner;
    //BoxActor runner;
    //SolarActor runner;
    VideoSaver vs;
};
