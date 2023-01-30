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
        for (int j = int(linePointList[i0].size()) - 1; j >= 0; j --) {
            polyline.curveTo(linePointList[i1][j]);
        }
        polyline.close();
        polylines.push_back(polyline);
    }
    return polylines;
}


vector<ofPolyline> Illustrator::createTreePath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    float cx = rect.x + rect.width / 2;
    float top = rect.y;
    float bottom = rect.y + rect.height;
    
    ofPolyline centerLine;
    for (int i = 0; i < 10; i ++) {
        ofVec3f p = ofVec3f(cx, top, 0).getInterpolated(ofVec3f(cx, bottom, 0.0), float(i) / 9);
        centerLine.addVertex(p);
    }
    centerLine = PolyLineUtil::noiseWarp(centerLine, 2, 8, 0.25, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(96.0));
    ofPolyline trunk = PolyLineUtil::toRoundedStroke(centerLine, 16);
    polylines.push_back(trunk);
    
    float w = 32;
    int n = rect.height / w;
    for (int i = 0; i < n; i ++) {
        float t = float(i) / (n - 1);
        float t1 = 0.25 + t * ofRandom(0.7, 0.8);
        float xLen = rect.width * t * 0.5 * ofRandom(0.5, 1.0);
        ofVec3f cp = centerLine.getPointAtPercent(t);
        ofVec3f lp(cp.x + xLen, ofLerp(top, bottom, t1), 0.0);
        ofVec3f rp(cp.x - xLen, ofLerp(top, bottom, t1), 0.0);
        ofPolyline left, right;
        for (int i = 0; i < 10; i ++) {
            ofVec3f p = cp.getInterpolated(lp, float(i) / 9);
            left.addVertex(p);
        }
        left = PolyLineUtil::toRoundedStroke(left, w * 0.25);
        left = PolyLineUtil::noiseWarp(left, 2, 8, 0.25, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(96.0));
        
        for (int i = 0; i < 10; i ++) {
            ofVec3f p = cp.getInterpolated(rp, float(i) / 9);
            right.addVertex(p);
        }
        right = PolyLineUtil::toRoundedStroke(right, w * 0.25);
        right = PolyLineUtil::noiseWarp(right, 2, 8, 0.25, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(96.0));
        polylines.push_back(left);
        polylines.push_back(right);
    }
    
    
    return polylines;
}






vector<ofPolyline> Illustrator::createWaveStarPath(ofRectangle rect) {
    
    vector<ofPolyline> polylines;
    float cx = rect.x + rect.width * 0.5;
    float cy = rect.y + rect.height * 0.5;
    float hw = rect.width * 0.5;
    float hh = rect.height * 0.5;

    ofPolyline line;
    int n = 64;
    float freq = round(ofRandom(3, 12));
    float offR = ofRandom(0.25);
    float baseR = 1.0 - offR;

    float angOffset = ofRandom(TWO_PI);
    for (int i = 0; i <= n + 2; i ++) {
        float ang = TWO_PI / n * (i % n) + angOffset;
        float r = sin(ang * freq) * offR + baseR;
        ofVec3f p(cos(ang) * r * hw + cx, sin(ang) * r * hh + cy, 0);
        line.curveTo(p);
    }
    line.close();
    line.simplify();
    
    polylines.push_back(line);
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



vector<ofPolyline> Illustrator::createRandomQuadPath(ofRectangle rect) {
    vector<ofPolyline> polylines;
    ofPolyline polyline;
    
    ofVec3f v0(rect.x + ofRandom(rect.width * 0.5), rect.y + ofRandom(rect.height * 0.5), 0);
    ofVec3f v1(rect.x + rect.width * 0.5 + ofRandom(rect.width * 0.5), rect.y + ofRandom(rect.height * 0.5), 0);
    ofVec3f v2(rect.x + rect.width * 0.5 + ofRandom(rect.width * 0.5), rect.y + rect.height * 0.5 + ofRandom(rect.height * 0.5), 0);
    ofVec3f v3(rect.x + ofRandom(rect.width * 0.5), rect.y + rect.height * 0.5 + ofRandom(rect.height * 0.5), 0);
    polyline.addVertex(v0);
    polyline.addVertex(v1);
    polyline.addVertex(v2);
    polyline.addVertex(v3);
    polyline.close();
    
    polylines.push_back(polyline);
    
    return polylines;
}


vector<ofPolyline> Illustrator::randomFillPaths(ofRectangle rect) {
    int rnd = ofRandom(5);
    if (rnd == 0) {
        return createWavyPath(rect);
    } else if (rnd == 1) {
        return createRandomQuadPath(rect);
    } else if (rnd == 2) {
        return createStarBlobPath(rect);
    } else if (rnd == 3) {
        return createOvalPath(rect);
    } else {
        return createBlobPath(rect);
    }
}

vector<ofPolyline> Illustrator::randomStrokePaths(ofRectangle rect) {
    int rnd = ofRandom(3);
    if (rnd == 0) {
        return createSquigglePath(rect);
    } else if (rnd == 1) {
        return createGridPointPath(rect, ofRandom(1, 5), ofRandom(1, 5), ofRandom(3, 8));
    } else {
        return createFastDenseSquigglePath(rect);
    }
}


vector<ofRectangle> Illustrator::createGrid(int nh, int nv) {
    
    vector<ofRectangle> rects;
    
    for (int nx = 0; nx < nh; nx ++) {
        for (int ny = 0; ny < nv; ny ++) {
            float x = float(BUFF_WIDTH) / nh * nx;
            float y = float(BUFF_HEIGHT) / nv * ny;
            float w = float(BUFF_WIDTH) / nh;
            float h = float(BUFF_HEIGHT) / nv;
            
            ofPolyline bgRect = PolyLineUtil::rectangle(x, y, w, h);
        }
    }
    return rects;
}

vector<ofRectangle> Illustrator::createRandomGrid(int nh, int nv) {
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

vector<ofRectangle> Illustrator::createRandomSquareGrid(int n) {
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




ofRectangle Illustrator::randomRect(float minW, float minH, float maxW, float maxH) {
    float w = ofRandom(minW, maxW);
    float h = ofRandom(minH, maxH);
    float x = ofRandom(0, BUFF_WIDTH - w);
    float y = ofRandom(0, BUFF_HEIGHT - h);
    return ofRectangle(x, y, w, h);
}
