
#pragma once

#include "Animator.hpp"
#include "ShapeMorphActor.hpp"
#include "WaveTideActor.hpp"
#include "BoxActor.hpp"
#include "SolarActor.hpp"

class TestAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    vector<ShapeMorphActor> shapeMorphActors;
    //vector<Actor> actors;
    BoxActor boxActor;
    vector<SolarActor> solarActors;
    int nShapes = 4;
};
