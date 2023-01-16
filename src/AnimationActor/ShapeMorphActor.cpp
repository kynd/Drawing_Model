#include "ShapeMorphActor.hpp"

ShapeMorphActor::ShapeMorphActor(int div) {
    colorSampler.load(COMMON_COLOR_SOURCE);
    if (div == 0) {
        rects =  Illustrator::createRandomGrid(ofRandom(2, 5), ofRandom(2, 5));
    } else {
        rects =  Illustrator::createRandomGrid(ofRandom(1, 5), ofRandom(1, 5));
    }
    lines[0] = createShape();
    lines[1] = createShape();
    colors[0] = colorSampler.getRandomColor();
    colors[1] = colorSampler.getRandomColor();
    colors[2] = colorSampler.getRandomColor();
    colors[3] = colorSampler.getRandomColor();
    dirs[0] = VectorUtil::randomVec2();
    dirs[1] = VectorUtil::randomVec2();
    breadths[0] = ofRandom(1.0);
    breadths[1] = ofRandom(1.0);
    centers[0] = ofRandom(1.0);
    centers[1] = ofRandom(1.0);
}



void ShapeMorphActor::update() {
    if (frameCount % loopLength == 0) {
        lines[0] = lines[1];
        lines[1] = createShape();
        
        colors[0] = colors[1];
        colors[2] = colors[3];
        colors[1] = colorSampler.getRandomColor();
        colors[3] = colorSampler.getRandomColor();
        
        dirs[0] = dirs[1];
        dirs[1] = VectorUtil::randomVec2();
        breadths[0] = breadths[1];
        breadths[1] = ofRandom(1.0);
        centers[0] = centers[1];
        centers[1] = ofRandom(1.0);
        //colorDirectionFlag = !colorDirectionFlag;
    }
    
    float t = float(frameCount % loopLength) / (loopLength - 1);
    t = Interpolator::powerInOut(t, 4);
    frameCount ++;
    
    line = PolyLineUtil::interpolatePath(lines[0], lines[1], t, false);
}

void ShapeMorphActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    float t = float((frameCount - 1) % loopLength) / (loopLength - 1);
    t = Interpolator::powerInOut(t, 4);
    
    ofFloatColor colorA = colors[0].getLerped(colors[1], t);
    ofFloatColor colorB = colors[2].getLerped(colors[3], t);
    ofVec2f dir = dirs[0].getInterpolated(dirs[1], t);
    float center = ofLerp(centers[0], centers[1], t);
    float breadth = ofLerp(breadths[0], breadths[1], t);
    
    shared_ptr<ShaderFill> fill;
    
    if (colorDirectionFlag) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, center, breadth));
    } else {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorB, colorA, dir, center, breadth));
    }
    
    //auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir, 24));
    
    auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 1, fill, line));
    conductor.addTool(tool);
}

void ShapeMorphActor::drawMain() {
    ofNoFill();
    lines[0].draw();
    lines[1].draw();
    line.draw();
    ofDrawRectangle(rect);
}


ofPolyline ShapeMorphActor::createShape() {
    /*
    float minSize = 640;
    float x = ofRandom(BUFF_WIDTH - minSize);
    float y = ofRandom(BUFF_HEIGHT - minSize);
    float w = ofRandom(minSize, BUFF_WIDTH - x);
    float h = ofRandom(minSize, BUFF_HEIGHT - y);
    rect = ofRectangle(x, y, w, h);
     */
    rect = rects[ofRandom(rects.size())];
    
    vector<ofPolyline> polylines;
    int rnd = ofRandom(3);
    if (rnd == 0) {
        polylines = Illustrator::createRandomQuadPath(rect);
    } else if (rnd == 1) {
        polylines = Illustrator::createBlobPath(rect);
    } else {
        polylines = Illustrator::createOvalPath(rect);
    }
    
    return polylines[0];
}
