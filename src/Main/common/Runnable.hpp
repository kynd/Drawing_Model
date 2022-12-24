#pragma once

class Runnable {
public:
    virtual void update();
    virtual void draw();
    virtual void next();
    virtual void save();
};
