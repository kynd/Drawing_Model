#include "SquishyActor.hpp"


SquishyActor::SquishyActor() {
    for (int i = 0; i < 8; i ++) {
        Squishy s = Squishy::rounded(ofRandom(240, 640));
        s.pos = ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
        squishies.push_back(s);
    }
}

void SquishyActor::update() {
    
    /*
    {
        float ang = float(frameCount) / 360 * TWO_PI;
        ofVec2f p = ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5 - 480) + ofVec2f(cos(ang), 0) * 720;
        squishies[1].pos = p;
    }
    
    {
        float ang = float(frameCount) / 360 * TWO_PI * 2;
        ofVec2f p = ofVec2f(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5 + 480) + ofVec2f(-cos(ang), 0) * 720;
        squishies[2].pos = p;
    }
     */
    
    /*
    {
        float ang = float(frameCount) / 360 * TWO_PI;
        ofVec2f p = ofVec2f(BUFF_WIDTH * 0.5 - 540, BUFF_HEIGHT * 0.5) + ofVec2f(0, cos(ang)) * 720;
        squishies[1].pos = p;
    }
    {
        float ang = float(frameCount) / 360 * TWO_PI * 1.5;
        ofVec2f p = ofVec2f(BUFF_WIDTH * 0.5 + 540, BUFF_HEIGHT * 0.5) + ofVec2f(0, -cos(ang)) * 720;
        squishies[2].pos = p;
    }
     */
    for (int i = 0; i < 8; i++) {
        float a1 = float(i) / squishies.size() * TWO_PI;
        float a2 = float(frameCount + i) / 1440 * TWO_PI * (i + 1) + a1 * 2;
        
        float x = BUFF_WIDTH / 2;
        float y = BUFF_HEIGHT/ 2;
        float d = 0.75+ ofSignedNoise(i * 0.1234) * 0.5;
        
        x -= BUFF_HEIGHT / 3 * sin(a2) * d;
        y -= BUFF_HEIGHT / 3 * cos(a2) * d;
        squishies[i].pos = ofVec2f(x, y);
    }
    
    for (int i = 0; i < 8; i++) {
        
        squishies[i].update();
    }
    
    for (int i = 0; i < squishies.size() - 1; i++) {
        for (int j = i + 1; j < squishies.size(); j++) {
            squishies[i].react(squishies[j]);
        }
    }
    frameCount ++;
}

void SquishyActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    for (int i = 0; i < squishies.size(); i++) {
        //auto fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(squishies[i].colorA, squishies[i].colorB, squishies[i].paintDir, 1.0, 1.0));
        
        //auto fill = shared_ptr<ShaderFill>(new SlideBleedShaderFill(squishies[i].colorA, squishies[i].colorB, squishies[i].paintDir));
        {
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, i, squishies[i].fill, squishies[i].line));
            conductor.addTool(tool);
        }
        {
            auto fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(squishies[i].colorA, squishies[i].colorB, squishies[i].paintDir, 1.0, 1.0));
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, i + 1, fill, squishies[i].line));
            conductor.addTool(tool);
        }
        
    }
}

void SquishyActor::drawMain() {
    ofNoFill();
    for (int i = 0; i < squishies.size(); i++) {
        squishies[i].draw();
    }
}
