#pragma once

#include "Scenario.hpp"

class SketchScenario : public Scenario {
public:
    SketchScenario();
    virtual void grid2();
    virtual void watermelons();
    virtual void dragStrokeTest();
    virtual void blobPathTest();
    virtual void gridFBOTest();
    
    virtual void randomGridTest();
    virtual void randomGridTest2();
    

 
    ofRectangle randomRect(float minW = 200, float minH = 200, float maxW = 1200, float maxH = 1200);
    
    virtual void update();
    virtual void next();
    virtual void draw();
    
    
    int cnt = 0;
    virtual ofPolyline polyBlob();
    Conductor conductor;
    ofFloatColor backgroundColor;
    ColorSampler colorSampler;
    ToolUtil toolUtil;
};

