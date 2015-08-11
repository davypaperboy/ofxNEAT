//
//  rtNEATThread.h
//  exampleSimpleXOR
//
//  Created by Davy Smith on 14/04/2015.
//
//

#pragma once

#include "ofMain.h"
#include "ofxNEAT.h"
#include "XORNEATFitnessFunction.h"

class rtNEATThread : public ofThread {
    
public:
    void setup();
    std::vector<double>& fitnessResults();
    unsigned int populationSize() const;
    
private:
    XORNEATFitnessFunction xorFitness;
    ofxNEAT neat;
    
    double best_fitness;
    int last_killed;
    int last_baby;
    
    std::vector<double> fitness_results;
    
    void threadedFunction();
    
};