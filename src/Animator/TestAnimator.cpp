#include "TestAnimator.hpp"

void TestAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    for (int i = 0; i < 8; i ++) {
        testActors.push_back(TestActor(i/ 2 + 2));
    }
}

void TestAnimator::update(Conductor& conductor) {
    conductor.clear();
    for (int i = 0; i < 8; i ++) {
        testActors[i].update();
        testActors[i].updateConductor(canvas, conductor);
        conductor.getLastTool()->setPriority(i);
    }
    
}
