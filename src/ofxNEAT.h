//
//  ofxNEATThread.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 07/04/2015.
//
//

#pragma once

#include "ofMain.h"

class ofxNEATImplementation;
class ofxNEATFitnessFunction;

class ofxNEAT : public ofThread
{

    public:
    
    ofxNEAT();
    ~ofxNEAT();
    
    void initDefaultNEATParameters();
    void loadParameters(const string a_filename);
    void saveParameters(const string a_filename);
    
    void setupPopulation(unsigned int inputs, unsigned int hidden, unsigned int outputs);

    void setFitnessFunction(ofxNEATFitnessFunction& fitness);
    void setTargetFitness(const double target);
    void setNumberOfGenerations(const int gens);
    
    void evolveThreaded();
    void realTimeEvaluateFitnessAndTick(int& deceased_id, int& new_baby_id);
    void realTickWithoutEvaluation(int& deceased_id, int& new_baby_id);
    
    unsigned int currentGeneration() const;
    unsigned int populationSize() const;
    vector<unsigned int>& genomeIds();
    double bestFitness() const;

private:
    
    void threadedFunction();
    
    ofxNEATImplementation* p_impl;

};

