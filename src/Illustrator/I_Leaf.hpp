#pragma once

#include "const.h"
#include "ofMain.h"
#include "PolylineUtil.hpp"
#include "VectorUtil.hpp"
class I_Leaf {
public:
    static vector<vector<ofVec3f> > createVainPoints();
    static vector<vector<ofVec3f> > createStripePoints();
    static void drawPoints(vector<vector<ofVec3f> > v, ofVec3f origin, float scale);
    static vector<ofPolyline> pointsToLeaf(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    static vector<ofPolyline> pointsToLeaf02(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    static vector<ofPolyline> pointsToLeafBase(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    
    
    static vector<ofPolyline> mapPointsToLeaf(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right, vector<vector<ofVec3f> > pointVec);
    static ofVec3f ip(vector<ofVec3f> v, float t);
    static vector<vector<ofVec3f> > simpleLeafPoints(ofVec3f p, ofVec3f dir, float h, float w);
    static vector<vector<ofVec3f> > trunkPoints(ofVec3f p, ofVec3f dir, float h, float w);
};
