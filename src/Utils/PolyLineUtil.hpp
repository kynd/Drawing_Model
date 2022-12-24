#pragma once

#include "const.h"
#include "ofMain.h"
#include "Interpolator.hpp"



class PolyLineUtil {
public:
    static ofPolyline toFlatStroke(ofPolyline line, float width, int resolutionn = 64);
    static ofPolyline toRoundedStroke(ofPolyline line, float width, int resolution = 64);
    
    static ofPolyline noiseWarp(ofPolyline line, int octave, float scaleMult, float decay, ofVec2f scale, ofVec2f amount, ofVec2f seed = ofVec2f(0.0));
    static ofPolyline rectangle(float x, float y, float w, float h);
    static ofPolyline oval(float x, float y, float w, float h, int resolution = 63);
    
    static ofMesh toStrokeMesh(ofPolyline line, float width, int resolution = 64, ofPolyline taper = ofPolyline());
    static ofMesh toFlatPenStrokeMesh(ofPolyline line, float width, ofVec2f dir, int resolution = 64, ofPolyline taper = ofPolyline());
    static ofMesh toRoundStrokeMesh(ofPolyline line, float width, int resolution = 64, ofPolyline taper = ofPolyline());
    
    static ofPath polylineToPath(ofPolyline line);
    
    static ofPolyline createTaperNtoN(float n0, float n1);
    
    static ofPolyline interpolatePath(ofPolyline line0, ofPolyline line1, float t, bool angleMap = false);
};
