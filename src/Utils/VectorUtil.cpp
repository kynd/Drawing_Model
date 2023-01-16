#include "VectorUtil.hpp"


ofVec2f VectorUtil::randomUnitVec2() {
    return ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)).normalize();
}

ofVec2f VectorUtil::randomVec2(float maxLength) {
    return randomUnitVec2() * ofRandom(maxLength);
}

ofVec3f VectorUtil::randomUnitVec3() {
    return ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)).normalize();
}

ofVec3f VectorUtil::randomVec3(float maxLength) {
    return randomUnitVec3() * ofRandom(maxLength);
}



ofVec4f VectorUtil::toV4(ofVec3f v) {
    return ofVec4f(v.x, v.y, v.z, 1.0);
}

ofVec3f VectorUtil::toV3(ofVec4f v) {
    return ofVec3f(v.x, v.y, v.z);
}

ofVec3f VectorUtil::project(ofVec3f p, ofVec3f cam, ofVec3f center, float fov, float aspect) {
    ofVec4f pp = projectTo4f(p, cam, center);
    return toV3(pp);
}


ofVec4f VectorUtil::projectTo4f(ofVec3f p, ofVec3f cam, ofVec3f center, float fov, float aspect) {
    
    ofMatrix4x4 perspective = ofMatrix4x4::newPerspectiveMatrix(fov, aspect, 100, 2000);
    
    //cout << perspective << &endl<< &endl<< &endl;
    ofMatrix4x4 view;
    view.makeLookAtViewMatrix(cam, center, ofVec3f(0, 1, 0));
    ofVec4f pp = toV4(p);
    
    pp = pp * view;
    
    pp = pp * perspective;
    pp.x /= pp.w;
    pp.y /= -pp.w;
    pp.z /= pp.w;
    
    //cout << pp << &endl;
    
    pp.x *= BUFF_WIDTH * 0.5;
    pp.y *= BUFF_WIDTH * 0.5;
    pp.z *= BUFF_WIDTH * 0.5;
    return pp;
}
