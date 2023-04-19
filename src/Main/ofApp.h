#pragma once

#include "ofMain.h"

#include "Runnable.hpp"
#include "Scenario.hpp"
#include "SketchScenario.hpp"
#include "SketchScenario02.hpp"
#include "AnimationScenario.hpp"
#include "StepScenario.hpp"
#include "VideoSaver.hpp"

#include "I_Leaf.hpp"
#include "I_Tree.hpp"
#include "TreeActor.hpp"

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
    //DrapeActor runner;
    //CandyClashActor runner;
    //SquishyActor runner;
    //TreeActor runner;
    VideoSaver vs;
};
