//
//  XORNEATFitnessFunction.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 09/04/2015.
//
//

#pragma once

#include "ofxNEATFitnessFunction.h"
#include "ofxNEATGenome.h"

class XORNEATFitnessFunction : public ofxNEATFitnessFunction
{
    public:
    double evaluate(ofxNEATGenome& genome);
    
};