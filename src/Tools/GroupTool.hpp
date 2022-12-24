#pragma once

#include "Tool.hpp"
#include "Conductor.hpp"

class GroupTool : public Tool {
public:
    GroupTool(shared_ptr<ofFbo> _canvas, float _priority);
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void debugDraw();
    void addTool(shared_ptr<Tool> tool);
protected:
    static void initialize();
    Conductor conductor;
    vector<shared_ptr<Tool> > tools;
    static bool isInitialized;
};
