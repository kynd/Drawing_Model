#include "SketchScenario.hpp"


SketchScenario::SketchScenario() {
    colorSampler.load("img/26.jpg");
    
    canvas = shared_ptr<ofFbo>(new ofFbo());
    canvas->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
 
    next();
};


void SketchScenario::next() {
    canvas->begin();
    backgroundColor = colorSampler.getRandomColor();
    ofClear(backgroundColor);
    canvas->end();
    conductor.clear();
}

void SketchScenario::dragStrokeTest() {
    for (int i = 0; i < 160; i ++) {
        ofFloatColor cbl = colorSampler.getRandomColor();
        ofFloatColor cbr = colorSampler.getRandomColor();
        ofFloatColor cel = colorSampler.getRandomColor();
        ofFloatColor cer = colorSampler.getRandomColor();
        
        canvas->begin();
        for (int i = 0; i < 120; i ++) {
            ofPushStyle();
            ofSetColor(colorSampler.getRandomColor());
            ofDrawCircle(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT), ofRandom(30, 120));
            ofPopStyle();
        }
        
        canvas->end();
        
        float w = ofRandom(6, 62);
        ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0.0).normalize();
        ofPolyline lineA, lineB;
        ofVec3f pt(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT), 0);
        for (int j = 0; j < 12; j ++) {
            pt += ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0.0).normalize() * ofRandom(8, 228);
            lineA.curveTo(pt + dir * w);
            lineB.curveTo(pt - dir * w);
        }
        shared_ptr<Tool> tool = shared_ptr<Tool>(
                             new DragStrokeTool(
                               canvas, 0,
                               lineA,
                               lineB,
                               cbl,
                               cbr,
                               cel,
                               cer,
                               backgroundColor));
        conductor.addTool(tool);
    }
    
}


