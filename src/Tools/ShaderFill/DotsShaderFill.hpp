#pragma once

#import "ShaderFill.hpp"

class DotsShaderFill : public ShaderFill {
public:
    DotsShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir);
    
    virtual void initialize();
    virtual void begin();
    virtual void end();
    virtual ofShader& getShader();
    
protected:
    ofFloatColor colorA, colorB;
    ofVec2f dir;
    static ofShader shader;
    static bool isInitialized;
};
