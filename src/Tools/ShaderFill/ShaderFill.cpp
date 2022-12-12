#include "ShaderFill.hpp"


ofShader ShaderFill::shader;

ShaderFill::ShaderFill() {
    
}

ofShader& ShaderFill::getShader() {
    return shader;
}

void ShaderFill::begin() {}
void ShaderFill::end() {};
void ShaderFill::preprocess(ofFbo fbo) {};
