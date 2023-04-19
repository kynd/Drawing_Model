#pragma once

#include "const.h"
#include "ofMain.h"
#include "PolylineUtil.hpp"

struct MP{
    ofVec3f p, v;
};

class Branch {
public:
    Branch(ofVec3f p, ofVec3f v, float len, float t, int nChild, float seed);
    
    vector<ofVec3f> points;
    vector<Branch> children;
};


class I_Tree {
public:
    
    static Branch createTree(float t, float seed);
    static vector<ofPolyline> branchToPolylines(Branch b, ofVec3f o, float scale);
    static vector<vector<ofVec3f> > branchToPointVectors(Branch b);
    static MP getMidPoint(vector<ofVec3f> arr, int arrMaxLen, float t);
    
    /*
    static vector<vector<ofVec3f> > createVainPoints();
    static void drawPoints(vector<vector<ofVec3f> > v, ofVec3f origin, float scale);
    static vector<ofPolyline> pointsToLeaf(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    static vector<ofPolyline> pointsToLeafBase(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    static vector<ofPolyline> pointsToLeafVains(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right);
    static ofVec3f ip(vector<ofVec3f> v, float t);
    */
};
