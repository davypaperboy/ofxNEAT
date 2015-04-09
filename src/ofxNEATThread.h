//
//  ofxNEATThread.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 07/04/2015.
//
//

#pragma once

#include "ofMain.h"
#include "ofxNEATFitnessFunction.h"

class ofxNEATThreadImplementation;

class ofxNEATThread : public ofThread
{

    public:
    
    ofxNEATThread();
    ~ofxNEATThread();
    
    void initDefaultNEATParameters();
    void setTargetFitness(double target);
    void setFitnessFunction(ofxNEATFitnessFunction& fitness);
    void setGenerations(int gens);
    unsigned int getCurrentGeneration() const;

    private:
    
    void threadedFunction();
    
    ofxNEATThreadImplementation* p_impl;

};

