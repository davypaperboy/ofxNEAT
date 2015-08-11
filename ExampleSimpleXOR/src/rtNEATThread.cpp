//
//  rtNEATThread.cpp
//  exampleSimpleXOR
//
//  Created by Davy Smith on 14/04/2015.
//
//

#include "rtNEATThread.h"

void rtNEATThread::setup()
{
    neat.setFitnessFunction(xorFitness);
    
    // Initialise defaults
    neat.initDefaultNEATParameters();
    
    // Setup Population With 3 inputs, 0 hidden, 1 output
    neat.setupPopulation(3, 0, 1);
    
    // Either Stop after 1000 generations
    neat.setNumberOfGenerations(1000);
    
    // Or when we reach the target
    neat.setTargetFitness(15.999);
  
}

unsigned int rtNEATThread::populationSize() const {
    return neat.populationSize();
}

void rtNEATThread::threadedFunction()
{
    while (true) {
        neat.realTimeEvaluateFitnessAndTick(last_killed, last_baby);
        best_fitness = neat.bestFitness();
        fitness_results.push_back(best_fitness);
    }
}

std::vector<double>& rtNEATThread::fitnessResults()
{
    return fitness_results;
}



