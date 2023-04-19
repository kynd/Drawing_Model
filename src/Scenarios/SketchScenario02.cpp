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
    //leafTest4();
    vainTest();
    vainTest();
    trunksTest();
    trunksTest();
}

void SketchScenario02::trunksTest() {
    int LN = 4;
    for (int kk = 0; kk < 2; kk ++) {
        for (int k = 0; k < LN; k ++) {
            GroupTool* gt = new GroupTool(canvas, ofRandom(10));
            auto groupTool = shared_ptr<Tool>(gt);
            vector<ofVec3f> center;
            vector<ofVec3f> left, right;
            
            ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), k % 2 == 0 ? 0 : BUFF_HEIGHT);
           ofVec3f dir = ofVec3f(0, k % 2 == 0 ? 1 : -1, 0);
            
            if (kk == 0) {
                p.y = k % 2 == 0 ? BUFF_HEIGHT  : 0;
                dir.y = k % 2 == 0 ? -1 : 1;
            }
            float rnd = ofRandom(1.0);
            float hm = ofRandom(0.2, 0.5);
            float wm = hm * ofRandom(0.01, 0.2);
            vector<vector<ofVec3f> > points = I_Leaf::trunkPoints(p, dir, BUFF_HEIGHT, BUFF_WIDTH * wm);
            if (rnd < 0.5) {
                vector<ofPolyline> polylines = I_Leaf::pointsToLeaf02(points[0], points[1], points[2]);
                
                for (int i = 0; i < polylines.size(); i ++) {
                    ofPolyline line = polylines[i];
                    auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                    gt->addTool(tool);
                    
                }
            } else {
                vector<ofPolyline> polylines = I_Leaf::pointsToLeaf(points[0], points[1], points[2]);
                
                ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.5);
                ofFloatColor scolor = toolUtil.getRandomColor();
                
                for (int i = 0; i < polylines.size(); i ++) {
                    ofPolyline line = polylines[i];
                    if (i < 2) {
                        auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                        gt->addTool(tool);
                    } else {
                        
                        float width = ofRandom(1, 6);
                        auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(scolor));
                        auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, int(polylines.size()) - i, style, line, width, taper));
                        gt->addTool(tool);
                    }
                }
            }
            conductor.addTool(groupTool);
        }
    }
}

void SketchScenario02::vainTest() {
    int LN = 4;
    for (int k = 0; k < LN; k ++) {
        GroupTool* gt = new GroupTool(canvas, ofRandom(10));
        auto groupTool = shared_ptr<Tool>(gt);
        vector<ofVec3f> center;
        vector<ofVec3f> left, right;
        
        ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT));
        //ofVec3f p = ofVec3f(BUFF_WIDTH / 2, ofRandom(BUFF_HEIGHT), 0);
        ofVec3f dir = VectorUtil::randomUnitVec3();
        //dir.y = -ofRandom(-0.1, 0.1);
        //dir.x = ofRandom(1.0) < 0.5 ? -1 : 1;
        
        //ofVec2f p = ofVec3f(BUFF_WIDTH / LN * (k + 0.5), k % 2 == 0 ? 0 : BUFF_HEIGHT);
        //ofVec3f dir = ofVec3f(0, k % 2 == 0 ? 1 : -1, 0);
        
        /*
        if (kk == 0) {
            p.y = k % 2 == 0 ? BUFF_HEIGHT * 1.33 : -BUFF_HEIGHT * 0.33;
            dir.y = k % 2 == 0 ? -1 : 1;
        }
        */
    vector<vector<ofVec3f> > points = I_Leaf::simpleLeafPoints(p, dir, BUFF_HEIGHT, BUFF_WIDTH * 0.5);
        vector<ofPolyline> polylines = I_Leaf::pointsToLeaf(points[0], points[1], points[2]);
        
        ofFloatColor scolor = toolUtil.getRandomColor();
        
        ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.5);
        
        for (int i = 2; i < polylines.size(); i ++) {
            ofPolyline line = polylines[i];
            
            if (ofRandom(1.0) < 0.1) {
                scolor = toolUtil.getRandomColor();
            }
            float width = ofRandom(2, 12);
            auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(scolor));
            auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, ofRandom(10), style, line, width, taper));
            conductor.addTool(tool);
        }
        //conductor.addTool(groupTool);
    }
}

