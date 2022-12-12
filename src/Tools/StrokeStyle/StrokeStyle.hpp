
#pragma once

#include "const.h"
#include "ofMain.h"
#include "PolylineUtil.hpp"

class StrokeStyle {
public:
    StrokeStyle();
    virtual ofMesh polylineToMesh(ofPolyline line);
    virtual void begin();
    virtual void end();
    virtual void beginPrint();
    virtual void endPrint();
    virtual ofFloatColor getDebugColor();
    virtual ofShader& getShader();
    virtual ofShader& getPrintShader();
    static ofShader shader;
};
