#include "BoxActor.hpp"

BoxDef::BoxDef() {
    ofVec3f size(ofRandom(50, 200), ofRandom(50, 200), ofRandom(50, 200));
    ofVec3f center(ofRandom(-200, 200), ofRandom(-200, 200), ofRandom(-200, 200));
    float rot = round(ofRandom(-8, 8)) / 8 * 180;
    pCenter = tCenter = iCenter = center;
    pSize = tSize = iSize = size;
    pRot = tRot = iRot = rot;
    z = ofRandom(10.0);
    
    float rnd = ofRandom(2.0);
    if (rnd < 1.0) {
        axis = ofVec3f(1.0, 0.0, 0.0);
    } else if (rnd < 2.0) {
        axis = ofVec3f(0.0, 1.0, 0.0);
    } else {
        axis = ofVec3f(0.0, 0.0, 1.0);
    }
    
    updatePoints();
    updateTarget();
    
    edges.push_back(vector<int> {0, 1});
    edges.push_back(vector<int> {1, 2});
    edges.push_back(vector<int> {2, 3});
    edges.push_back(vector<int> {3, 0});
    edges.push_back(vector<int> {4, 5});
    edges.push_back(vector<int> {5, 6});
    edges.push_back(vector<int> {6, 7});
    edges.push_back(vector<int> {7, 4});
    edges.push_back(vector<int> {0, 4});
    edges.push_back(vector<int> {1, 5});
    edges.push_back(vector<int> {2, 6});
    edges.push_back(vector<int> {3, 7});
    
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {0, 1, 2, 3});}
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {4, 5, 6, 7});}
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {0, 1, 5, 4});}
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {1, 2, 6, 5});}
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {2, 3, 7, 6});}
    if (ofRandom(1.0) < 0.5) { faces.push_back(vector<int> {3, 0, 4, 7});}
    
    for (int i = 0; i < faces.size(); i ++) {
        fills.push_back(toolUtil.getRandomShaderFill());
    }
    
    strokeColor = toolUtil.getRandomColor();
    baseSpan = ofRandom(8, 16);
    span = ofRandom(baseSpan *0.5, baseSpan);
    lineWidth = ofRandom(1, span);
    moveLen = int(ofRandom(1, 4)) * 30;
    
}


void BoxDef::updatePoints() {
    points.clear();
    points.push_back(ofVec3f(-1,-1,-1));
    points.push_back(ofVec3f(1,-1,-1));
    points.push_back(ofVec3f(1, 1,-1));
    points.push_back(ofVec3f(-1, 1,-1));
    points.push_back(ofVec3f(-1,-1, 1));
    points.push_back(ofVec3f(1,-1, 1));
    points.push_back(ofVec3f(1, 1, 1));
    points.push_back(ofVec3f(-1, 1, 1));
    
    for (int i = 0; i < points.size(); i ++) {
        points[i] = points[i] * size;
        points[i].rotate(rot, axis);
        points[i] += center;
    }
}

void BoxDef::update() {
    
    if ((frameCount + moveLen) % 360 == 0) {
        updateTarget(true);
    } else if (frameCount % moveLen == 0) {
        updateTarget();
    }
    
    float t = float(frameCount % moveLen) / (moveLen - 1);
    
    t = max(0.f, min(t, 1.f));
    if (t < 0.5) {
      t = pow(t * 2.0, 2.0) * 0.5;
    } else {
      t = 1.0 - pow((1.0 - t) * 2, 2.0) * 0.5;
    }
    
    center = pCenter.getInterpolated(tCenter, t);
    size = pSize.getInterpolated(tSize, t);
    rot = ofLerp(pRot, tRot, t);
    updatePoints();
    
    frameCount ++;
}

