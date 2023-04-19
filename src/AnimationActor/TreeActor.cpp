#include "TreeActor.hpp"


TreeActor::TreeActor() {
    color = toolUtil.getRandomColor();
}

void TreeActor::update() {
    lines = I_Tree::branchToPolylines(I_Tree::createTree(1, frameCount * 0.001), ofVec3f(BUFF_WIDTH / 2, BUFF_HEIGHT, 0), BUFF_HEIGHT);

    frameCount ++;
}

void TreeActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    
    for (int i = 0; i < lines.size(); i++) {
        int priority = i;
        
        if (i >= styles.size()) {
            auto style = toolUtil.getRandomStrokeStyle();
            styles.push_back(style);
        }
        if (i >= fills.size()) {
            auto fill = toolUtil.getRandomShaderFill();
            fills.push_back(fill);
        }
        
        {
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fills[i], lines[i]));
            conductor.addTool(tool);
        }
        {
            ofPolyline taper = PolyLineUtil::createTaperNtoN(2, 1);
            auto tool = shared_ptr<Tool>(new RoundStrokeTool(canvas, priority, styles[i], lines[i], 2, taper));
            conductor.addTool(tool);
        }
    }
}

void TreeActor::drawMain() {
    ofNoFill();
    for (int i = 0; i < lines.size(); i++) {
        lines[i].draw();
    }
}
