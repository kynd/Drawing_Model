#pragma once

#include "StrokeTool.hpp"

class FlatPenStrokeTool : public StrokeTool {
public:
    
    FlatPenStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofVec2f _dir, ofPolyline _taper = ofPolyline());
    virtual void setupMain();
    ofVec2f dir;
};
