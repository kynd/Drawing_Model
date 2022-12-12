#pragma once

#include "Scenario.hpp"

class SketchScenario : public Scenario {
public:
    SketchScenario();
    virtual void grid();
    virtual void grid2();
    virtual void watermelons();
    virtual void dragStrokeTest();
    virtual void blobPathTest();
    virtual void gridFBOTest();
    
    virtual void imageTest();
    virtual void randomGridTest();
    virtual void randomGridTest2();
    virtual void paintTest();
    virtual void squiggleTest();
    
    
    shared_ptr<Tool> randomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority = 0);
    shared_ptr<Tool> randomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority = 0);
    shared_ptr<Tool> randomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority = 0, float minW = 1, float maxW = 8);
    ofRectangle randomRect(float minW = 200, float minH = 200, float maxW = 1200, float maxH = 1200);
    ofRectangle randomRect2(float minW = 200, float minH = 200, float maxW = 1200, float maxH = 1200);
    
    vector<ofRectangle> createRandomGrid(int nh, int nv);
    vector<ofRectangle> createRandomSquareGrid(int n);
    virtual void update();
    virtual void next();
    virtual void draw();
    
    virtual ofPolyline polyBlob();
    shared_ptr<ofFbo> canvas;
    Conductor conductor;
    ofFloatColor backgroundColor;
    ColorSampler colorSampler;
};

