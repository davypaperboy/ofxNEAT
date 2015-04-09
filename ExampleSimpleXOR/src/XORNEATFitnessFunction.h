//
//  XORNEATFitnessFunction.h
//  example_XOR_NEAT
//
//  Created by Davy Smith on 09/04/2015.
//
//

#pragma once

#include "ofxNEATFitnessFunction.h"
#include "Genome.h"

class XORNEATFitnessFunction : public ofxNEATFitnessFunction
{
    public:
    double evaluate(NEAT::Genome& genome);
    
};