void SketchScenario::grid2() {
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(randomPathTool(canvas, bgRect, 20));
    
    int n = 6;
    float xSpan = float(BUFF_WIDTH) / n;
    float ySpan = float(BUFF_HEIGHT) / n;
    vector<vector<int> > map;
    vector<ofRectangle> rects;
    for (int i = 0; i < n; i ++) {
        vector<int> row;
        for (int j = 0; j < n; j ++) {
            row.push_back(0);
        }
        map.push_back(row);
    }
    for (int i = 0; i < n * n; i ++) {
        int x = ofRandom(n);
        int y = ofRandom(n);
        int w = ofRandom(n - x) + 1;
        int h = ofRandom(n - y) + 1;
        bool flag = false;
        for (int i = x; i < x + w; i ++) {
            for (int j = y; j < y + h; j ++) {
                if (map[i][j] == 1) {flag = true;}
            }
        }
        if (!flag) {
            rects.push_back(ofRectangle(x * xSpan, y * ySpan, w * xSpan, h * ySpan));
            for (int i = x; i < x + w; i ++) {
                for (int j = y; j < y + h; j ++) {
                    map[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines;
        float rnd = ofRandom(1.0);
        if (rnd < 0.25) {
            polylines = Illustrator::createBlobPath(rects[i]);
        } else if (rnd < 0.5) {
            polylines = Illustrator::createBlobPath(rects[i]);
            //polylines = Illustrator::createWatermelonPath(rects[i]);
        } else if (rnd < 0.75) {
            polylines = Illustrator::createWavyPath(rects[i]);
        } else {
            polylines = Illustrator::createStarBlobPath(rects[i]);
        }
        
        for (int i = 0; i < polylines.size(); i ++) {
            shared_ptr<Tool> tool = randomPathTool(canvas, polylines[i], ofRandom(1, 10));
            conductor.addTool(tool);
        }
    }
}


void SketchScenario::grid() {
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(randomPathTool(canvas, bgRect, 20));
    
    int n = 4;
    for (int nx = 0; nx < n; nx ++) {
        for (int ny = 0; ny < n; ny ++) {
            int span = ofRandom(1, 4);
            span = min(span, n - ny);
            float x = float(BUFF_WIDTH) / n * nx;
            float y = float(BUFF_HEIGHT) / n * ny;
            float w = float(BUFF_WIDTH) / n;
            float h = float(BUFF_HEIGHT) / n * span;
            
            ofPolyline bgRect = PolyLineUtil::rectangle(x, y, w, h);
            //conductor.addTool(randomPathTool(bgRect, 20));
            
            vector<ofPolyline> polylines = Illustrator::createBlobPath(ofRectangle(x, y, w, h));
            
            for (int i = 0; i < polylines.size(); i ++) {
                shared_ptr<Tool> tool = randomPathTool(canvas, polylines[i], ofRandom(1, 10));
                conductor.addTool(tool);
            }
            
            ny += (span - 1);
        }
    }
}

void SketchScenario::watermelons() {
    
    ofPolyline bgRect = PolyLineUtil::rectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    conductor.addTool(randomPathTool(canvas, bgRect, 20));
    
    int n = 5;
    for (int nx = 0; nx < n; nx ++) {
        for (int ny = 0; ny < n; ny ++) {
            int span = ofRandom(1, 4);
            span = min(span, n - ny);
            float x = float(BUFF_WIDTH) / n * nx;
            float y = float(BUFF_HEIGHT) / n * ny;
            float w = float(BUFF_WIDTH) / n;
            float h = float(BUFF_HEIGHT) / n * span;
            
            ofPolyline bgRect = PolyLineUtil::rectangle(x, y, w, h);
            //conductor.addTool(randomPathTool(bgRect, 20));
            
            vector<ofPolyline> polylines = Illustrator::createWatermelonPath(ofRectangle(x, y, w, h));
            
            for (int i = 0; i < polylines.size(); i ++) {
                shared_ptr<Tool> tool = randomPathTool(canvas, polylines[i], ofRandom(1, 10));
                conductor.addTool(tool);
            }
            
            ny += (span - 1);
        }
    }
}

void SketchScenario::blobPathTest() {
    int n = ofRandom(3, 12);
    for (int i = 0; i < n; i ++) {
        ofPolyline polyline = polyBlob();
        if (ofRandom(1.0) < 0.5) {
            conductor.addTool(randomPathTool(canvas, polyline, ofRandom(0, 10)));
        }
        if (ofRandom(1.0) < 0.5) {
            conductor.addTool(randomStrokeTool(canvas, polyline, ofRandom(0, 10)));
        }
    }
}

void SketchScenario::gridFBOTest() {
    for (int k = 0; k < 2; k ++) {
        int n = k == 0 ? 4 : 8;
        float w = float(BUFF_WIDTH) / n;
        float h = float(BUFF_HEIGHT) / n;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                ofFbo fbo;
                fbo.allocate(w, h, fboDepth, samplingDepth);
                fbo.begin();
                ofClear(0, 0, 0, 0);
                ofDrawCircle(ofRandom(w), ofRandom(h), w);
                fbo.end();
                
                if (ofRandom(1.0) < 0.5) {
                    conductor.addTool(randomFboTool(canvas, fbo, ofVec2f(w * i, h * j), ofRandom(0, 10)));
                }
            }
        }
    }
}


shared_ptr<Tool> SketchScenario::randomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority) {
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    shared_ptr<ShaderFill> fill;
    
    float rnd = ofRandom(7.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 5.0) {
        fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
    } else if (rnd < 6.0) {
        fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
    } else {
        fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
    }
    
    auto tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, polyline));
    return tool;
}

shared_ptr<Tool> SketchScenario::randomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority) {
    shared_ptr<Tool> tool;
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    
    float rnd = ofRandom(7.0);
    if (rnd < 1.0) {
        auto fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 2.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(_fill);
        
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 4.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, fbo, pos));
    } else if (rnd < 5.0) {
        auto fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, fbo, pos));
    } else if (rnd < 6.0) {
        auto fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, ofRandom(10), fill, fbo, pos));
    } else {
        auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    }
    return tool;
}





