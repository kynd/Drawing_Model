#include "Illustrator.hpp"




vector<ofPolyline> Illustrator::eclipse(ofRectangle rect, float angle) {
    angle = fmod(angle, TWO_PI);
    vector<ofPolyline> polylines;
    int res = 64;
    float cx = rect.x + rect.width / 2;
    float cy = rect.y + rect.height / 2;
    float hw = rect.width / 2;
    float hh = rect.height / 2;
    
    ofPolyline line;
    line.addVertex(ofVec3f(cx, cy + hh, 0));
    for (int i = 0; i <= res; i ++) {
        float xScale;
        if (angle < PI) {
            xScale = -cos(angle);
        } else {
            xScale = 1;
        }
        float a = PI / res * i;
        line.curveTo(ofVec3f(cx + hw * sin(a) * xScale, cy + hh * cos(a), 0));
    }
     
    line.addVertex(ofVec3f(cx, cy - hh, 0));
    for (int i = res; i >= 0 ; i --) {
        float xScale;
        if (angle < PI) {
            xScale = -1;
        } else {
            xScale = -cos(angle - PI);
        }
        float a = PI / res * i;
        line.curveTo(ofVec3f(cx + hw * sin(a) * xScale, cy + hh * cos(a), 0));
    }
    line.close();
    polylines.push_back(line);
    return polylines;
}


vector<ofPolyline> Illustrator::createOvalPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    polylines.push_back(PolyLineUtil::oval(rect.x, rect.y, rect.width, rect.height));
    return polylines;
}

vector<ofPolyline> Illustrator::createRectanglePath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    polylines.push_back(PolyLineUtil::rectangle(rect.x, rect.y, rect.width, rect.height));
    return polylines;
}

vector<ofPolyline> Illustrator::createSquigglePath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    ofPolyline centerLine;
    
    for (int i = 0; i <= 10; i ++) {
        ofVec3f p(ofRandom(rect.width) + rect.x, ofRandom(rect.height) + rect.y);
        centerLine.curveTo(p);
    }
    //int res = max(rect.width, rect.height) / 5;
    polylines.push_back(centerLine);
    return polylines;
}

vector<ofPolyline> Illustrator::createFastDenseSquigglePath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    ofPolyline centerLine;
    
    int n = ofRandom(30, 50);
    vector<ofVec2f> pts;
    float ang = ofRandom(360);
    ofVec2f scale(rect.width * 0.5, rect.height * 0.5);
    ofVec2f center(rect.x + rect.width * 0.5, rect.y + rect.height * 0.5);
    for (int i = 0; i < n; i ++) {
        float y = float(i) / (n - 1)  * 2.0 - 1.0;
        ofVec2f p0(-ofRandom(0.5, 1.0), y + ofRandom(-1, 1) / n);
        ofVec2f p1(ofRandom(0.5, 1.0), y + ofRandom(-1, 1) / n);
        p0.rotate(ang);
        p1.rotate(ang);
        p0 = center + p0 * scale;
        p1 = center + p1 * scale;
        pts.push_back(p0);
        pts.push_back(p1);
    }
    
    for (int i = 0; i <n; i ++) {
        centerLine.curveTo(ofVec3f(pts[i].x, pts[i].y, 0.0));
    }
    //int res = max(rect.width, rect.height) / 5;
    polylines.push_back(centerLine);
    return polylines;
}



vector<ofPolyline> Illustrator::createGridPointPath(ofRectangle rect, int nx, int ny, int np) {
    vector<ofPolyline> polylines;
    ofPolyline centerLine;
    
    ofVec2f lastPt(int(ofRandom(nx + 1)), int(ofRandom(ny + 1)));
    float xSpan = rect.width / nx;
    float ySpan = rect.height / ny;
    
    for (int i = 0; i < np; i ++) {
        ofVec2f pt;
        int safetyCnt = 0;
        do {
            pt = lastPt + ofVec2f(round(ofRandom(-1, 1)), round(ofRandom(-1, 1)));
            pt.x = max(0.f, min(float(nx), pt.x));
            pt.y = max(0.f, min(float(ny), pt.y));
            safetyCnt ++;
        } while (pt == lastPt && safetyCnt < 10);
        
        lastPt = pt;
        centerLine.curveTo(ofVec3f(xSpan * pt.x + rect.x, ySpan * pt.y + rect.y, 0.0));
    }
    
    polylines.push_back(centerLine);
    return polylines;
}


