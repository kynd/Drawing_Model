#include "ColorUtil.hpp"


ofFloatColor ColorUtil::rondomOpaqueColor() {
    return ofFloatColor(ofRandom(1), ofRandom(1), ofRandom(1), 1);
}
