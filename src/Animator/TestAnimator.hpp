
#pragma once

#include "Animator.hpp"
#include "TestActor.hpp"

class TestAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    vector<TestActor> testActors;
};
