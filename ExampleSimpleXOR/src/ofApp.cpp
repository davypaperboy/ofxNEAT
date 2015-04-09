#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // Setup Overidden Fitness Function
    neat.setFitnessFunction(xorFitness);
    
    // Initialise defaults
    neat.initDefaultNEATParameters();
    
    // Either Stop after 1000 generations
    neat.setNumberOfGenerations(1000);
    
    // Or when we reach the target
    neat.setTargetFitness(15.999);
    
    // Go!!
    neat.evolve();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(ofRandom(255), ofRandom(255), ofRandom(255));
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
