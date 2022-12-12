
#include "StrokeStyle.hpp"


ofShader StrokeStyle::shader;

StrokeStyle::StrokeStyle() {
    
}


ofMesh StrokeStyle::polylineToMesh(ofPolyline line){
    ofMesh mesh;
    return mesh;
}

ofShader& StrokeStyle::getShader() {
    return shader;
}

ofShader& StrokeStyle::getPrintShader() {
    return shader;
}

ofFloatColor StrokeStyle::getDebugColor() {
    return ofFloatColor();
}

void StrokeStyle::begin() {}
void StrokeStyle::end() {};

void StrokeStyle::beginPrint() {}
void StrokeStyle::endPrint() {};
