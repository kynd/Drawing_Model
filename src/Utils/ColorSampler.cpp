#include "ColorSampler.hpp"

void ColorSampler::load(string path) {
    img.load(path);
}

ofColor ColorSampler::getRandomColor() {
    int x = ofRandom(0, img.getWidth());
    int y = ofRandom(0, img.getHeight());
    return img.getColor(x, y);
}
