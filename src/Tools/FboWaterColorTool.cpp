#include "FboWaterColorTool.hpp"

bool FboWaterColorTool::isInitialized = false;
ofFbo FboWaterColorTool::dummy, FboWaterColorTool::noise;
ofShader FboWaterColorTool::noiseShader;
ofShader FboWaterColorTool::blurShader;
ofShader FboWaterColorTool::blobProcessShader;
ofShader FboWaterColorTool::colorPrintShader;

FboWaterColorTool::FboWaterColorTool(shared_ptr<ofFbo> _canvas, int _priority, ofFbo fbo, ofVec2f pos, ofFloatColor _color) : Tool(_canvas, _priority) {
    
    if (!isInitialized) { initialize(); }
    color = _color;
    maxCnt = 12;
    boundingBox = ofRectangle(pos.x - margin, pos.y - margin, fbo.getWidth() + margin * 2, fbo.getHeight() + margin * 2);
    
   base.allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
   base.begin();
   colorPrintShader.begin();
   colorPrintShader.setUniform4f("color", color);
   fbo.draw(margin, margin);
   colorPrintShader.end();
   base.end();
   setup();
}

void FboWaterColorTool::initialize() {
    isInitialized = true;
    
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, GL_RGBA32F, 4);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, GL_RGBA32F, 4);
    blurShader.load("shader/basic.vs", "shader/blob/blur.fs");
    blobProcessShader.load("shader/basic.vs", "shader/blob/blobProcess.fs");
    noiseShader.load("shader/basic.vs", "shader/blob/noise.fs");
    colorPrintShader.load("shader/basic.vs", "shader/blob/colorPrint.fs");
    
    noise.begin();
    ofClear(0, 0, 0);
    noiseShader.begin();
    noiseShader.setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    dummy.draw(0, 0);
    noiseShader.end();
    noise.end();
}

void FboWaterColorTool::setupMain() {
    blur.allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
    workspace.allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
    original.allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
    pingpong[0].allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
    pingpong[1].allocate(boundingBox.width, boundingBox.height, GL_RGBA32F, 4);
    
    workspace.begin();
    blurShader.begin();
    blurShader.setUniform2f("dir", ofVec2f(1, 0));
    base.draw(0,0);
    blurShader.end();
    workspace.end();
    
    blur.begin();
    blurShader.begin();
    blurShader.setUniform2f("dir", ofVec2f(0, 1));
    workspace.draw(0,0);
    blurShader.end();
    blur.end();
}

void FboWaterColorTool::activateMain() {
    original.begin();
    ofPushMatrix();
    canvas->draw(-boundingBox.x, -boundingBox.y);
    ofPopMatrix();
    original.end();
    
    pingpong[0].begin();
    ofPushMatrix();
    canvas->draw(-boundingBox.x, -boundingBox.y);
    ofPopMatrix();
    pingpong[0].end();
}



void FboWaterColorTool::updateMain() {
    int i0 = pIdx;
    int i1 = (pIdx + 1) % 2;
    
    // PingPong
    pingpong[i1].begin();
    blobProcessShader.begin();
    blobProcessShader.setUniformTexture("base", base, 1);
    blobProcessShader.setUniformTexture("blur", blur, 2);
    blobProcessShader.setUniformTexture("original", original, 3);
    blobProcessShader.setUniformTexture("noise", noise, 4);
    blobProcessShader.setUniform2f("pos", boundingBox.getTopLeft());
    
    pingpong[i0].draw(0, 0);
    
    blobProcessShader.end();
    pingpong[i1].end();
    pIdx = i1;
    
    // Draw pn canvas
    canvas->begin();
    //pathShape.draw();
    ofPushMatrix();
    ofTranslate(boundingBox.getTopLeft());
    //blur.draw(0,0);
    pingpong[pIdx].draw(0, 0);
    ofPopMatrix();
    ofPopStyle();
    //noise.draw(0, 0);
    canvas->end();
    
    // progress
    cnt ++;
    if (cnt >= maxCnt) {
        finalize();
    }
    
}

void FboWaterColorTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(color);
    base.draw(boundingBox.x, boundingBox.y);
    ofDrawRectangle(boundingBox);
    ofPopStyle();
}
