#pragma once

#include "StrokeStyle.hpp"

class StripeStrokeStyle : public StrokeStyle {
public:
    StripeStrokeStyle(ofFloatColor _colorA, ofFloatColor _colorB, float _freq = 16);
    virtual ofFloatColor getDebugColor();
    virtual void begin();
    virtual void end();
    virtual void beginPrint();
    virtual void endPrint();
    virtual ofShader& getShader();
    virtual ofShader& getPrintShader();
    
private:
    static ofShader shader, printShader;
    static bool isInitialized;
    ofFloatColor colorA, colorB;
    float freq;
};