shared_ptr<Tool> SketchScenario::randomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority, float minW, float maxW) {
    ofFloatColor color = colorSampler.getRandomColor();
    shared_ptr<Tool> tool;
    shared_ptr<StrokeStyle> style;
    float width;
    
    ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 1);
    float rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        width = ofRandom(1, 12);
        style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(color));
    } else if (rnd < 2.0) {
        width = ofRandom(1, 12);
        style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
    } else {
        width = ofRandom(4, 12);
        float freq = width / ofRandom(2, 4);
        style = shared_ptr<StrokeStyle>(new StripeStrokeStyle(color, colorSampler.getRandomColor(), freq));
    }
    
    rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        tool = shared_ptr<Tool>(new BasicStrokeTool(_canvas, priority, style, polyline, width, taper));
    } else if (rnd < 2.0) {
        tool = shared_ptr<Tool>(new FlatPenStrokeTool(_canvas, priority, style, polyline, width, ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)), taper));
    } else {
        tool = shared_ptr<Tool>(new RoundStrokeTool(_canvas, priority, style, polyline, width, taper));
    }
    return tool;
}

void SketchScenario::update() {
    conductor.update();
};

void SketchScenario::draw() {
    canvas->draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (debugFlag || animationDebugFlag) {
        conductor.debugDraw();
    }
    if (debugFlag) {
        conductor.debugDraw();
    }
}

ofRectangle SketchScenario::randomRect(float minW, float minH, float maxW, float maxH) {
    float w = ofRandom(minW, maxW);
    float h = ofRandom(minH, maxH);
    float x = ofRandom(0, BUFF_WIDTH - w);
    float y = ofRandom(0, BUFF_HEIGHT - h);
    return ofRectangle(x, y, w, h);
}

ofRectangle SketchScenario::randomRect2(float minW, float minH, float maxW, float maxH) {
    float w = ofRandom(minW, maxW);
    float h = ofRandom(minH, maxH);
    float x = ofRandom(0 - w * 0.5, BUFF_WIDTH - w * 0.5);
    float y = ofRandom(0 - h * 0.5, BUFF_HEIGHT - h * 0.5);
    return ofRectangle(x, y, w, h);
}

ofPolyline SketchScenario::polyBlob() {
    float angleOffset = ofRandom(TWO_PI);
    float x = ofRandom(BUFF_WIDTH);
    float y = ofRandom(BUFF_HEIGHT);
    int nVertices = ofRandom(3, 36);
    float radius = ofRandom(BUFF_WIDTH / 8, BUFF_WIDTH / 2);
    ofPolyline polyline;
    vector<ofVec3f> pts;
    for (int i = 0; i < nVertices; i ++) {
        int idx = i % nVertices;
        float ang = TWO_PI / nVertices * idx + angleOffset;
        float r = radius * ofRandom(0.5, 1.5);
        pts.push_back(ofVec3f(cos(ang) * r + x, sin(ang) * r + y, 0.0));
    }
    for (int i = 0; i <= nVertices + 2; i ++) {
        int idx = i % nVertices;
        polyline.curveTo(pts[idx]);
    }
    polyline.close();
    return polyline;
}

