//
//  ofxNEATFitnessFunction.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 08/04/2015.
//
//

#pragma once

#include "ofxNEATGenome.h"

class ofxNEATFitnessFunction
{
    public:
    virtual double evaluate(ofxNEATGenome& genome) = 0;
};


