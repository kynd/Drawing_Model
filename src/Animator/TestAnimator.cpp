#include "TestAnimator.hpp"

void TestAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    
    /*
    for (int i = -1; i <=1; i += 2) {
        for (int j = -1; j <=1; j += 2) {
            solarActors.push_back(SolarActor());
            
            solarActors[solarActors.size() - 1].setPosition(
                ofVec2f(    BUFF_WIDTH / 6 * i,
                            BUFF_HEIGHT / 6 * j) ,
                ofVec2f(0.66));
        }
    }
     */
    /*
    for (int i = 0; i < nShapes; i ++) {
        shapeMorphActors.push_back(ShapeMorphActor());
    }
    */
    //solarActors.push_back(SolarActor());
    
    
}

void TestAnimator::update(Conductor& conductor) {
    conductor.clear();
    
    /*
    for (int i = 0; i < solarActors.size(); i ++) {
        solarActors[i].update();
        solarActors[i].updateConductor(canvas, conductor);
    }
     */
    /*
    boxActor.updateConductor(canvas, conductor);
    for (int i = 0; i < nShapes; i ++) {
        shapeMorphActors[i].update();
        shapeMorphActors[i].updateConductor(canvas, conductor);
        conductor.getLastTool()->setPriority(i);
    }
    */
    /*
    boxActor.update();
    boxActor.updateConductor(canvas, conductor);
    
    drapeActor.update();
    drapeActor.updateConductor(canvas, conductor);
    */
    //candyClashActor.update();
    //candyClashActor.updateConductor(canvas, conductor);
    treeActor.update();
    treeActor.updateConductor(canvas, conductor);
}
