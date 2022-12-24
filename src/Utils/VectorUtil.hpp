#pragma once

#include "const.h"
#include "ofMain.h"


class VectorUtil {
public:
    static ofVec2f randomUnitVec2();
    static ofVec2f randomVec2(float maxLength = 1);
};
