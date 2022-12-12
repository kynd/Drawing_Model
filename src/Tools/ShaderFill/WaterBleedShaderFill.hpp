#pragma once

#import "ShaderFill.hpp"

class WaterBleedShaderFill : public ShaderFill {
public:
    WaterBleedShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, int _nIterations = 0);
    void initialize();
    virtual void preprocess(ofFbo fbo);
    virtual void begin();
    virtual void end();
    virtual ofShader& getShader();
    
protected:
    ofFloatColor colorA, colorB;
    ofVec2f dir;
    ofFbo blurDummy, blur;
    static ofFbo noise, dummy;
    static ofShader shader, noiseShader, blurShader;
    static bool isInitialized;
    
};
