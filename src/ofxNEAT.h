//
//  ofxNEAT.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 06/04/2015.
//
//

#pragma once
#include "ofMain.h"
#include "ofxNEATThread.h"
#include "ofxNEATFitnessFunction.h"

class ofxNEAT
{
  
public:
    
    void setFitnessFunction(ofxNEATFitnessFunction& fitness);
    void initDefaultNEATParameters();
    void setTargetFitness(double target);
    void setNumberOfGenerations(int gens);
    void evolve();

private:

    ofxNEATThread thread;
    
};
