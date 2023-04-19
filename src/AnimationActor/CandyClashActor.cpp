#include "CandyClashActor.hpp"


Ball::Ball(ofVec2f p, ofVec2f v, float r) {
    radius = r;
    pos = p;
    vel = v;
    paintDir = VectorUtil::randomUnitVec2() * ofRandom(2.0, 4.0);
    res = ceil(r / 3 + 2);
    grav = ofRandom(1.0) < 0.5 ? ofVec2f(0.0, -1.0) : ofVec2f(0.0, 1.0);
    colorA = toolUtil.getRandomColor();
    colorB = toolUtil.getRandomColor();
    for (int i = 0; i < res; i ++) {
        boundOffset.push_back(radius);
        boundOffsetBuff.push_back(radius);
    }
}

void Ball::update() {
    checkBorders();
    if (vel.length() > maxVec) {
        vel = vel.normalize() * maxVec;
    }
    pos += vel;
    vel += grav * 0.02;
    updateShape();
}

void Ball::updateShape() {
    line.clear();
    for (int i = 0; i < res + 3; i ++) {
        int idx = i % res;
        ofVec2f sp = getSidePoint(idx);
        ofVec3f sp3(sp.x, sp.y, 0.0);
        line.curveTo(sp3);
    }
    for (int j = 0; j < 3; j ++) {
        for (int i = 0; i < res; i ++) {
            if (boundOffset[i] < radius / 4) {
                boundOffset[i] = radius / 4;
            }
            int next = (i + 1) % res;
            int prev = (i > 0) ? i - 1 : res - 1;
            float offset = boundOffset[i];
            offset += (radius - offset) / 120;
            offset += (((boundOffset[next] + boundOffset[prev]) / 2 - offset) / 3) * 0.3;
            boundOffsetBuff[i] = boundOffset[i] = offset;
        }
    }
    
}

void Ball::updateBounds() {
    for (int i = 0; i < res; i ++) {
        boundOffset[i] = boundOffsetBuff[i];
    }
}

void Ball::checkBorders() {
    if (pos.x < -radius) {
        pos.x = BUFF_WIDTH + radius;
    }
    if (pos.x > BUFF_WIDTH + radius) {
        pos.x = -radius;
    }
    if (pos.y < -radius) {
        pos.y = BUFF_HEIGHT + radius;
    }
    if (pos.y > BUFF_HEIGHT + radius) {
        pos.y = -radius;
    }
}
void Ball::react(Ball* b) {
    float dist = pos.distance(b->pos);
    if (dist < radius + b->radius && dist != 0) {
        float overlap = radius + b->radius - dist;
        ofVec2f direc = (pos - b->pos).normalize() * overlap * 0.001;
        vel += direc;
        b->vel -= direc;

        calcBounds(b);
        b->calcBounds(this);
        updateBounds();
        b->updateBounds();
    }
}

float Ball::getBoundOffset(ofVec2f p) {
    ofVec2f diff = pos - p;
    float angle = fmod(atan2(diff.y, diff.x) + PI, TWO_PI);
    return boundOffset[floor(angle / TWO_PI * boundOffset.size())];
}
                             
void Ball::calcBounds(Ball* b) {
    for (int i = 0; i < res; i ++) {
        ofVec2f tp = getSidePoint(i);
        float bLen = b->getBoundOffset(tp);
        float td = tp.distance(b->pos);
        if (td < bLen) {
            boundOffsetBuff[i] -= (bLen  - td) / 2;
        }
    }
}
                             
ofVec2f Ball::getSidePoint(int i) {
    float ang = float(i) / res * TWO_PI;
    return pos + ofVec2f(cos(ang), sin(ang)) * boundOffset[i];
}


CandyClashActor::CandyClashActor() {
    int nBalls = 32;
    for (int i = 0; i < nBalls; i++) {
        ofVec2f pos(ofRandom(BUFF_WIDTH), ofRandom(BUFF_WIDTH));
        float a = ofRandom(TWO_PI);
        ofVec2f vel = ofVec2f(cos(a), sin(a)) * ofRandom(10);
        float radius = ofRandom(680) + 120;
        balls.push_back(Ball(pos, vel, radius));
    }
}

void CandyClashActor::update() {
    for (int i = 0; i < balls.size() - 1; i++) {
        for (int j = i + 1; j < balls.size(); j++) {
            balls[i].react(&balls[j]);
        }
    }
    for (int i = 0; i < balls.size(); i++) {
        balls[i].update();
    }
    frameCount ++;
}

void CandyClashActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    for (int i = 0; i < balls.size(); i++) {
        auto fill = shared_ptr<ShaderFill>(new SlideBleedShaderFill(balls[i].colorA, balls[i].colorB, balls[i].paintDir));
        //auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(balls[i].colorA, balls[i].colorB, balls[i].paintDir));
        auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, i, fill, balls[i].line));
        conductor.addTool(tool);
    }
}


void CandyClashActor::drawMain() {
    ofNoFill();
    for (int i = 0; i < balls.size(); i++) {
        balls[i].line.draw();
    }
}



