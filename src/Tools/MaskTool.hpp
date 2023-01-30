#pragma once

#include "Tool.hpp"
#include "Conductor.hpp"

class MaskTool : public Tool {
public:
    MaskTool(shared_ptr<ofFbo> _canvas, float _priority);
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void firstUpdate();
    virtual void debugDraw();
    shared_ptr<ofFbo> getLocalCanvas();
    shared_ptr<ofFbo> getMask();
    void allocateMask();
    void addTool(shared_ptr<Tool> tool);
    void addMask(shared_ptr<Tool> tool);
protected:
    bool wasUpdated = false;
    static void initialize();
    shared_ptr<ofFbo> localCanvas, mask;
    Conductor conductor;
    vector<shared_ptr<Tool> > tools;
    vector<shared_ptr<Tool> > masks;
    
    static bool isInitialized;
    static ofShader maskShader;
    static ofFbo canvasCopy;
};
