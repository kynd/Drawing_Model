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
    static bool compareToolPriorities(shared_ptr<Tool> a, shared_ptr<Tool> b);
    void activate();
    bool getIsDone();
    void clear();
    void update();
    void debugDraw(bool drawAll = false);
    shared_ptr<Tool> getLastTool();
    
    vector< shared_ptr<Tool> > tools;
    int id = 0;
protected:
    bool isSorted = false;
    bool isDone = false;
    static int idCnt;
};
