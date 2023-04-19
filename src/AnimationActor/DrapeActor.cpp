#include "DrapeActor.hpp"

DrapeTileDef::DrapeTileDef() {
    baseColor = toolUtil.getRandomColor();
}

void DrapeTileDef::update(ofVec3f _p0, ofVec3f _p1, ofVec3f _p2, ofVec3f _p3, ofFloatColor _color) {
    p0 = _p0;
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    color = _color;
    polyline.clear();
    AddVerts(polyline, p0, p1);
    AddVerts(polyline, p1, p3);
    AddVerts(polyline, p3, p2);
    AddVerts(polyline, p2, p0);
    polyline.close();
}

void DrapeTileDef::AddVerts(ofPolyline & line, ofVec3f pa, ofVec3f pb) {
    int n = 6;
    for (int i = 0; i <= n; i ++) {
        float t = float(i) / n;
        polyline.addVertex(pa.getInterpolated(pb, t));
    }
}


DrapeActor::DrapeActor() {
    float offset = 0.4;
    
    a0 = ofVec3f(-ofRandom(0.5, 0.5 + offset), -ofRandom(0.5, 0.5 + offset), 0.0);
    a1 = ofVec3f(ofRandom(0.5, 0.5 + offset), -ofRandom(0.5, 0.5 + offset), 0.0);
    a2 = ofVec3f(-ofRandom(0.5, 0.5 + offset), ofRandom(0.5, 0.5 + offset), 0.0);
    a3 = ofVec3f(ofRandom(0.5, 0.5 + offset), ofRandom(0.5, 0.5 + offset), 0.0);
    
    
    for (int iy = 0; iy < yDiv - 1; iy ++) {
        for (int ix = 0; ix < xDiv - 1; ix ++) {
            DrapeTileDef tile;
            tile.d = VectorUtil::randomVec2();
            tiles.push_back(tile);
        }
    }
}

void DrapeActor::setPosition(ofVec2f _center, ofVec2f _scale) {
    AnimationActor::setPosition(_center, _scale);
}


void DrapeActor::update() {
    ofVec3f cam = ofVec3f(0, 0, 900);
    ofVec3f center(0, 0, 0);
    
    points.clear();
    ofVec3f freq = ofVec3f(1,2,8);
    float noiseSize = 0.1;
    for (int iy = 0; iy <= yDiv; iy ++) {
        vector<ofVec2f> pts;
        
        ofVec3f ax0 = a0.getInterpolated(a2, float(iy)/ yDiv);
        ofVec3f ax1 = a1.getInterpolated(a3, float(iy)/ yDiv);
        
        for (int ix = 0; ix <= xDiv; ix ++) {
            ofVec3f p = ax0.getInterpolated(ax1, float(ix)/ xDiv);
            ofVec3f ns = p + ofVec3f(frameCount) * 0.005;
            p.x += ofSignedNoise(ofVec3f(ns.x, ns.y, ns.z) * freq.x) * noiseSize;
            p.y += ofSignedNoise(ofVec3f(ns.y, ns.z, ns.x) * freq.y) * noiseSize;
            p.z += ofSignedNoise(ofVec3f(ns.z, ns.x, ns.y) * freq.z) * noiseSize;
            
            ofVec4f pp = VectorUtil::projectTo4f(p * BUFF_WIDTH / 8, cam, center) * 2;
            
            pp *= dispScale;
            pp += dispCenter + ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
            
            pts.push_back(pp);
        }
        points.push_back(pts);
    }
    
    int idx = 0;
    for (int iy = 0; iy < yDiv - 1; iy ++) {
        for (int ix = 0; ix < xDiv - 1; ix ++) {
            ofVec3f p0 = points[iy][ix];
            ofVec3f p1 = points[iy][ix + 1];
            ofVec3f p2 = points[iy + 1][ix];
            ofVec3f p3 = points[iy + 1][ix + 1];
            ofVec3f c0 = (p0 - p3).normalize();
            ofVec3f c1 = (p1 - p2).normalize();
            ofVec3f n = c1.getCrossed(c0);
            float a = float(frameCount) / 180 * PI;
            float lev = max(0.0f, n.dot(ofVec3f(sin(a), cos(a), 1.0)));
            ofFloatColor color = tiles[idx].baseColor;
            color.r *= lev * 1.5 + lev;
            color.g *= lev * 1.5 + lev;
            color.b *= (0.5 + lev) + lev;
            
            ofVec3f center = (p0 + p1 + p2 + p3) / 4;
            float offset = -0.2;
            p0 += (p0 - center) * offset;
            p1 += (p1 - center) * offset;
            p2 += (p2 - center) * offset;
            p3 += (p3 - center) * offset;
            
            tiles[idx].update(p0, p1, p2, p3, color);
            idx ++;
        }
    }
    
    frameCount ++;
}

void DrapeActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    for (int i = 0; i < tiles.size(); i ++) {
        
        auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(tiles[i].color, tiles[i].color, tiles[i].d));
        
        ofPolyline line = PolyLineUtil::PolyLineUtil::noiseWarp(tiles[i].polyline, 2, 8, 0.5, ofVec2f(1.f / BUFF_WIDTH) * 3.0, ofVec2f(20));
        
        auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 15, fill, line));
        conductor.addTool(tool);
    }
}


void DrapeActor::drawMain() {
    ofNoFill();
    //ofTranslate(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    
    
    int idx = 0;
    for (int iy = 0; iy < yDiv - 1; iy ++) {
        for (int ix = 0; ix < xDiv - 1; ix ++) {
            ofPushStyle();
            ofSetColor(tiles[idx].color);
            ofFill();
            ofBeginShape();
            ofVertex(tiles[idx].p0);
            ofVertex(tiles[idx].p1);
            ofVertex(tiles[idx].p3);
            ofVertex(tiles[idx].p2);
            ofEndShape(true);
            ofPopStyle();
            idx ++;
        }
    }
}



