#pragma once

#import "ShaderFill.hpp"

class SlideBleedShaderFill : public ShaderFill {
public:
    SlideBleedShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, int _nIterations = 0);
    void initialize();
    virtual void begin();
    virtual void end();
    virtual ofShader& getShader();
    
protected:
    ofFloatColor colorA, colorB;
    ofVec2f dir;
    static ofShader shader;
    static bool isInitialized;
    
};
