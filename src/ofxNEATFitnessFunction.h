//
//  ofxNEATFitnessFunction.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 08/04/2015.
//
//

#pragma once

#include "ofMain.h"
#include "Genome.h"

class ofxNEATFitnessFunction
{
    public:
    virtual ~ofxNEATFitnessFunction() {};
    virtual double evaluate(NEAT::Genome& genome) = 0;
};


