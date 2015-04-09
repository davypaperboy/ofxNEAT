//
//  ofxNEAT.cpp
//  example_XOR_NEAT
//
//  Created by Davy Smith on 06/04/2015.
//
//

#include "ofxNEAT.h"
#include "ofxNEATThread.h"



void ofxNEAT::initDefaultNEATParameters()
{
    thread.initDefaultNEATParameters();
}

void ofxNEAT::setNumberOfGenerations(int gens)
{
    thread.setGenerations(gens);
}

void ofxNEAT::setTargetFitness(double target)
{
    thread.setTargetFitness(target);
}

void ofxNEAT::setFitnessFunction(ofxNEATFitnessFunction &fitness)
{
    thread.setFitnessFunction(fitness);
}

void ofxNEAT::evolve()
{
    thread.startThread(true);
}