#pragma once

#include "StrokeTool.hpp"

class BasicStrokeTool : public StrokeTool {
public:
    
    BasicStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofPolyline _taper = ofPolyline());
    virtual void setupMain();
};
