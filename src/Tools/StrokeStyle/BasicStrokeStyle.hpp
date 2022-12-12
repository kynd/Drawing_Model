#pragma once

#include "StrokeStyle.hpp"

class BasicStrokeStyle : public StrokeStyle {
public:
    BasicStrokeStyle(ofFloatColor _color);
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
    ofFloatColor color;
};
