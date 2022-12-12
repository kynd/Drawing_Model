#include "PlanetAnimator.hpp"

void PlanetAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
   
    float wSpan = float(BUFF_WIDTH) / n;
    float hSpan = float(BUFF_HEIGHT) / n;
    for (int i = 0; i < n; i ++) {
        vector<PlanetDef> cdefs;
        for (int j = 0; j < n; j ++) {
            shared_ptr<ShaderFill> fillA = randomFill();
            shared_ptr<ShaderFill> fillB = randomFill();
            ofRectangle rect(i * wSpan, j * hSpan, wSpan, hSpan);
            float ang = ofRandom(TWO_PI);
            float rot = ofRandom(TWO_PI);
            cdefs.push_back(PlanetDef(fillA, fillB, rect, ang, rot));
        }
        defs.push_back(cdefs);
    }
    
    for (int i = 0; i < n; i ++) {
        vector<PlanetDef> cdefs;
        for (int j = 0; j < n; j ++) {
            shared_ptr<ShaderFill> fillA = randomFill();
            shared_ptr<ShaderFill> fillB = randomFill();
            ofRectangle rect(i * wSpan, j * hSpan, wSpan, hSpan);
            float ang = ofRandom(TWO_PI);
            float rot = ofRandom(TWO_PI);
            cdefs.push_back(PlanetDef(fillA, fillB, rect, ang, rot));
        }
        defs2.push_back(cdefs);
    }
    backgroundColor = ofFloatColor(0.95, 0.90, 0.8, 1);
}

void PlanetAnimator::update(Conductor& conductor) {
    conductor.clear();
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            float ang = defs[i][j].ang + float(step) / 36 * TWO_PI;
            ofPolyline pl0 = Illustrator::eclipse(defs[i][j].rect, ang)[0];
            ofPolyline pl1 = Illustrator::eclipse(defs[i][j].rect, ang + PI)[0];
            
            ofRectangle rect = defs[i][j].rect ;
            ofVec3f tr(rect.x + rect.width * 0.5, rect.y + rect.height * 0.5, 0.0);
            pl0.translate(-tr);
            pl1.translate(-tr);
            pl0.rotateRad(defs[i][j].rot, ofVec3f(0,0,1));
            pl1.rotateRad(defs[i][j].rot, ofVec3f(0,0,1));
            pl0.translate(tr);
            pl1.translate(tr);
            
            auto tool0 = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, defs[i][j].fillA, pl0));
            auto tool1 = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, defs[i][j].fillB, pl1));
            conductor.addTool(tool0);
            conductor.addTool(tool1);
        }
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            float ang = defs2[i][j].ang + float(step) / 72 * TWO_PI;
            ofPolyline pl0 = Illustrator::eclipse(defs2[i][j].rect, ang)[0];
            ofPolyline pl1 = Illustrator::eclipse(defs2[i][j].rect, ang + PI)[0];
            
            ofRectangle rect = defs2[i][j].rect ;
            ofVec3f tr(rect.x + rect.width * 0.5, rect.y + rect.height * 0.5, 0.0);
            pl0.translate(-tr);
            pl1.translate(-tr);
            pl0.rotateRad(defs2[i][j].rot, ofVec3f(0,0,1));
            pl1.rotateRad(defs2[i][j].rot, ofVec3f(0,0,1));
            pl0.translate(tr);
            pl1.translate(tr);
            
            auto tool0 = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, defs2[i][j].fillA, pl0));
            auto tool1 = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, defs2[i][j].fillB, pl1));
            conductor.addTool(tool0);
            conductor.addTool(tool1);
        }
    }
    
    step += 1;
    
    canvas->begin();
    ofClear(backgroundColor);
    canvas->end();
}

shared_ptr<ShaderFill> PlanetAnimator::randomFill() {
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)) * 12.0;
    
    /*
    shared_ptr<ShaderFill> fill;
    float rnd = ofRandom(6.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        NoiseGradientShaderFill* _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 5.0) {
        fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
    } else {
        fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir * 0.1));
    }
     */
    
    auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
    return fill;
}

