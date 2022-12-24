#include "Conductor.hpp"

int Conductor::idCnt = 0;

Conductor::Conductor() {
    id = idCnt;
    idCnt ++;
    
};

void Conductor::addTool(shared_ptr<Tool> tool) {
    tools.push_back(tool);
}


shared_ptr<Tool> Conductor::getLastTool() {
    return tools[tools.size() - 1];
}

void Conductor::runToolImmediately(shared_ptr<Tool> tool, int safetyCount) {
    tool->activate();
    for (int i = 0; i < safetyCount; i ++) {
        tool->update();
        if (tool->getState() == Tool::COMPLETE) {
            break;
        }
        if (i == safetyCount - 1) {
            cout << "** WARNING ** runToolImmediately: the tool didn't finish within the safetyCount " << safetyCount << &endl;
        }
    }
}

void Conductor::activate() {
    float maxPriority = -9999999;
    //cout << &endl;
    // Get the lowest priority among active tools
    for (int i = 0; i < tools.size(); i ++) {
        maxPriority = max(maxPriority, tools[i]->getPriority());
    }
    
    
    // Loop and activate
    int doneCount = 0;
    for (int i = 0; i < tools.size(); i ++) {
        
        if (tools[i]->getState() == Tool::COMPLETE) { doneCount ++; continue; }
        if (tools[i]->getState() == Tool::ACTIVE){ continue; }
        if (tools[i]->getPriority() < maxPriority) { continue; }
        bool result = true;
        for (int j = 0; j < tools.size(); j ++) {
            if (tools[j]->getState() == Tool::ACTIVE &&
                tools[i]->getBoundingBox().intersects(tools[j]->getBoundingBox()) ) {
                    result = false; break;
            }
        }
        
        if (result) {
            //cout << "activate " << i << "(" << ofGetFrameNum() << ")" << &endl;
            tools[i]->activate();
        }
    }
}


bool Conductor::getIsDone() {
    return isDone;
}

void Conductor::clear() {
    isDone = false;
    tools.clear();
};


void Conductor::update() {
    int activeCnt = 0;
    for (int i = 0; i < tools.size(); i ++) {
        if (tools[i]->getState() == Tool::ACTIVE) {
            tools[i]->update();
            activeCnt ++;
        }
    }
    
    bool deleted = false;
    for (int i = tools.size() - 1; i >= 0; i --) {
        if (tools[i]->getState() == Tool::COMPLETE) {
            //cout << "delete " << i << "(" << ofGetFrameNum() << ")" << &endl;
            tools.erase(tools.begin() + i);
            deleted = true;
            
            if (tools.size() == 0) {
                //cout << "DONE" << &endl;
                isDone = true;
            }
        }
    }
    if (tools.size() > 0 && (activeCnt == 0 || deleted)) {
        activate();
    }
};

void Conductor::debugDraw(bool drawAll) {
    ofPushMatrix();
    ofScale(float(ofGetWidth()) / float(BUFF_WIDTH), float(ofGetHeight()) / float(BUFF_HEIGHT));
    for (int i = 0; i < tools.size(); i ++) {
        if (tools[i]->getState() == Tool::ACTIVE || drawAll) {
            tools[i]->debugDraw();
        }
    }
    ofPopMatrix();
};
