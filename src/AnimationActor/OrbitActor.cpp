#include "OrbitActor.hpp"

OrbitObj::OrbitObj(ofVec3f _pos, ofVec3f _vel, float _mass) {
    pos = _pos;
    vel = _vel;
    mass = _mass;
}

void OrbitObj::update() {
    trail.push_back(pos);
    if (trail.size() > 50) {
        trail.pop_front();
    }
    pos += vel;
}


OrbitActor::OrbitActor() {
    for (int i = 0; i < 20; i ++) {
        ofVec3f pos = VectorUtil::randomVec3() * 640;
        ofVec3f vel = VectorUtil::randomVec3() * 1;
        float mass = (i == 0) ? 150 : ofRandom(0, 10);
        objs.push_back(OrbitObj(pos, vel, mass));
    }
}

void OrbitActor::update() {
    lines.clear();
    
    for (int i = 0; i < objs.size() - 1; i ++) {
        for (int j = i + 1; j < objs.size(); j ++) {
            ofVec3f p0 = objs[i].pos;
            ofVec3f p1 = objs[j].pos;
            float dist = max(10.f, p0.distance(p1) * 0.1f) ;
            ofVec3f f = (p0 - p1) / dist / dist * objs[i].mass * objs[j].mass * 0.01;
            objs[i].vel -= f / objs[i].mass;
            objs[j].vel += f / objs[j].mass;
            float maxVel = 15;
            //objs[i].vel *= 0.999;
            //objs[j].vel *= 0.999;
            objs[i].vel = objs[i].vel.length() > maxVel ? objs[i].vel.normalize() * maxVel : objs[i].vel;
            objs[j].vel = objs[j].vel.length() > maxVel ? objs[j].vel.normalize() * maxVel : objs[j].vel;
        }
        if (i == 0) {
            float ang = float(frameCount) / 60 * PI;
            objs[i].vel.x += cos(ang) - objs[i].pos.x / BUFF_WIDTH;
            objs[i].vel.y += sin(ang) - objs[i].pos.y / BUFF_HEIGHT;
        }
    }
    
    for (int i = 0; i < objs.size(); i ++) {
        objs[i].update();
        ofPolyline line;
        for (int j = objs[i].trail.size() - 1; j > 0 ; j --) {
            ofVec3f p = objs[i].trail[j];
            line.curveTo(p);
            if (j == 0 || j == objs[i].trail.size() - 1) {
                line.curveTo(p);
            }
            
            for (int j = 0; j < objs[i].trail.size(); j ++) {
                
            }
        }
        vector<ofPolyline> dots = PolyLineUtil::toDottedLine(line, 24, 12);
        lines.push_back(dots);
        
    }
    frameCount ++;
}

void OrbitActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
}

void OrbitActor::drawMain() {
    ofNoFill();
    ofTranslate(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    
    for (int i = 0;i < lines.size(); i ++) {
        for (int j = 0; j < lines[i].size(); j ++){
            lines[i][j].draw();
        }
    }
    
}

