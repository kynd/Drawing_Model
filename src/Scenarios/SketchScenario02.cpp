#include "SketchScenario02.hpp"


SketchScenario02::SketchScenario02() {
    colorSampler.load(COMMON_COLOR_SOURCE);
    
    canvas = shared_ptr<ofFbo>(new ofFbo());
    canvas->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
 
    next();
};


void SketchScenario02::next() {
    canvas->begin();
    backgroundColor = colorSampler.getRandomColor();
    ofClear(backgroundColor);
    canvas->end();
    
    conductor.clear();
    maskTest();
}

vector<ofPolyline> SketchScenario02::randomPaths(ofRectangle rect) {
    int rnd = ofRandom(5);
    if (rnd == 0) {
        return Illustrator::createWavyPath(rect);
    } else if (rnd == 1) {
        return Illustrator::createRandomQuadPath(rect);
    } else if (rnd == 2) {
        return Illustrator::createStarBlobPath(rect);
    } else if (rnd == 3) {
        return Illustrator::createOvalPath(rect);
    } else {
        return Illustrator::createBlobPath(rect);
    }
    return Illustrator::createBlobPath(rect);
}

void SketchScenario02::starTest() {
    vector<ofRectangle> rects;
    
    for (int i = 0; i < 120; i ++) {
        float w = ofRandom(50, 100);
        float x = ofRandom(BUFF_WIDTH - w);
        float h = w;
        float y = ofRandom(BUFF_HEIGHT - h);
        rects.push_back(ofRectangle(x,y,w,h));
    }
    
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        polylines = Illustrator::createStarBlobPath(rects[i]);
        
        for (int j = 0; j < polylines.size(); j ++) {
            ofFloatColor colorA = ofFloatColor(1,1,1,1);
            ofFloatColor colorB = colorSampler.getRandomColor();
            ofVec2f dir = VectorUtil::randomVec2();
            
            auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
            
            int priority = ofRandom(10);
            
            auto tool2 = toolUtil.getRandomPathTool(canvas, polylines[j], priority);
            
            conductor.addTool(tool2);
            
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, polylines[j]));
            
            conductor.addTool(tool);
        }
    }
}

void SketchScenario02::treeTest() {
    
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(toolUtil.getRandomPathTool(canvas, bgRect, 20));
    
    vector<ofRectangle> rects;
    
    for (int i = 0; i < 12; i ++) {
        float w = ofRandom(BUFF_WIDTH / 6, BUFF_WIDTH);
        float x = ofRandom(BUFF_WIDTH - w);
        float h = ofRandom(BUFF_HEIGHT / 3, BUFF_HEIGHT);
        float y = ofRandom(BUFF_HEIGHT - h);
        rects.push_back(ofRectangle(x,y,w,h));
    }
    //rects = Illustrator::createRandomGrid(ofRandom(1,5), ofRandom(1,5));
    
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        polylines = Illustrator::createTreePath(rects[i]);
        
        for (int j = 0; j < polylines.size(); j ++) {
            
            ofFloatColor colorA = colorSampler.getRandomColor();
            ofFloatColor colorB = colorSampler.getRandomColor();
            ofVec2f dir = VectorUtil::randomVec2();
            
            auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
            
            int priority = ofRandom(10);
            auto tool2 = toolUtil.getRandomPathTool(canvas, polylines[j], priority );
            
            conductor.addTool(tool2);
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority , fill, polylines[j]));
            
            conductor.addTool(tool);
        }
    }
}

void SketchScenario02::pathMorphTest() {
    for (int i = 0; i < 360 * 4; i ++) {
        shapeMorphActor.update();
        shapeMorphActor.updateConductor(canvas, conductor);
        conductor.tools[conductor.tools.size()-1]->setPriority(i);
    }
}


