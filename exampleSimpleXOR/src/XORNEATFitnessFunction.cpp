//
//  XORNEATFitnessFunction.cpp
//  example_XOR_NEAT
//
//  Created by Davy Smith on 09/04/2015.
//
//

#include "XORNEATFitnessFunction.h"

double testNet(ofxNEATGenome& genome, double input_a, double input_b)
{
    std::vector<double> inputs;
    inputs.resize(3);
    inputs[0] = input_a;
    inputs[1] = input_b;
    inputs[2] = 1;
    return genome.activate(inputs)[0];
}

double xorTestNEAT(ofxNEATGenome& genome)
{
    genome.buildPhenotype();
    double error = 0;
    error += abs(testNet(genome, 1, 0) - 1.0);
    error += abs(testNet(genome, 0, 1) - 1.0);
    error += testNet(genome, 0, 0);
    error += testNet(genome, 1, 1);
    return  (4.0 - error)*(4.0 - error);
}

double XORNEATFitnessFunction::evaluate(ofxNEATGenome& genome)
{
    return xorTestNEAT(genome);
}
