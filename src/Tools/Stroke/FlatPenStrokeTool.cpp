#include "FlatPenStrokeTool.hpp"

FlatPenStrokeTool::FlatPenStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofVec2f _dir, ofPolyline _taper) : StrokeTool(_canvas, _priority, _style, _shape, _width, _taper) {
    dir = _dir;
    setup();
}

void FlatPenStrokeTool::setupMain() {
    mesh = PolyLineUtil::toFlatPenStrokeMesh(shape, width, dir, resolution, taper);
}
