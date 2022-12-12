#pragma once

#import "ShaderFill.hpp"

class NoiseGradientShaderFill : public ShaderFill {
public:
    NoiseGradientShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir = ofVec2f(0.0, 1.0), float _center = 0.5, float _breadth = 1.0);
    
    void setRadial(ofVec2f _center = ofVec2f(0.5), float _breadth = 1.0);
    virtual void begin();
    virtual void end();
    virtual ofShader& getShader();
    
protected:
    ofFloatColor colorA, colorB;
    ofVec2f dir;
    ofVec2f center;
    bool isRadial = false;
    float breadth;
    static ofShader shader;
    static bool isInitialized;
};
