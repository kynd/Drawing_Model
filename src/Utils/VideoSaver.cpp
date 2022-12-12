#include "VideoSaver.hpp"


int VideoSaver::counter = 0;
int VideoSaver::baseTime = 0;

VideoSaver::VideoSaver() :
num(0)
{
    baseTime = ofGetUnixTime();
};

void VideoSaver::save(ofFbo& fbo) {
    ofImage image;
    ofPixels pixels;
    fbo.readToPixels(pixels);
    image.setFromPixels(pixels);
    
    counter ++;
    stringstream ss;
    ss << "outputTS/output_" << setfill('0') << setw(5) << right << baseTime << "_" << setfill('0') << setw(5) << right << counter <<
    ".jpg";
    file_name = ss.str();
    cout << "Saving file: " << file_name << &endl;
    image.save(file_name);
}


void VideoSaver::save(ofRectangle rect) {
    stringstream ss;
    ss << "output/output_" << setfill('0') << setw(5) << right << num << ".jpg";
    file_name = ss.str();
    saveFile(rect);
    num ++;
}

void VideoSaver::saveTS(ofRectangle rect) {
    int n = ofGetUnixTime();
    stringstream ss;
    ss << "outputTS/output_" << setfill('0') << setw(5) << right << n << ".jpg";
    file_name = ss.str();
    saveFile(rect);
}

void VideoSaver::saveFile(ofRectangle rect) {
    if (rect.width == 0 || rect.height == 0) {
        rect.width = ofGetWidth();
        rect.height = ofGetHeight();
    }
    
    img_saver.getTexture().clear();
    img_saver.grabScreen(rect.x, rect.y, rect.width, rect.height);
    cout << "Saving file: " << file_name << &endl;
    img_saver.save(file_name);
}

void VideoSaver::setNum(int n) {
    num = n;
}