void SketchScenario02::shaderFillTest() {
    auto line = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    auto tool = toolUtil.getRandomPathTool(canvas, line, 2000);
    conductor.addTool(tool);
    
    MaskTool* mt = new MaskTool(canvas, ofRandom(10));
    auto maskTool = shared_ptr<Tool>(mt);
    conductor.addTool(maskTool);
    {
        vector<ofRectangle> rects = Illustrator::createRandomSquareGrid(ofRandom(1, 4));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(ofFloatColor(0,0,0,1),ofFloatColor(0, 0,0,1)));
        for (int i = 0; i < rects.size(); i ++) {
            vector<ofPolyline> polylines = randomPaths(rects[i]);
            for (int j = 0; j < polylines.size(); j ++) {
                
                ofPolyline line = polylines[j];//PolyLineUtil::noiseWarp(polylines[j], 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(20));
                auto tool = shared_ptr<Tool>(new ShaderFillTool(mt->getMask(), -1, fill, line));
                mt->addMask(tool);
                

                line.translate(ofVec3f(ofRandom(-24, 24), ofRandom(-24, 24), ofRandom(-24, 24)));
                auto tool2 = toolUtil.getRandomPathTool(canvas, line, 1000);
                conductor.addTool(tool2);
                
                line.translate(ofVec3f(ofRandom(-24, 24), ofRandom(-24, 24), ofRandom(-24, 24)));
                auto tool3 = toolUtil.getRandomPathTool(canvas, line, 1000);
                conductor.addTool(tool3);
            }
        }
    }
    
    vector<ofRectangle> rects = Illustrator::createRandomSquareGrid(ofRandom(1, 6));
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines = randomPaths(rects[i]);
        for (int j = 0; j < polylines.size(); j ++) {
            
            ofPolyline line = PolyLineUtil::noiseWarp(polylines[j], 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(20));
            auto tool = toolUtil.getRandomPathTool(canvas, line, ofRandom(10));
            mt->addTool(tool);
        }
    }
};


void SketchScenario02::randomBgTest() {
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(toolUtil.getRandomPathTool(canvas, bgRect, 20));
}

void SketchScenario02::dottedLineTest() {
    
    vector<ofRectangle> rects = Illustrator::createRandomGrid(ofRandom(1,5), ofRandom(1,5));
    
    
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        float rnd = ofRandom(3.0);
        if (rnd < 1.0) {
            polylines = Illustrator::createBlobPath(rects[i]);
        } else if (rnd < 2.0) {
            polylines = Illustrator::createOvalPath(rects[i]);
        } else {
            polylines = Illustrator::createRandomQuadPath(rects[i]);
        }
        
        if (ofRandom(1.0) < 0.25) {
            polylines[0] = PolyLineUtil::noiseWarp(polylines[0], 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(200));
        }
        
        {
            auto tool = toolUtil.getRandomPathTool(canvas, polylines[0], 0);
            tool->setPriority(ofRandom(5, 10));
            conductor.addTool(tool);
        }
        
        {
            float baseSpan = ofRandom(24, 48);
            polylines = PolyLineUtil::toDottedLine(polylines[0], baseSpan, ofRandom(baseSpan));
            ofFloatColor color = colorSampler.getRandomColor();
            float width = ofRandom(1, 12);
            auto style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
            for (int i = 0; i < polylines.size(); i ++) {
                auto tool = shared_ptr<Tool>(new RoundStrokeTool(canvas, 1, style, polylines[i], width));
                conductor.addTool(tool);
            }
        }
        
    }
    
    /*
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        float rnd = ofRandom(3.0);
        if (rnd < 1.0) {
            polylines = Illustrator::createSquigglePath(rects[i]);
        } else if (rnd < 2.0) {
            polylines = Illustrator::createFastDenseSquigglePath(rects[i]);
        } else {
            polylines = Illustrator::createGridPointPath(rects[i], 4, 4, ofRandom(4, 12));
        }
        
        if (ofRandom(1.0) < 0.25) {
            polylines[0] = PolyLineUtil::noiseWarp(polylines[0], 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(200));
        }
        
        float baseSpan = ofRandom(24, 48);
        polylines = PolyLineUtil::toDottedLine(polylines[0], baseSpan, ofRandom(baseSpan));
        ofFloatColor color = colorSampler.getRandomColor();
        float width = ofRandom(1, 12);
        auto style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
        for (int i = 0; i < polylines.size(); i ++) {
            auto tool = shared_ptr<Tool>(new RoundStrokeTool(canvas, 0, style, polylines[i], width));
            conductor.addTool(tool);
        }
    }
    */
    
    boxActor.update();
    boxActor.updateConductor(canvas, conductor);
}


void SketchScenario02::lineTest() {
    vector<ofRectangle> rects = Illustrator::createRandomGrid(ofRandom(1,5), ofRandom(1,5));
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        float rnd = ofRandom(3.0);
        if (rnd < 1.0) {
            polylines = Illustrator::createSquigglePath(rects[i]);
        } else if (rnd < 2.0) {
            polylines = Illustrator::createFastDenseSquigglePath(rects[i]);
        } else {
            polylines = Illustrator::createGridPointPath(rects[i], 4, 4, ofRandom(4, 12));
        }
        
        if (ofRandom(1.0) < 0.25) {
            polylines[0] = PolyLineUtil::noiseWarp(polylines[0], 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(200));
        }
        auto strokeTool = toolUtil.getRandomStrokeTool(canvas, polylines[0], 0, 1, 40);
        conductor.addTool(strokeTool);
    }
}

