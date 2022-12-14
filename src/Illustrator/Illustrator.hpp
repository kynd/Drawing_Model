#pragma once

#include "const.h"
#include "ofMain.h"
#include "PolylineUtil.hpp"


class Illustrator {
public:
    
    static vector<ofPolyline> eclipse(ofRectangle rect, float angle);
    
    static vector<ofPolyline> createSquigglePath(ofRectangle rect);
    static vector<ofPolyline> createGridPointPath(ofRectangle rect, int nx, int ny, int np);
    static vector<ofPolyline> createFastDenseSquigglePath(ofRectangle rect);
    
    static vector<ofPolyline> createWavyPath(ofRectangle rect);
    static vector<ofPolyline> createOvalPath(ofRectangle rect);
    static vector<ofPolyline> createRectanglePath(ofRectangle rect);
    
    static vector<ofPolyline> createWaveStarPath(ofRectangle rect);
    static vector<ofPolyline> createStarBlobPath(ofRectangle rect);
    static vector<ofPolyline> createBlobPath(ofRectangle rect);
    static vector<ofPolyline> createRandomQuadPath(ofRectangle rect);
    static vector<ofPolyline> createWatermelonPath(ofRectangle rect);
    static vector<ofPolyline> createTreePath(ofRectangle rect);
 
    
    static vector<ofRectangle> createRandomGrid(int nh, int nv);
    static vector<ofRectangle> createRandomSquareGrid(int n);
};
