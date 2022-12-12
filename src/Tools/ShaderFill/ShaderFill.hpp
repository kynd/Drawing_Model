#pragma once

#include "const.h"
#include "ofMain.h"

class ShaderFill {
public:
    ShaderFill();
    virtual void begin();
    virtual void end();
    virtual void preprocess(ofFbo fbo);
    virtual ofShader& getShader();
    int nIterations = 1;
protected:
    static ofShader shader;
};
