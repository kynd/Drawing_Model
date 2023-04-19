#include "I_Leaf.hpp"

vector<vector<ofVec3f> > I_Leaf::createVainPoints() {
    class Vain {
    public:
        Vain(ofVec3f _p, ofVec3f _v, int _g): p(_p), v(_v), gen(_g) {}
        void update() {
            if (isDone) { return; }
            pts.push_back(p);
            p += v;
            if (p.distance(ofVec3f(0.0, 0.5, 0.0)) > 0.5) {
                isDone = true;
            }
        }
        ofVec3f p, v;
        int gen;
        vector<ofVec3f> pts;
        bool isDone = false;
    };
    
    vector<Vain> vains;
    const int N = ofRandom(50, 150);
    
    vains.push_back(Vain(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0) / N, 0));
    for (int i = 0; i < N; i ++) {
        bool isAllDone = true;
        
        for (auto& vain : vains) {
            vain.update();
            vain.v.rotate(ofRandom(-10, 10), ofVec3f(0, 0, 1));
            if (!vain.isDone) {isAllDone = false;}
        }
        int n = int(vains.size());
        for (int j = 0; j < n; j ++) {
            if (ofRandom(1.0) < 0.25 / (1 + vains[j].gen * 0.5 + i * 0.1)) {
                ofVec3f v = vains[j].v.getNormalized();
                float rot = 60.0 * (ofRandom(1.0) < 0.5 ? -1 : 1) / (vains[j].gen + 1);
                v.rotate(rot, ofVec3f(0, 0, 1));
                
                vains.push_back(Vain(vains[j].p, v / N, vains[j].gen + 1));
            }
        }
    }
    //cout << vains.size();
    vector<vector<ofVec3f> > points;
    for (auto vain: vains) {
        points.push_back(vain.pts);
        if (ofGetFrameNum() == 1) {
           // for (auto p : vain.pts) { cout << p << &endl;}
        }
    }
    return points;
}

vector<vector<ofVec3f> > I_Leaf::createStripePoints() {
    vector<vector<ofVec3f> > points;
    float seed = ofRandom(100.0);
    const int N = ofRandom(20, 100);
    for (int i = 0; i < N; i ++) {
        vector<ofVec3f> pts;
        float y0 = 1.0 / N * i;
        float y1 = 1.0 / N * (i + 1);
        float xMult = (i % 2 == 0) ? -0.5 : 0.5;
        int xRes = 15, yRes = 15;
        
        float c0 = (y0 - 0.5) * 2.0;
        float x0 = sqrt(1.0 - c0 * c0) * xMult;
        for (int j = 0; j < xRes; j ++) {
            float t = float(j) / (xRes - 1);
            float x = ofLerp(0.0, x0, t);
            float y = y0 + ofSignedNoise(j * 0.1 + seed) * 0.1 / N;
            pts.push_back(ofVec3f(x, y, 0));
        }
        
        for (int j = 0; j < yRes; j ++) {
            float t = float(j) / (yRes - 1);
            float y = ofLerp(y0, y1, t);
            float co = (y - 0.5) * 2.0;
            float x = sqrt(1.0 - co * co) * xMult;
            pts.push_back(ofVec3f(x, y, 0));
        }
        
        float c1 = (y1 - 0.5) * 2.0;
        float x1 = sqrt(1.0 - c1 * c1) * xMult;
        for (int j = 0; j < xRes; j ++) {
            float t = float(j) / (xRes - 1);
            float x = ofLerp(x1, 0.0, t);
            float y = y1 + ofSignedNoise(j * 0.1 + seed + 0.123) * 0.1 / N;
            pts.push_back(ofVec3f(x, y, 0));
        }
        
        for (int j = 0; j < yRes; j ++) {
            float t = float(j) / (yRes - 1);
            float y = ofLerp(y1, y0, t);
            pts.push_back(ofVec3f(0, y, 0));
        }
        points.push_back(pts);
    }
    return points;
}

void I_Leaf::drawPoints(vector<vector<ofVec3f> > v, ofVec3f origin, float scale) {
    ofPushMatrix();
    ofTranslate(origin);
    for (auto points : v) {
        for (int i = 0; i < points.size(); i ++) {
            //ofDrawCircle(points[i] * scale, 2);
            if (i != 0) {
                ofDrawLine(points[i] * scale, points[i - 1] * scale);
            }
        }
    }
    ofPopMatrix();
}

vector<ofPolyline> I_Leaf::pointsToLeaf(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right) {
    
    vector<ofPolyline> polylines;
    
    vector<ofPolyline> base = pointsToLeafBase(center, left, right);
    polylines.insert(polylines.end(), base.begin(), base.end());
    
    vector<ofPolyline> vains = mapPointsToLeaf(center, left, right, createVainPoints());
    polylines.insert(polylines.end(), vains.begin(), vains.end());
    return polylines;
}

vector<ofPolyline> I_Leaf::pointsToLeaf02(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right) {
    
    vector<ofPolyline> polylines;
    
    vector<ofPolyline> base = pointsToLeafBase(center, left, right);
    polylines.insert(polylines.end(), base.begin(), base.end());
    
    vector<ofPolyline> vains = mapPointsToLeaf(center, left, right, createStripePoints());
    polylines.insert(polylines.end(), vains.begin(), vains.end());
    return polylines;
}


