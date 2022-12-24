#pragma once

#include "const.h"
#include "ofMain.h"
#include "Tool.hpp"
#include "TestTool.hpp"

class Conductor {
public:
    Conductor();
    void addTool(shared_ptr<Tool> tool);
    void runToolImmediately(shared_ptr<Tool> tool, int safetyCount = 30);
    void activate();
    bool getIsDone();
    void clear();
    void update();
    void debugDraw(bool drawAll = false);
    shared_ptr<Tool> getLastTool();
    
    vector< shared_ptr<Tool> > tools;
    int id = 0;
protected:
    bool isDone = false;
    static int idCnt;
};
