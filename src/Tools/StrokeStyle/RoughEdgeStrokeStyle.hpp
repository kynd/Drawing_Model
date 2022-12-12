#pragma once

#include "StrokeStyle.hpp"

class RoughEdgeStrokeStyle : public StrokeStyle {
public:
    RoughEdgeStrokeStyle(ofFloatColor _color);
    virtual void initialize();
    virtual ofFloatColor getDebugColor();
    virtual void begin();
    virtual void end();
    virtual void beginPrint();
    virtual void endPrint();
    virtual ofShader& getShader();
    virtual ofShader& getPrintShader();
    
private:
    static ofShader shader, printShader, noiseShader;
    static ofFbo noise, dummy;
    static bool isInitialized;
    ofFloatColor color;
};
