//
//  ofApp.cpp
//  exampleSimpleXOR
//
//  Created by Davy Smith on 14/04/2015.
//
//

#include "ofApp.h"

void ofApp::setup()
{
    rtThread.setup();
    rtThread.startThread();
}

void ofApp::update()
{
    
}

const double getHeight(double fitness)
{
    return ofGetHeight() - (fitness * ( (double) ofGetHeight() / (double) 16));
}

void ofApp::draw()
{
    ofBackground(255, 255, 255);
    ofSetColor(255, 0, 0, 120);
    ofBeginShape();
    ofVertex(0, ofGetHeight());
    for (int i = 0; i < rtThread.fitnessResults().size(); i++) {
        fitness = rtThread.fitnessResults()[i];
        ofVertex(i * ((double) ofGetWidth() / (double) rtThread.fitnessResults().size()), getHeight(fitness));
    }
    ofVertex(ofGetWidth(), getHeight(fitness) );
    ofVertex(ofGetWidth(), ofGetHeight());
    ofVertex(ofGetWidth(), ofGetHeight());
    ofEndShape();
}

void ofApp::keyPressed(int key)
{
    if (key == 's' || key == 'S') {
        string dir = ofSystemSaveDialog("parameters.NEAT", "Please select directory to save").getPath();
    }
    else if (key == 'l' || key == 'L') {
        string dir = ofSystemLoadDialog("parameters.NEAT", "Please select file to load").getPath();
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}

