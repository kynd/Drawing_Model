
#include "StripeStrokeStyle.hpp"


bool StripeStrokeStyle::isInitialized;
ofShader StripeStrokeStyle::shader;
ofShader StripeStrokeStyle::printShader;

StripeStrokeStyle::StripeStrokeStyle(ofFloatColor _colorA, ofFloatColor _colorB, float _freq) {
    colorA = _colorA;
    colorB = _colorB;
    freq = _freq;
    if (!isInitialized) {
        isInitialized = true;
        shader.load("shader/basic.vs", "shader/stripeStroke/stroke.fs");
        printShader.load("shader/basic.vs", "shader/stripeStroke/print.fs");
    }
}

ofShader& StripeStrokeStyle::getShader() {
    return shader;
}
ofShader& StripeStrokeStyle::getPrintShader() {
    return printShader;
}

ofFloatColor StripeStrokeStyle::getDebugColor() {
    return colorA;
}

void StripeStrokeStyle::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform1f("freq", freq);
}

void StripeStrokeStyle::end() {
    shader.end();
};


void StripeStrokeStyle::beginPrint() {
    printShader.begin();
    printShader.setUniform4f("colorA", colorA);
    printShader.setUniform4f("colorB", colorB);
};

void StripeStrokeStyle::endPrint() {
    printShader.end();
};
