#include "VectorUtil.hpp"


ofVec2f VectorUtil::randomUnitVec2() {
    return ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)).normalize();
}

ofVec2f VectorUtil::randomVec2(float maxLength) {
    return randomUnitVec2() * ofRandom(maxLength);
}