void SketchScenario02::lineTestSpecific() {
    vector<ofRectangle> rects = Illustrator::createRandomGrid(ofRandom(1,5), ofRandom(1,5));
    rects.push_back(ofRectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT));
    ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.2);
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        polylines = Illustrator::createGridPointPath(rects[i], 4, 4, ofRandom(4, 12));
        //createSquigglePath(rects[i]);
        float w = ofRandom(16, 128) * 2;
        float freq = w / ofRandom(8, 64);
        auto style = shared_ptr<StrokeStyle>(new StripeStrokeStyle(colorSampler.getRandomColor(), colorSampler.getRandomColor(), freq));
        auto tool = shared_ptr<Tool>(new RoundStrokeTool(canvas, ofRandom(0,10), style, polylines[0], w, taper));
        conductor.addTool(tool);
    }
}


void SketchScenario02::maskTest() {
    vector<ofRectangle> rects = Illustrator::createRandomSquareGrid(ofRandom(1, 16));
    for (int i = 0; i < rects.size(); i ++) {
        MaskTool* mt = new MaskTool(canvas, ofRandom(10));
        auto maskTool = shared_ptr<Tool>(mt);
        auto _fill = new NoiseGradientShaderFill(ofFloatColor(1,1,1,1),ofFloatColor(0,0,0,1));
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(_fill);
        
        vector<ofPolyline> polylines = Illustrator::createBlobPath(rects[i]);
        auto tool = shared_ptr<Tool>(new ShaderFillTool(mt->getMask(), -1, fill, polylines[0]));
        mt->addMask(tool);
        
        for (int j = 0; j < 2; j ++) {
            vector<ofPolyline> polylines = Illustrator::createBlobPath(rects[i]);
            auto tool = toolUtil.getRandomPathTool(mt->getLocalCanvas(), polylines[0], 0);
            if (ofRandom(1.0) < 0.5) {
                mt->addTool(tool);
            }
            auto strokeTool = toolUtil.getRandomStrokeTool(mt->getLocalCanvas(), polylines[0], 0, 10, 40);
            if (ofRandom(1.0) < 0.5) {
                mt->addTool(strokeTool);
            }
        }
        {
            vector<ofPolyline> polylines = Illustrator::createSquigglePath(rects[i]);
            auto strokeTool = toolUtil.getRandomStrokeTool(mt->getLocalCanvas(), polylines[0], 0, 10, 40);
            mt->addTool(strokeTool);
        }
        conductor.addTool(maskTool);
    }
}


void SketchScenario02::groupTest() {
    
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(toolUtil.getRandomPathTool(canvas, bgRect, 20));
    
    int n = ofRandom(16, 24);
    for (int i = 0; i < n; i ++) {
        GroupTool* gt = new GroupTool(canvas, ofRandom(10));
        auto groupTool = shared_ptr<Tool>(gt);
        auto _fill = new NoiseGradientShaderFill(colorSampler.getRandomColor(),colorSampler.getRandomColor());
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(_fill);
        
        ofVec3f center(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT), 0);
        for (int j = 0; j < 48; j ++) {
            float angA = ofRandom(TWO_PI);
            float angB = angA + ofRandom(TWO_PI) / 16;
            float distA = ofRandom(BUFF_WIDTH / 4);
            float distB = ofRandom(BUFF_WIDTH / 4);
            ofVec3f pA = center + ofVec3f(cos(angA) * distA, sin(angA) * distA);
            
            ofVec3f pB = center + ofVec3f(cos(angB) * distB, sin(angB) * distB);
            ofPolyline polyline;
            polyline.addVertex(center);
            polyline.addVertex(pA);
            polyline.addVertex(pB);
            
            
            polyline = PolyLineUtil::noiseWarp(polyline, 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(200));
            
            
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, fill, polyline));
            gt->addTool(tool);
        }
        conductor.addTool(groupTool);
    }
}

void SketchScenario02::draw() {
    canvas->draw(0, 0, ofGetWidth(), ofGetHeight());
    if (debugFlag || animationDebugFlag) {
        conductor.debugDraw();
    }
    if (debugFlag) {
        conductor.debugDraw();
    }
}