void SketchScenario02::leafTest4() {
    int LN = 8;
    for (int kk = 0; kk < 2; kk ++) {
        for (int k = 0; k < LN; k ++) {
            GroupTool* gt = new GroupTool(canvas, ofRandom(10));
            auto groupTool = shared_ptr<Tool>(gt);
            vector<ofVec3f> center;
            vector<ofVec3f> left, right;
            
            ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT));
            //ofVec3f p = ofVec3f(BUFF_WIDTH / 2, ofRandom(BUFF_HEIGHT), 0);
            ofVec3f dir = VectorUtil::randomUnitVec3();
            //dir.y = -ofRandom(-0.1, 0.1);
            //dir.x = ofRandom(1.0) < 0.5 ? -1 : 1;
            
            //ofVec2f p = ofVec3f(BUFF_WIDTH / LN * (k + 0.5), k % 2 == 0 ? 0 : BUFF_HEIGHT);
            //ofVec3f dir = ofVec3f(0, k % 2 == 0 ? 1 : -1, 0);
            
            /*
            if (kk == 0) {
                p.y = k % 2 == 0 ? BUFF_HEIGHT * 1.33 : -BUFF_HEIGHT * 0.33;
                dir.y = k % 2 == 0 ? -1 : 1;
            }
            */
            float rnd = ofRandom(1.0);
            float hm = ofRandom(0.2, 0.5);
            float wm = hm * ofRandom(0.2, 0.5);
            vector<vector<ofVec3f> > points = I_Leaf::simpleLeafPoints(p, dir, BUFF_HEIGHT * hm, BUFF_WIDTH * wm);
            if (rnd < 0.5) {
                vector<ofPolyline> polylines = I_Leaf::pointsToLeaf02(points[0], points[1], points[2]);
                
                for (int i = 0; i < polylines.size(); i ++) {
                    ofPolyline line = polylines[i];
                    auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                    gt->addTool(tool);
                    
                }
            } else {
                vector<ofPolyline> polylines = I_Leaf::pointsToLeaf(points[0], points[1], points[2]);
                
                ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.5);
                ofFloatColor scolor = toolUtil.getRandomColor();
                
                for (int i = 0; i < polylines.size(); i ++) {
                    ofPolyline line = polylines[i];
                    if (i < 2) {
                        auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                        gt->addTool(tool);
                    } else {
                        
                        float width = ofRandom(1, 6);
                        auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(scolor));
                        auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, int(polylines.size()) - i, style, line, width, taper));
                        gt->addTool(tool);
                    }
                }
            }
            conductor.addTool(groupTool);
        }
    }
}

void SketchScenario02::leafTest3() {
    for (int k = 0; k < 8; k ++) {
        GroupTool* gt = new GroupTool(canvas, ofRandom(10));
        auto groupTool = shared_ptr<Tool>(gt);
        vector<ofVec3f> center;
        vector<ofVec3f> left, right;
        
        ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT));
        ofVec3f dir = ofVec3f(0, 1, 0);//VectorUtil::randomUnitVec3();
        
        vector<vector<ofVec3f> > points = I_Leaf::simpleLeafPoints(p, dir, BUFF_HEIGHT, BUFF_WIDTH * 0.25);
        vector<ofPolyline> polylines = I_Leaf::pointsToLeaf02(points[0], points[1], points[2]);
        
        for (int i = 0; i < polylines.size(); i ++) {
            ofPolyline line = polylines[i];
            auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
            conductor.addTool(tool);
            
        }
        //conductor.addTool(groupTool);
    }
}


void SketchScenario02::leafTest2() {
    int LN = 8;
    for (int kk = 0; kk < 2; kk ++) {
        for (int k = 0; k < LN; k ++) {
            GroupTool* gt = new GroupTool(canvas, ofRandom(10));
            auto groupTool = shared_ptr<Tool>(gt);
            vector<ofVec3f> center;
            vector<ofVec3f> left, right;
            
            ofVec2f p = ofVec3f(BUFF_WIDTH / LN * (k + 0.5), k % 2 == 0 ? 0 : BUFF_HEIGHT);
            ofVec3f dir = ofVec3f(0, k % 2 == 0 ? 1 : -1, 0);
            
            if (kk == 0) {
                p.y = k % 2 == 0 ? BUFF_HEIGHT * 1.33 : -BUFF_HEIGHT * 0.33;
                dir.y = k % 2 == 0 ? -1 : 1;
            }
            
            ofVec3f sDir = ofVec3f(1, 0, 0);
            float seed = ofRandom(1000.0);
            float pw = ofRandom(0.5, 3.0);
            float size = BUFF_HEIGHT * 0.66;
            int iN = 50;
            float ns = ofRandom(0.01, 1.0);
            float nAmt = ofRandom(0.01, 0.2);
            
            for (int i = 0; i < iN; i ++) {
                center.push_back(p);
                float sLen = pow(sin(float(i) / (iN - 1) * PI), pw);
                sLen *= 1.0 + ofSignedNoise(seed + i * ns) * nAmt;
                ofVec3f lp = p + sDir * sLen * BUFF_WIDTH / LN * 0.75;
                ofVec3f rp = p - sDir * sLen * BUFF_WIDTH / LN * 0.75;
                left.push_back(lp);
                right.push_back(rp);
                ofDrawCircle(p, 2);
                ofDrawCircle(rp, 2);
                ofDrawCircle(lp, 2);
                
                p += dir * size / (iN - 1);
                dir += VectorUtil::noiseVec3(seed + i * 0.3) * 0.1;
                dir.normalize();
                float sLot = ofSignedNoise(seed + i * 0.2 + 9.87654);
                sDir.rotate(sLot * 15.0, dir);
                
            }
            vector<ofPolyline> polylines = Illustrator::pointsToLeaf(center, left, right);
            
            
            ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.5);
            ofFloatColor scolor = toolUtil.getRandomColor();
            
            for (int i = 0; i < polylines.size(); i ++) {
                ofPolyline line = polylines[i];
                if (i < 2) {
                    auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                    gt->addTool(tool);
                } else {
                    
                    float width = ofRandom(1, 6);
                    auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(scolor));
                    auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, int(polylines.size()) - i, style, line, width, taper));
                    gt->addTool(tool);
                }
            }
            conductor.addTool(groupTool);
        }
    }
}


