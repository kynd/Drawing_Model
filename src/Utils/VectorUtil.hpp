#pragma once

#include "const.h"
#include "ofMain.h"


class VectorUtil {
public:
    static ofVec2f randomUnitVec2();
    static ofVec2f randomVec2(float maxLength = 1);
    static ofVec3f randomUnitVec3();
    static ofVec3f randomVec3(float maxLength = 1);
    static ofVec3f noiseVec3(float seed);
    
    static ofVec4f toV4(ofVec3f v);
    static ofVec3f toV3(ofVec4f v);
    static ofVec3f project(ofVec3f p, ofVec3f cam, ofVec3f center, float fov = 60.f, float aspect = 1.f);
    static ofVec4f projectTo4f(ofVec3f p, ofVec3f cam, ofVec3f center, float fov = 60.f, float aspect = 1.f);
};
