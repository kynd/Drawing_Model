#include "I_Tree.hpp"

bool flag = false;
Branch::Branch(ofVec3f p, ofVec3f v, float len, float t, int nChild, float seed) {
    int res = 20;
    ofVec3f head = p;
    points.push_back(head);
    for (int i = 0; i < t * res + 1; i ++) {
        float l = len / res;
        if (i > t * res) {
            l *= 1 - (i - t * res);
        }
        float vv = ofNoise(seed * 2.0, seed * 0.12342) * 5.0 + 1.0;
        float vl = ofSignedNoise(seed * 0.1234 + i * 0.013 + 14.56, seed * 0.31234 - i * 0.012) * 60.0;
        v.rotate(ofSignedNoise(seed + i * 0.1 * vv, i * 0.0234) * vl, ofVec3f(0, 0, 1));
        ofVec3f cDisp = head - ofVec3f(0.0, 0.5, 0.0);
        float mag = cDisp.length();
        if (mag + l > 0.5) {
            float d = cDisp.dot(v);
            if (d > 0) {
                l *= d;
            }
        }
        if (mag > 0.5) {break;}
        head += v * l;
        points.push_back(head);
        
    }
    
    for (int i = 0; i < t * nChild; i ++) {
        float tt = float(i + 1) / nChild;
        
        float ns =  ofSignedNoise(seed + i * 0.1234, i * 0.23) * 0.2;
        MP mp = I_Tree::getMidPoint(points, res, tt + ns * 0.5);
        
        float rot = ofSignedNoise(seed) * 2.0 * 180 / 4 + ofSignedNoise(seed + i * 0.234, i * 0.323419) * 15;
        
        ofVec3f v = mp.v.rotate(children.size() % 2 == 0 ? -rot : rot, ofVec3f(0, 0, 1));
        
        v *= (1.0 + ofSignedNoise(seed + i * 12 + 0.2344));
        children.push_back(
            Branch(mp.p, v, 1, t - tt, nChild - 4, ofNoise(seed + i * 123.23456 + 1.234))
                           );
    }
    flag = true;
}

MP I_Tree::getMidPoint(vector<ofVec3f> arr, int arrMaxLen, float t) {
    t = ofClamp(t, 0, 1);
    
    int l = int(arrMaxLen - 1);
    float i, f;
    f = modf(t * l, &i);
    i = floor(t * (arrMaxLen - 1));
    f = t * (arrMaxLen - 1) - i;
    
    ofVec3f p0 = arr[min(i, float(arr.size() - 1))];
    ofVec3f p1 = arr[min(i + 1, float(arr.size() - 1))];
    ofVec3f p = p0.getInterpolated(p1, f);
    
    ofVec3f v = (p1 - p0).normalize();
    if (v.x == 0 && v.y == 0 && i > 0) {
        v = (p0 - arr[i - 1]).normalize();
    }
    MP mp;
    mp.p = p;
    mp.v = v;
    return mp;
}

Branch I_Tree::createTree(float t, float seed) {
    Branch b = Branch(ofVec3f(0), ofVec3f(0, 1, 0), 1, t, 8, seed);
    return b;
}

vector<ofPolyline> I_Tree::branchToPolylines(Branch b, ofVec3f o, float scale) {
    vector<ofPolyline> polylines;
    ofPolyline polyline;
    for (int i = 0; i < b.points.size(); i ++) {
        ofVec3f p = b.points[i] * scale * ofVec3f(1, -1, 1) + o;
        polyline.curveTo(p);
        if (i == 0 || i == b.points.size() - 1) {
            polyline.curveTo(p);
        }
    }
    polylines.push_back(polyline);
    for (int i = 0; i < b.children.size(); i ++) {
        vector<ofPolyline> childLines = branchToPolylines(b.children[i], o, scale);
        polylines.insert(polylines.end(), childLines.begin(), childLines.end());
    }
    return polylines;
}

vector<vector<ofVec3f> > I_Tree::branchToPointVectors(Branch b) {
    vector<vector<ofVec3f> > v;
    vector<ofVec3f> points;
    for (int i = 0; i < b.points.size(); i ++) {
        ofVec3f p = b.points[i];
        points.push_back(p);
    }
    v.push_back(points);
    for (int i = 0; i < b.children.size(); i ++) {
        vector<vector<ofVec3f> > cV = branchToPointVectors(b.children[i]);
        v.insert(v.end(), cV.begin(), cV.end());
    }
    return v;
}



