#include "Squishy.hpp"


int Squishy::res = 180;

Squishy::Squishy(vector<float> o) {
    offsetBase = o;
    offset = o;
    offsetBuff = o;
    float xMax, xMin, yMax, yMin;
    for (int i = 0; i < offset.size(); i ++) {
        float ang = float(i) / res * TWO_PI;
        ofVec2f p = ofVec2f(cos(ang), sin(ang)) * offset[i];
        xMax = max(xMax, p.x);
        xMin = min(xMin, p.x);
        yMax = max(yMax, p.y);
        yMin = min(yMin, p.y);
        squishMark.push_back(false);
    }
    
    paintDir = VectorUtil::randomUnitVec2() * ofRandom(1.0, 2.0);
    colorA = toolUtil.getRandomColor();
    colorB = toolUtil.getRandomColor();
    fill = toolUtil.getRandomShaderFill();
    bounds = ofRectangle(xMin, yMin, xMax - xMin, yMax - yMin);
}


ofRectangle Squishy::getBounds() {
    ofRectangle b = bounds;
    b.x += pos.x;
    b.y += pos.y;
    return b;
}

Squishy Squishy::rounded(float s) {
    vector<float> o;
    for (int i = 0; i < res; i ++) {
        float ang = float(i) / res * TWO_PI;
        float x = cos(ang);
        float y = sin(ang);
        x = (x < 0 ? -1 : 1) * pow(abs(x), 0.9);
        y = (y < 0 ? -1 : 1) * pow(abs(y), 0.9);
        float l = ofVec2f(x, y).length() * s;
        //l *= sin(ang * 8.0) * 0.1 + 1.0;
        o.push_back(l);
    }
    return Squishy(o);
}

Squishy Squishy::rect(float w, float h) {
    vector<float> o;
    for (int i = 0; i < res; i ++) {
        float ang = float(i) / res * TWO_PI;
        ofVec2f v = ofVec2f(cos(ang), sin(ang));
        float l0 = (v * w / abs(v.x)).length();
        float l1 = (v * h / abs(v.y)).length();
        float l = min(l0, l1);
        o.push_back(l);
    }
    return Squishy(o);
}


void Squishy::react(Squishy& s) {
    if ( !s.getBounds().intersects(getBounds()) ) { return; }
    float rep = 16;
    for (int i = 0; i < rep; i ++) {
        float t = float(i + 1) / rep;
        calcBounds(s, t);
        s.calcBounds(*this, t);
        updateOffset();
        s.updateOffset();
    }
}


void Squishy::calcBounds(Squishy& s, float amt) {
    for (int i = 0; i < res; i ++) {
        offsetBuff[i] = offset[i];
        ofVec2f tp = getSidePoint(i);
        float bLen = s.getBoundOffset(tp);
        float td = tp.distance(s.pos);
        float dt = max(0.f, (tp - pos).getNormalized().dot((s.pos - tp).getNormalized()));
        float diff = bLen  - td + 48;
        squishMark[i] = false;
        if (diff > 0.0) {
            offsetBuff[i] -= diff * amt * (s.weight + weight) / weight * 2;
            offsetBuff[i] = max(offsetBuff[i], offsetBase[i] / 24.f);
            squishMark[i] = true;
        }
    }
}

void Squishy::updateOffset() {
    offset = offsetBuff;
}

ofVec2f Squishy::getSidePoint(int i) {
    float ang = float(i) / res * TWO_PI;
    return pos + ofVec2f(cos(ang), sin(ang)) * offset[i];
}

float Squishy::getBoundOffset(ofVec2f p) {
    ofVec2f diff = pos - p;
    float angle = fmod(atan2(diff.y, diff.x) + PI, TWO_PI);
    return offset[floor(angle / TWO_PI * offset.size())];
}


void Squishy::update() {
    for (int i = 0; i < res; i ++) {
        if (!squishMark[i]) {
            offset[i] += (offsetBase[i] - offset[i]) / 12;
        }
    }
    
    for (int i = 0; i < res; i ++) {
        int idx = (i + 1) % res;
        offsetBuff[i] = offsetBase[idx];
    }
    //offsetBase = offsetBuff;
    
    for (int j = 0; j < 8; j ++) {
        for (int i = 0; i < res; i ++) {
            int n = (i + 1) % res;
            int p = (i + res - 1) % res;
            int n2 = (i + 2) % res;
            int p2 = (i + res - 2) % res;
            float dn = offsetBase[n] - offset[n];
            float dp = offsetBase[p] - offset[p];
            float dn2 = offsetBase[n2] - offset[n2];
            float dp2 = offsetBase[p2] - offset[p2];
            float di = offsetBase[i] - offset[i];
            float adj = (dn + dp + dn2 + dp2) / 4 - di;
            offsetBuff[i] = offset[i] - adj * 0.25;
        }
        offset = offsetBuff;
    }
        
    points.clear();
    line.clear();
    for (int i = 0; i < res + 4; i ++) {
        int idx = i % res;
        float ang = float(idx) / res * TWO_PI;
        ofVec2f p = ofVec2f(cos(ang), sin(ang)) * offset[idx] + pos;
        points.push_back(p);
        line.curveTo(ofVec3f(p.x, p.y, 0));
    }
}

void Squishy::draw() {
    ofBeginShape();
    line.draw();
    for (int i = 0; i < res; i ++) {
        int idx = i % res;
        ofDrawLine(pos, points[i]);
    }
}
