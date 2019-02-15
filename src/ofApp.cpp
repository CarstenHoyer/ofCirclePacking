#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(800, 800, GL_RGBA);
    minRadius = 2;
    maxRadius = 100;
    totalCircles = 1000;
    createCircleAttempts = 500;
    doUpdate = true;
    ofSetBackgroundColor(255);
    ofEnableSmoothing();
    plotter = ofxGCodePlotter("/Users/carstenhoyer/Desktop/gcode.config", ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (doUpdate) {
        cout << "Draw\n";
        doUpdate = false;
        doDraw();
    }
    fbo.draw(0,0);
}

void ofApp::doDraw(){
    for (int i = 0; i < totalCircles; ++i) {
        createCircle();
    }
    fbo.begin();
    ofClear(255,255,255, 0);
    for(auto i = circles.begin(); i != circles.end(); ++i) {
        ofPath circle;
        circle.ellipse((*i).x, (*i).y, (*i).radius * 2, (*i).radius * 2);
        circle.setStrokeColor(0);
        circle.setStrokeWidth(2);
        circle.setCircleResolution(100);
        circle.draw();
        paths.push_back(circle);
    }
    fbo.end();
    fbo.draw(0,0);
}

void ofApp::createCircle(){
    float w = ofGetWidth();
    float h = ofGetHeight();
    Circle newCircle;
    bool circleSafeToDraw = false;
    for(int tries = 0; tries < createCircleAttempts; ++tries) {
        newCircle.x = floor(ofRandom(w));
        newCircle.y = floor(ofRandom(h));
        newCircle.radius = minRadius;
        
        if(doesCircleHaveACollision(newCircle)) {
            continue;
        } else {
            circleSafeToDraw = true;
            break;
        }
    }
    
    if(!circleSafeToDraw) {
        return;
    }
    
    for(int radiusSize = minRadius; radiusSize < maxRadius; ++radiusSize) {
        newCircle.radius = radiusSize;
        if(doesCircleHaveACollision(newCircle)){
            newCircle.radius--;
            break;
        }
    }
    
    circles.push_back(newCircle);
}

bool ofApp::doesCircleHaveACollision(Circle circle) {
    for(auto i = circles.begin(); i != circles.end(); ++i) {
        float a = circle.radius + (*i).radius;
        float x = circle.x - (*i).x;
        float y = circle.y - (*i).y;
        
        if (a >= sqrt((x*x) + (y*y))) {
            return true;
        }
    }
    
    if(circle.x + circle.radius >= ofGetWidth() ||
       circle.x - circle.radius <= 0) {
        return true;
    }
    
    if(circle.y + circle.radius >= ofGetHeight() ||
       circle.y - circle.radius <= 0) {
        return true;
    }
    
    return false;
}

void ofApp::printGcode(){
    vector<GCodePath> gps = plotter.generate(paths);
    plotter.print(gps);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