vector<ofPolyline> I_Leaf::pointsToLeafBase(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right) {
    vector<ofPolyline> polylines;
    ofPolyline leftBody, rightBody;
    for (int i = 0; i < center.size(); i ++) {
        ofVec3f p = center[i];
        p.z = 0;
        leftBody.curveTo(p);
        rightBody.curveTo(p);
        if (i == 0 || i == center.size() - 1) {
            leftBody.curveTo(p);
            rightBody.curveTo(p);
        }
    }
    
    for (int i = int(left.size()) - 1; i >= 0; i --) {
        ofVec3f p = left[i];
        p.z = 0;
        leftBody.curveTo(p);
        if (i == 0 || i == left.size() - 1) {
            leftBody.curveTo(p);
        }
    }
    
    for (int i = int(right.size()) - 1; i >= 0; i --) {
        ofVec3f p = right[i];
        p.z = 0;
        rightBody.curveTo(p);
        if (i == 0 || i == right.size() - 1) {
            rightBody.curveTo(p);
        }
    }
    polylines.push_back(leftBody);
    polylines.push_back(rightBody);
    return polylines;
}



vector<ofPolyline> I_Leaf::mapPointsToLeaf(vector<ofVec3f> center, vector<ofVec3f> left, vector<ofVec3f> right, vector<vector<ofVec3f> > pointVec) {
    vector<ofPolyline> polylines;
    
    for (auto points: pointVec) {
        ofPolyline line;
        ofVec3f p;
        for (int i = 0; i < points.size(); i ++) {
            ofVec3f vp = points[i];
            ofVec3f cp = ip(center, vp.y);
            if (vp.x < 0) {
                ofVec3f ep = ip(left, vp.y);
                p = cp.getInterpolated(ep, vp.x * -2);
            } else {
                ofVec3f ep = ip(right, vp.y);
                p = cp.getInterpolated(ep, vp.x * 2);
            }
            p.z = 0;
            line.curveTo(p);
            if (i == 0 || i == points.size() - 1) {
                line.curveTo(p);
            }
        }
        polylines.push_back(line);
    }
    return polylines;
}


ofVec3f I_Leaf::ip(vector<ofVec3f> v, float t) {
    t = ofClamp(t, 0, 1);
    int l = int(v.size() - 1);
    float i, f;
    f = modf(t * l, &i);
    return v[i].getInterpolated(v[min(i + 1, float(l))], f);
}


vector<vector<ofVec3f> > I_Leaf::simpleLeafPoints(ofVec3f p, ofVec3f dir, float h, float w) {
    vector<ofVec3f> center, left, right;
    
    ofVec3f sDir = dir.getCrossed(ofVec3f(0, 0, 1));
    float seed = ofRandom(1000.0);
    float pw = ofRandom(0.1, 3.0);
    int iN = 50;
    float ns = ofRandom(0.01, 1.0);
    float nAmt = ofRandom(0.01, 0.2);

    for (int i = 0; i < iN; i ++) {
        center.push_back(p);
        float sLen = pow(sin(float(i) / (iN - 1) * PI), pw);
        sLen *= 1.0 + ofSignedNoise(seed + i * ns) * nAmt;
        ofVec3f lp = p + sDir * sLen * w * 0.5;
        ofVec3f rp = p - sDir * sLen * w * 0.5;
        left.push_back(lp);
        right.push_back(rp);
        
        p += dir * h / (iN - 1);
        dir += VectorUtil::noiseVec3(seed + i * 0.3) * 0.1;
        dir.normalize();
        float sLot = ofSignedNoise(seed + i * 0.2 + 9.87654);
        sDir.rotate(sLot * 15.0, dir);
    }
    vector<vector<ofVec3f> > points;
    points.push_back(center);
    points.push_back(left);
    points.push_back(right);
    return points;
}


vector<vector<ofVec3f> > I_Leaf::trunkPoints(ofVec3f p, ofVec3f dir, float h, float w) {
    vector<ofVec3f> center, left, right;
    
    ofVec3f sDir = dir.getCrossed(ofVec3f(0, 0, 1));
    float seed = ofRandom(1000.0);
    float pw = ofRandom(0.1, 3.0);
    int iN = 50;
    float ns = ofRandom(0.01, 1.0);
    float nAmt = ofRandom(0.01, 0.2);

    for (int i = 0; i < iN; i ++) {
        center.push_back(p);
        float sLen = 1.0;//pow(sin(float(i) / (iN - 1) * PI), pw);
        sLen *= 1.0 + ofSignedNoise(seed + i * ns) * nAmt;
        ofVec3f lp = p + sDir * sLen * w * 0.5;
        ofVec3f rp = p - sDir * sLen * w * 0.5;
        left.push_back(lp);
        right.push_back(rp);
        
        p += dir * h / (iN - 1);
        dir += VectorUtil::noiseVec3(seed + i * 0.3) * 0.1;
        dir.normalize();
        float sLot = ofSignedNoise(seed + i * 0.2 + 9.87654);
        sDir.rotate(sLot * 15.0, dir);
    }
    vector<vector<ofVec3f> > points;
    points.push_back(center);
    points.push_back(left);
    points.push_back(right);
    return points;
}