void SketchScenario02::leafTest() {
    for (int k = 0; k < 8; k ++) {
        GroupTool* gt = new GroupTool(canvas, ofRandom(10));
        auto groupTool = shared_ptr<Tool>(gt);
        vector<ofVec3f> center;
        vector<ofVec3f> left, right;
        
        ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT));
        ofVec3f dir = ofVec3f(0, 1, 0);//;
        ofVec3f sDir = VectorUtil::randomUnitVec3().cross(dir);
        float seed = ofRandom(1000.0);
        float pw = ofRandom(0.2, 2.0);
        float size = ofRandom(250, 750) * 2;
        for (int i = 0; i < 10; i ++) {
            center.push_back(p);
            float sLen = pow(sin(float(i) / 9 * PI), pw);
            ofVec3f lp = p + sDir * sLen * size;
            ofVec3f rp = p - sDir * sLen * size;
            left.push_back(lp);
            right.push_back(rp);
            ofDrawCircle(p, 2);
            ofDrawCircle(rp, 2);
            ofDrawCircle(lp, 2);
            
            p += dir * size / 3;
            dir += VectorUtil::noiseVec3(seed + i * 0.3);
            dir.normalize();
            float sLot = ofSignedNoise(seed + i * 0.2 + 9.87654);
            sDir.rotate(sLot * 5.0, dir);
            
        }
        vector<ofPolyline> polylines = Illustrator::pointsToLeaf(center, left, right);
        
        
        ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 0.5);
        ofFloatColor scolor = toolUtil.getRandomColor();
        
        for (int i = 0; i < polylines.size(); i ++) {
            ofPolyline line = polylines[i];
            if (i < 2) {
                auto tool = toolUtil.getRandomPathTool2(canvas, line, int(polylines.size()) - i);
                gt->addTool(tool);
            } else {
                
                float width = ofRandom(1, 6);
                auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(scolor));
                auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, int(polylines.size()) - i, style, line, width, taper));
                gt->addTool(tool);
            }
        }
        conductor.addTool(groupTool);
    }
}

void SketchScenario02::curtainTest() {
    int xDiv = 48, yDiv = 48;
    ofVec2f p0 = ofVec2f(ofRandom(0.2), ofRandom(0.2)) * ofVec2f(BUFF_WIDTH, BUFF_HEIGHT);
    ofVec2f p1 = ofVec2f(ofRandom(0.8, 1.0), ofRandom(0.2)) * ofVec2f(BUFF_WIDTH, BUFF_HEIGHT);
    ofVec2f p2 = ofVec2f(ofRandom(0.2), ofRandom(0.8, 1.0)) * ofVec2f(BUFF_WIDTH, BUFF_HEIGHT);
    ofVec2f p3 = ofVec2f(ofRandom(0.8, 1.0), ofRandom(0.8, 1.0)) * ofVec2f(BUFF_WIDTH, BUFF_HEIGHT);
    
    for (int ix = 0; ix < xDiv; ix ++) {
        for (int ix = 0; ix < xDiv; ix ++) {
            
            
        }
    }
}

void SketchScenario02::orderTest() {
    
    for (int n = 4; n > 1; n --) {
        vector<ofRectangle> rects;
        for (int xi = 0; xi < n; xi ++) {
            for (int yi = 0; yi < n; yi ++) {
                float x = float(BUFF_WIDTH) / (n) * xi;
                float y = float(BUFF_HEIGHT) / (n) * yi;
                float w = float(BUFF_WIDTH) / n * 1;
                float h = float(BUFF_HEIGHT) / n * 1;
                rects.push_back(ofRectangle(x, y, w, h));
            }
        }
        
        for (int i = 0; i < rects.size(); i ++) {
            if (ofRandom(1.0) < 0.5) {
                vector<ofPolyline> lines = Illustrator::randomFillPaths(rects[i]);
                for (auto line: lines) {
                    auto tool = toolUtil.getRandomPathTool(canvas, line, i + (10 - n) * 100);
                    conductor.addTool(tool);
                }
            } else {
                vector<ofPolyline> lines = Illustrator::randomStrokePaths(rects[i]);
                for (auto line: lines) {
                    auto tool = toolUtil.getRandomStrokeTool(canvas, line, i + (10 - n) * 100);
                    conductor.addTool(tool);
                }
            }
        }
    }
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
            vector<ofPolyline> polylines = Illustrator::randomFillPaths(rects[i]);
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
        vector<ofPolyline> polylines = Illustrator::randomFillPaths(rects[i]);
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
