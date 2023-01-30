#include "Conductor.hpp"

int Conductor::idCnt = 0;

Conductor::Conductor() {
    id = idCnt;
    idCnt ++;
    
};

void Conductor::addTool(shared_ptr<Tool> tool) {
    isSorted = false;
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

bool Conductor::compareToolPriorities(shared_ptr<Tool> a, shared_ptr<Tool> b) {
    return a->getPriority() > b->getPriority();
}

void Conductor::activate() {
    if (!isSorted) {
        sort(tools.begin(), tools.end(), Conductor::compareToolPriorities);
        isSorted = true;
    }
    
    float maxPriority = tools[0]->getPriority();
    //cout << "MAX: " << maxPriority << &endl;
    //cout << &endl;
    // Get the lowest priority among active tools
    /*
     for (int i = 0; i < tools.size(); i ++) {
     maxPriority = max(maxPriority, tools[i]->getPriority());
     }
     */
    // Loop and activate
    int doneCount = 0;
    int activeCount = 0;
    bool hasActiveMultiStep = false;
    for (int i = 0; i < tools.size(); i ++) {
        if (activeCount >= 300) {break;}
        if (tools[i]->getState() == Tool::COMPLETE) { doneCount ++; continue; }
        if (tools[i]->getState() == Tool::ACTIVE){
            activeCount ++;
            hasActiveMultiStep |= tools[i]->isMultiStep();
            continue;
        }
        
        if (tools[i]->getPriority() >= maxPriority) {
            bool result = true;
            for (int j = 0; j < tools.size(); j ++) {
                if (tools[j]->getState() == Tool::ACTIVE &&
                    tools[i]->getBoundingBox().intersects(tools[j]->getBoundingBox()) ) {
                    result = false; break;
                }
            }
            
            if (result) {
                tools[i]->activate();
                activeCount ++;
                hasActiveMultiStep |= tools[i]->isMultiStep();
                //cout << "A" << i << " prio" << tools[i]->getPriority() <<" " << hasActiveMultiStep <<  &endl;
            }
        } else {
            if (!hasActiveMultiStep) {
                tools[i]->activate();
                activeCount ++;
                hasActiveMultiStep |= tools[i]->isMultiStep();
                
                //cout << "B" << i << " prio" << tools[i]->getPriority() <<" " << hasActiveMultiStep <<  &endl;
            }
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
    for (int i = int(tools.size()) - 1; i >= 0; i --) {
        if (tools[i]->getState() == Tool::COMPLETE) {
            //cout << "delete " << i << "(" << ofGetFrameNum() << ")" << &endl;
            tools.erase(tools.begin() + i);
            deleted = true;
            
        }
    }
    
    if (tools.size() == 0) {
        //cout << "DONE" << &endl;
        isDone = true;
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