vector<ofPolyline> Illustrator::createWavyPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    ofPolyline centerLine;
    float cx =  rect.x + rect.width / 2;
    int freq = ofRandom(1,4);
    float w = rect.width / (freq * 4) * 0.5;
    float h = rect.height - w * 2;
    int res = h / 5;
    float span = h / res;
    for (int i = 0; i <= res; i ++) {
        float ang = float(i) / res * TWO_PI * freq;
        
        float s = sin(ang);
        float dx = (s < 0 ? -1 : 1) * pow(abs(s), 0.2);
        float x = cx + dx * (rect.width * 0.25);
        float y = rect.y + w + span * i;
        ofVec3f p(x, y, 0);
        centerLine.curveTo(p);
        if (i == 0 || i == res) {
            centerLine.curveTo(p);
        }
    }
    polylines.push_back(PolyLineUtil::toFlatStroke(centerLine, w, max(12, res)));
    return polylines;
}


vector<ofPolyline> Illustrator::createWatermelonPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    vector<vector<ofVec3f> > linePointList;
    float cx =  rect.x + rect.width / 2;
    float cy = rect.y + rect.height / 2;
    int vn = ofRandom(4, 8);
    int freq = ofRandom(1, 4);
    float hn = freq * 16;
    float w = rect.width;
    float h = rect.height;
    
    // Create Points
    for (int i = -vn; i <= vn; i ++) {
        float xamp = float(vn - abs(i)) / vn;
        vector<ofVec3f> linePoints;
        for (int j = -hn; j <= hn; j ++) {
            float amp = xamp * float(hn - abs(j)) / hn;
            amp = pow(amp, 0.1) + 0.05;
            amp *= w / hn * 0.5;
            float ny = 0.5 / hn * j;
            float y = h * ny;
            
            float x = sqrt(0.5 * 0.5 - ny * ny) * w * i / vn + sin(j / hn * TWO_PI * freq) * amp;
            linePoints.push_back(ofVec3f(x + cx, y + cy, 0));
        }
        linePointList.push_back(linePoints);
    }
    
    // Create Polylines and tools
    for (int i = 0; i < linePointList.size() - 1; i ++) {
        ofPolyline polyline;
        int i0 = i;
        int i1 = i + 1;
        polyline.addVertex(linePointList[i0][0]);
        for (int j = 0; j < linePointList[i0].size(); j ++) {
            polyline.curveTo(linePointList[i0][j]);
        }
        polyline.addVertex(linePointList[i0][linePointList[i0].size() - 1]);
        for (int j = linePointList[i0].size() - 1; j >= 0; j --) {
            polyline.curveTo(linePointList[i1][j]);
        }
        polyline.close();
        polylines.push_back(polyline);
    }
    return polylines;
}

vector<ofPolyline> Illustrator::createStarBlobPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    float angleOffset = ofRandom(TWO_PI);
    float cx = rect.x + rect.width * 0.5;
    float cy = rect.y + rect.height * 0.5;
    int nVertices = ofRandom(3, 36);
    ofPolyline polyline;
    vector<ofVec3f> pts;
    for (int i = 0; i < nVertices; i ++) {
        int idx = i % nVertices;
        float ang = TWO_PI / nVertices * idx + angleOffset;
        float r = ofRandom(0.5, 1.0);
        float dx = cos(ang) * r * rect.width * 0.5;
        float dy = sin(ang) * r * rect.height * 0.5;
        pts.push_back(ofVec3f(dx + cx, dy + cy, 0.0));
    }
    
    for (int i = 0; i <= nVertices + 2; i ++) {
        int idx = i % nVertices;
        polyline.curveTo(pts[idx]);
    }
    polyline.close();
    polylines.push_back(polyline);
    return polylines;
}

vector<ofPolyline> Illustrator::createBlobPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    float angleOffset = ofRandom(TWO_PI);
    float cx = rect.x + rect.width * 0.5;
    float cy = rect.y + rect.height * 0.5;
    int nVertices = ofRandom(3, 36);
    ofPolyline polyline;
    vector<ofVec3f> pts;
    float nx = ofRandom(10000);
    float ny = ofRandom(10000);
    float maxW = 0;
    float maxH = 0;
    for (int i = 0; i <= nVertices; i ++) {
        int idx = i % nVertices;
        float ang = TWO_PI / nVertices * idx + angleOffset;
        float dx = cos(ang) * rect.width * 0.5;
        float dy = sin(ang) * rect.height * 0.5;
        float ns = 0.0005;
        float n = 0.6 + ofSignedNoise(nx + dx * ns, ny + dy * ns) * 0.2;
        ofVec3f p(dx * n, dy * n, 0.0);
        pts.push_back(p);
        maxW = max(maxW, abs(p.x));
        maxH = max(maxH, abs(p.y));
    }
    
    float mult = min(rect.width * 0.5 / maxW, rect.height * 0.5 / maxH);
    
    for (int i = 0; i <= nVertices + 2; i ++) {
        int idx = i % nVertices;
        polyline.curveTo(pts[idx] * mult + ofVec3f(cx, cy, 0));
    }
    polyline.close();
    polylines.push_back(polyline);
    return polylines;
}

