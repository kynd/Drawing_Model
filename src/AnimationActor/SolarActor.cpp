#include "SolarActor.hpp"

SolarEntityDef::SolarEntityDef() {
    baseDir = VectorUtil::randomUnitVec3();
    baseDir *= ofRandom(80, 300);
    axis = baseDir.getCrossed(VectorUtil::randomVec3(1)).normalize();
    size = ofRandom(10, 60);
    speed = ofRandom(0.1, 1);
    angle = ofRandom(360);
    rot = ofRandom(360);
    rotSpeed = ofRandom(0.1, 1);
    
    strokeColor = toolUtil.getRandomColor();
    for (int i = 0; i < 2; i ++) {
        fills.push_back(toolUtil.getRandomShaderFill());
    }
}

void SolarEntityDef::setParent(shared_ptr<SolarEntityDef> _parent) {
    hasParent = true;
    parent = _parent;
}


void SolarEntityDef::update() {
    ofVec3f center = hasParent ? parent->pos : ofVec3f(0);
    angle += speed;
    rot += rotSpeed;
    pos = center + baseDir.getRotated(angle, axis);
    
    
    trail.push_back(pos);
    if (trail.size() > 50) {
        trail.pop_front();
    }
}


SolarActor::SolarActor() {
    entities.push_back(shared_ptr<SolarEntityDef>( new SolarEntityDef()));
    entities[0]->baseDir *= 0.1;
    entities[0]->size = ofRandom(100, 200);
    
    for (int i = 0; i < 6; i ++) {
        auto def = shared_ptr<SolarEntityDef>( new SolarEntityDef());
        def->setParent(entities[0]);
        def->baseDir = ofVec3f((i + 1) * 20 + entities[0]->size * 0.5, 0, 0).rotate(ofRandom(360), ofVec3f(0, 0, 1));
        def->axis = ofVec3f(0, 0, 1);
        entities.push_back(def);
        
    }
    for (int i = 0; i < 6; i ++) {
        auto def = shared_ptr<SolarEntityDef>( new SolarEntityDef());
        
        if (ofRandom(1.0) < 0.5) {
            def->setParent(entities[0]);
        } else {
            int idx = ofRandom(1, 6);
            def->setParent(entities[idx]);
            def->baseDir.normalize();
            def->baseDir.normalize() *= ofRandom(entities[idx]->baseDir.length() * 0.5);
            def->size *= 0.5;
            def->speed *= ofRandom(entities[idx]->speed) * 5.0;
        }
        entities.push_back(def);
    }
    
    // ----
    
    boudaryFill = toolUtil.getRandomShaderFill();
    updateBoundaryBase();
}

void SolarActor::updateBoundaryBase() {
    
    ofVec2f rCenter = dispCenter + ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    ofVec2f rSize = ofVec2f(BUFF_WIDTH, BUFF_HEIGHT) * dispScale;
    ofVec2f topLeft = rCenter - rSize * 0.5;
    
    ofRectangle rect = ofRectangle(topLeft.x, topLeft.y, rSize.x, rSize.y);
    cout << rect << &endl;;
    boundaryLineBase = Illustrator::createBlobPath(rect)[0];
    
}
void SolarActor::setPosition(ofVec2f _center, ofVec2f _scale) {
    AnimationActor::setPosition(_center, _scale);
    updateBoundaryBase();
}

bool compareEntities(shared_ptr<SolarEntityDef> a, shared_ptr<SolarEntityDef> b) {
    return a->w > b->w;
}

void SolarActor::update() {
    float t = float(frameCount) / 720 * PI;
    ofVec3f cam = ofVec3f(sin(t), 0, cos(t)) * 900;
    cam = ofVec3f(0, 0, 900);
    ofVec3f center(0, 0, 0);
    
    for (auto entity : entities) {
        entity->update();
        ofVec4f p = VectorUtil::projectTo4f(entity->pos, cam, center) * 2;
        entity->w = p.w;
        
        p *= dispScale;
        p += dispCenter + ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
        
        float s = VectorUtil::projectTo4f(ofVec3f(entity->size, 0, entity->pos.z), cam, center).x;
        //entity->line = PolyLineUtil::oval(p.x - s* 0.5, p.y - s * 0.5, s,s );
        
        ofRectangle rect(p.x - s * 0.5, p.y - s * 0.5, s, s);
        entity->lines = Illustrator::eclipse(rect, entity->rot / 180 * PI);
        
        entity->lines.push_back(Illustrator::eclipse(rect, (entity->rot / 180 * PI) + PI)[0]);
        entity->update();
        
        
        ofPolyline line;
        for (int j = entity->trail.size() - 1; j > 0 ; j --) {
            ofVec3f p = VectorUtil::project(entity->trail[j], cam, center) * 2;
            p *= dispScale;
            p += dispCenter + ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
            line.curveTo(p);
            if (j == 0 || j == entity->trail.size() - 1) {
                line.curveTo(p);
            }
        }
       
        entity->trailLines = PolyLineUtil::toDottedLine(line, 24, 12);
    }
    
    sort(entities.begin(), entities.end(), compareEntities);
    
    
    boundaryLine = PolyLineUtil::noiseWarp(boundaryLineBase, 3, 4, 0.25, ofVec2f(1.f / BUFF_WIDTH), ofVec2f(100), ofVec2f(frameCount * 0.01));
    
    frameCount ++;
}

void SolarActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    {
        MaskTool* mt = new MaskTool(canvas, 0);
        auto maskTool = shared_ptr<Tool>(mt);
        auto _fill = new NoiseGradientShaderFill(ofFloatColor(1,1,1,1),ofFloatColor(1,1,1,1));
        shared_ptr<ShaderFill> maskFill = shared_ptr<ShaderFill>(_fill);
        
        auto tool = shared_ptr<Tool>(new ShaderFillTool(mt->getMask(), 0, maskFill, boundaryLine));
        mt->addMask(tool);
        
        for (int i = 0; i < entities.size(); i ++) {
            for (int j = 0; j < entities[i]->lines.size(); j ++) {
                auto tool = shared_ptr<Tool>(new ShaderFillTool(mt->getLocalCanvas(), i, entities[i]->fills[j], entities[i]->lines[j]));
                mt->addTool(tool);
            }
            
            
            for (int j = 0; j < entities[i]->trailLines.size(); j ++) {
            auto style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(entities[i]->strokeColor));
                auto tool = shared_ptr<Tool>(new RoundStrokeTool(mt->getLocalCanvas(), 100, style, entities[i]->trailLines[j], 4));
                mt->addTool(tool);
            }
        }
        
        conductor.addTool(maskTool);
    }
    
    
    {
        auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 2, boudaryFill, boundaryLine));
        conductor.addTool(tool);
    }
}


void SolarActor::drawMain() {
    ofNoFill();
    //ofTranslate(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    
    
    for (auto entity : entities) {
        for (auto line : entity->lines)  {
            line.draw();
        }
        for (auto line : entity->trailLines)  {
            line.draw();
        }
    }
    
    boundaryLine.draw();
    
    
}