vector<ofRectangle> SketchScenario::createRandomGrid(int nh, int nv) {
    float xSpan = float(BUFF_WIDTH) / nh;
    float ySpan = float(BUFF_HEIGHT) / nv;
    vector<vector<int> > map;
    vector<ofRectangle> rects;
    for (int i = 0; i < nh; i ++) {
        vector<int> column;
        for (int j = 0; j < nv; j ++) {
            column.push_back(0);
        }
        map.push_back(column);
    }
    for (int i = 0; i < nh * nv; i ++) {
        int x = ofRandom(nh);
        int y = ofRandom(nv);
        int w = ofRandom(nh - x) + 1;
        int h = ofRandom(nv - y) + 1;
        bool flag = false;
        for (int i = x; i < x + w; i ++) {
            for (int j = y; j < y + h; j ++) {
                if (map[i][j] == 1) {flag = true;}
            }
        }
        if (!flag) {
            rects.push_back(ofRectangle(x * xSpan, y * ySpan, w * xSpan, h * ySpan));
            for (int i = x; i < x + w; i ++) {
                for (int j = y; j < y + h; j ++) {
                    map[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < nh; i ++) {
        for (int j = 0; j < nv; j ++) {
            if (map[i][j] != 1) {
                rects.push_back(ofRectangle(i * xSpan, j * ySpan, xSpan, ySpan));
            }
        }
    }
    return rects;
}

vector<ofRectangle> SketchScenario::createRandomSquareGrid(int n) {
    float xSpan = float(BUFF_WIDTH) / n;
    float ySpan = float(BUFF_HEIGHT) / n;
    vector<vector<int> > map;
    vector<ofRectangle> rects;
    for (int i = 0; i < n; i ++) {
        vector<int> column;
        for (int j = 0; j < n; j ++) {
            column.push_back(0);
        }
        map.push_back(column);
    }
    for (int i = 0; i < n * n; i ++) {
        int x = ofRandom(n);
        int y = x;
        int w = ofRandom(n - x) + 1;
        int h = w;
        bool flag = false;
        for (int i = x; i < x + w; i ++) {
            for (int j = y; j < y + h; j ++) {
                if (map[i][j] == 1) {flag = true;}
            }
        }
        if (!flag) {
            rects.push_back(ofRectangle(x * xSpan, y * ySpan, w * xSpan, h * ySpan));
            for (int i = x; i < x + w; i ++) {
                for (int j = y; j < y + h; j ++) {
                    map[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (map[i][j] != 1) {
                rects.push_back(ofRectangle(i * xSpan, j * ySpan, xSpan, ySpan));
            }
        }
    }
    return rects;
}


void SketchScenario::imageTest() {
    ofImage img;
    img.load("img/PXL_20220721_034107723.jpg");
    ofShader maskShader;
    maskShader.load("shader/basic.vs", "shader/colorPrint/colorMaskPrint.fs");
    
    for(int i = 0; i < 10; i ++) {
        ofFbo fbo;
        fbo.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
        fbo.begin();
        maskShader.begin();
        maskShader.setUniform4f("keyColor", ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)));
        img.draw(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
        maskShader.end();
        fbo.end();
        auto tool = randomFboTool(canvas, fbo, ofVec2f(0,0));
        conductor.addTool(tool);
    }
}



void SketchScenario::randomGridTest() {
    vector<ofRectangle> rects = createRandomGrid(8, 8);
    for (int i = 0; i < rects.size(); i ++) {
        ofFloatColor colorA = colorSampler.getRandomColor();
        ofFloatColor colorB = colorSampler.getRandomColor();
        ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        auto fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
        vector<ofPolyline> polylines = Illustrator::createRectanglePath(rects[i]);
        auto tool = randomPathTool(canvas, polylines[0]);
        if (ofRandom(1.0) < 0.4) {
            conductor.addTool(tool);
        }
    }
}

void SketchScenario::randomGridTest2() {
    vector<ofRectangle> rects = createRandomGrid(4, 4);
    for (int i = 0; i < rects.size(); i ++) {
        ofFloatColor colorA = colorSampler.getRandomColor();
        ofFloatColor colorB = colorSampler.getRandomColor();
        ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        auto fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
        vector<ofPolyline> polylines = Illustrator::createOvalPath(rects[i]);
        
        polylines[0] = PolyLineUtil::noiseWarp(polylines[0], 3, 8, 0.1, ofVec2f(0.0005), ofVec2f(200));
        if(ofRandom(1.0) < 0.25) {
            auto tool = randomPathTool(canvas, polylines[0]);
            conductor.addTool(tool);
        }
    }
}


void SketchScenario::paintTest() {
    
    vector<ofRectangle> rects = createRandomGrid(8, 8);
    for (int i = 0; i < rects.size(); i ++) {
        ofFloatColor colorA = colorSampler.getRandomColor();
        ofFloatColor colorB = colorSampler.getRandomColor();
        ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        auto fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
        vector<ofPolyline> polylines = Illustrator::createBlobPath(rects[i]);
        auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, ofRandom(10), fill, polylines[0]));
        conductor.addTool(tool);
    }
}


void SketchScenario::squiggleTest() {
    vector<ofRectangle> rects = createRandomGrid(5, 5);
    for (int i = 0; i < rects.size(); i ++) {
        vector<ofPolyline> polylines = Illustrator::createSquigglePath(rects[i]);
        auto strokeTool = randomStrokeTool(canvas, polylines[0], 0, 10, 40);
        conductor.addTool(strokeTool);
    }
}
