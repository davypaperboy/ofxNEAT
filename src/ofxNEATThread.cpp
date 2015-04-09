//
//  ofxNEATThread.cpp
//  example_XOR_NEAT
//
//  Created by Davy Smith on 07/04/2015.
//
//

#include "ofxNEATThread.h"
#include "Genome.h"
#include "Population.h"
#include "NeuralNetwork.h"
#include "Parameters.h"
#include "Substrate.h"


using namespace NEAT;


class ofxNEATThreadImplementation
{

public:
    
    Population* population;
    ofxNEATFitnessFunction* fitness;
    Parameters parameters;
    int n_generations;
    double target_fitness;
    bool has_fitness_function;
    
    ofxNEATThreadImplementation()
    {
        target_fitness = -1;
        n_generations = -1;
        has_fitness_function = false;
    }
  
    ~ofxNEATThreadImplementation()
    {
        delete population;
    }
    
    void initDefaultNEATParameters()
    {
        parameters.PopulationSize = 150;
        parameters.DynamicCompatibility = true;
        parameters.WeightDiffCoeff = 4.0;
        parameters.CompatTreshold = 2.0;
        parameters.YoungAgeTreshold = 15;
        parameters.SpeciesMaxStagnation = 15;
        parameters.OldAgeTreshold = 35;
        parameters.MinSpecies = 5;
        parameters.MaxSpecies = 25;
        parameters.RouletteWheelSelection = false;
        parameters.RecurrentProb = 0.0;
        parameters.OverallMutationRate = 0.8;
        parameters.MutateWeightsProb = 0.90;
        parameters.WeightMutationMaxPower = 2.5;
        parameters.WeightReplacementMaxPower = 5.0;
        parameters.MutateWeightsSevereProb = 0.5;
        parameters.WeightMutationRate = 0.25;
        parameters.MaxWeight = 8;
        parameters.MutateAddNeuronProb = 0.03;
        parameters.MutateAddLinkProb = 0.05;
        parameters.MutateRemLinkProb = 0.0;
        parameters.MinActivationA  = 4.9;
        parameters.MaxActivationA  = 4.9;
        parameters.ActivationFunction_SignedSigmoid_Prob = 0.0;
        parameters.ActivationFunction_UnsignedSigmoid_Prob = 1.0;
        parameters.ActivationFunction_Tanh_Prob = 0.0;
        parameters.ActivationFunction_SignedStep_Prob = 0.0;
        parameters.CrossoverRate = 0.75;
        parameters.MultipointCrossoverRate = 0.4;
        parameters.SurvivalRate = 0.2;
    }

    void setTargetFitness(double t)
    {
        target_fitness = t;
    }
    
    void setFitnessFunction(ofxNEATFitnessFunction& func)
    {
        has_fitness_function = true;
        fitness = &func;
    }
    
    void doEvolution()
    {
        if (!has_fitness_function) {
            ofLog(OF_LOG_ERROR, "No Fitness Function Set!");
            return;
        }
        double bestf = -DBL_MAX;
        while ((population->getCurrentGeneration() < n_generations || n_generations == -1)
               && (bestf < target_fitness || target_fitness == -1) ) {
            for(unsigned int i = 0; i < population->getNumberOfSpecies(); ++i) {
                for(unsigned int j = 0; j < population->getSpecies(i)->m_Individuals.size(); ++j) {
                    double f = fitness->evaluate(population->getSpecies(i)->m_Individuals[j]);
                    population->getSpecies(i)->m_Individuals[j].SetFitness(f);
                    population->getSpecies(i)->m_Individuals[j].SetEvaluated();
                    bestf = (f > bestf) ? f : bestf;
                }
            }
            printf("Generation: %d, best fitness: %3.5f\n", population->getCurrentGeneration(), bestf);
            population->epoch();
        }
        ofLog(OF_LOG_NOTICE, (bestf >= target_fitness && target_fitness != -1) ? "Target Reached" : "Evolution Stopped");
    }

};

ofxNEATThread::ofxNEATThread() : p_impl(new ofxNEATThreadImplementation()) { }

ofxNEATThread::~ofxNEATThread()
{
    delete p_impl;
}

void ofxNEATThread::setTargetFitness(double target)
{
    p_impl->setTargetFitness(target);
}

void ofxNEATThread::setFitnessFunction(ofxNEATFitnessFunction &fitness)
{
    p_impl->setFitnessFunction(fitness);
}

void ofxNEATThread::initDefaultNEATParameters()
{
    p_impl->initDefaultNEATParameters();
}

void ofxNEATThread::setGenerations(int gens)
{
    p_impl->n_generations = gens;
}

unsigned int ofxNEATThread::getCurrentGeneration() const
{
    return p_impl->population->getCurrentGeneration();
}


void ofxNEATThread::threadedFunction()
{
    Genome genome(0, 3, 0, 1, true, UNSIGNED_SIGMOID, UNSIGNED_SIGMOID, 0, p_impl->parameters);
    p_impl->population = new Population(genome, p_impl->parameters, true, 1.0);
    p_impl->doEvolution();
}