void BoxDef::updateTarget(bool reset) {
    center = pCenter = tCenter;
    size = pSize = tSize;
    rot = pRot = tRot;
    
    if (reset) {
        tCenter = iCenter;
        tSize = iSize;
        tRot = iRot;
        cout << "A";
        return;
    }
    
    float r0 = ofRandom(3.0), r1 = ofRandom(3.0);
    if (r0 < 1.0) {
        if (r1 < 1.0) {
            tCenter.y = ofRandom(-300, 300);
        } else if (r1 < 2.0) {
            tCenter.y = ofRandom(-300, 300);
        } else {
            tCenter.z = ofRandom(-300, 300);
        }
    } else if (r0 < 2.0) {
        float v = ofRandom(5, 200);
        if (r1 < 1.0) {
            tSize.x = v;
        } else if (r1 < 2.0) {
            tSize.y = v;
        } else {
            tSize.z = v;
        }
    } else {
        tRot = round(ofRandom(-8, 8)) / 8 * 180;
    }
}


BoxActor::BoxActor() {
    for (int i = 0; i < 6; i ++) {
        boxes.push_back(BoxDef());
    }
}

void BoxActor::update() {
    
    float t = 0.6;//float(frameCount) / 360 * PI;
    //ofVec3f cam(cos(t) * 600, 200, sin(t) * 600);
    ofVec3f cam(0, 0, 600);
    ofVec3f center(0, 0, 0);
    
    
    for (int bi = 0; bi < boxes.size(); bi ++) {
        boxes[bi].update();
        boxes[bi].edgeLines.clear();
        boxes[bi].faceLines.clear();
        vector<ofVec3f> points;
        for (int i = 0; i < boxes[bi].points.size(); i ++) {
            ofVec3f p = boxes[bi].points[i];
            p = VectorUtil::project(p, cam, center);
            p *= ofVec3f(dispScale.x, dispScale.y, 0.0);
            p += ofVec3f(dispCenter.x, dispCenter.y, 0.0);
            p += ofVec3f(BUFF_WIDTH, BUFF_HEIGHT, 0.0) * 0.5;
            
            points.push_back(p);
        }
        
        for (int i = 0;i < boxes[bi].edges.size(); i ++) {
            ofPolyline line;
            line.addVertex(points[boxes[bi].edges[i][0]]);
            line.addVertex(points[boxes[bi].edges[i][1]]);
            boxes[bi].edgeLines.push_back(line);
        }
        
        for (int i = 0;i < boxes[bi].faces.size(); i ++) {
            ofPolyline line;
            for (int j = 0; j < boxes[bi].faces[i].size(); j ++) {
                line.addVertex(points[boxes[bi].faces[i][j]]);
            }
            line.close();
            boxes[bi].faceLines.push_back(line);
        }
    }
    frameCount ++;
}

void BoxActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    for (int bi = 0; bi < boxes.size(); bi ++) {
        for (int i = 0; i < boxes[bi].edgeLines.size(); i ++) {
            
            vector<ofPolyline> polylines;
            polylines = PolyLineUtil::toDottedLine(boxes[bi].edgeLines[i], boxes[bi].baseSpan, boxes[bi].span);
            
            
            ofFloatColor color = boxes[bi].strokeColor;
            auto style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
            for (int i = 0; i < polylines.size(); i ++) {
                auto tool = shared_ptr<Tool>(new RoundStrokeTool(canvas, 0, style, polylines[i], boxes[bi].lineWidth));
                conductor.addTool(tool);
            }
        }
        for (int i = 0; i < boxes[bi].faceLines.size(); i ++) {
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, boxes[bi].z, boxes[bi].fills[i], boxes[bi].faceLines[i]));
            
            conductor.addTool(tool);
        }
        
    }
    
}


void BoxActor::drawMain() {
    ofNoFill();
    //ofTranslate(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    
    for (int bi = 0; bi < boxes.size(); bi ++) {
        for (int i = 0;i < boxes[bi].edgeLines.size(); i ++) {
            boxes[bi].edgeLines[i].draw();
        }
    }
}

