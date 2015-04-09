//
//  XORNEATFitnessFunction.cpp
//  example_XOR_NEAT
//
//  Created by Davy Smith on 09/04/2015.
//
//

#include "XORNEATFitnessFunction.h"


double testNet(NEAT::NeuralNetwork& net, double input_a, double input_b, double output)
{
    std::vector<double> inputs;
    inputs.resize(3);
    
    net.Flush();
    inputs[0] = input_a;
    inputs[1] = input_b;
    inputs[2] = 1;
    net.Input(inputs);
    for(int i=0; i < 2; i++) {
        net.Activate();
    }
    double out = net.Output()[0];
    return std::abs(out - output);
}

double xorTestNEAT(NEAT::Genome& g)
{
    NEAT::NeuralNetwork net(false);
    g.BuildPhenotype(net);
    
    double error = 0;
    error += testNet(net, 1, 0, 1.0);
    error += testNet(net, 0, 1, 1.0);
    error += testNet(net, 0, 0, 0.0);
    error += testNet(net, 1, 1, 0.0);
    return  (4.0 - error)*(4.0 - error);
}

double XORNEATFitnessFunction::evaluate(NEAT::Genome &genome)
{
    return xorTestNEAT(genome);
}
