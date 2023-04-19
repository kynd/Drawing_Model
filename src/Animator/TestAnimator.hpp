
#pragma once

#include "Animator.hpp"
#include "ShapeMorphActor.hpp"
#include "WaveTideActor.hpp"
#include "BoxActor.hpp"
#include "SolarActor.hpp"
#include "DrapeActor.hpp"
#include "CandyClashActor.hpp"
#include "SquishyActor.hpp"
#include "TreeActor.hpp"



class TestAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    vector<ShapeMorphActor> shapeMorphActors;
    BoxActor boxActor;
    vector<SolarActor> solarActors;
    CandyClashActor candyClashActor;
    DrapeActor drapeActor;
    SquishyActor squishyActor;
    TreeActor treeActor;
    int nShapes = 4;
};
