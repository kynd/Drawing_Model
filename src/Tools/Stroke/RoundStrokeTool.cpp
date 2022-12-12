#include "RoundStrokeTool.hpp"

RoundStrokeTool::RoundStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofPolyline _taper) : StrokeTool(_canvas, _priority, _style, _shape, _width, _taper) {
    setup();
}

void RoundStrokeTool::setupMain() {
    mesh = PolyLineUtil::toRoundStrokeMesh(shape, width, resolution, taper);
}
