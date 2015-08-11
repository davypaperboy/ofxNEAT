//
//  ofxNEATThread.cpp
//  example_XOR_NEAT
//
//  Created by Davy Smith on 07/04/2015.
//
//


#include "ofxNEAT.h"
#include "ofxNEATFitnessFunction.h"

#include "Genome.h"
#include "Population.h"
#include "NeuralNetwork.h"
#include "Parameters.h"
#include "Substrate.h"


using namespace NEAT;


class ofxNEATImplementation {

public:
    
    const static bool DO_LOG = false;
    
    Population* population;
    ofxNEATFitnessFunction* fitness;
    Parameters parameters;
    int n_generations;
    double target_fitness;
    double best_fitness_ever;
    bool has_fitness_function;
    bool first_evaluation;
    
    vector<unsigned int> genome_ids;
    Genome* template_genome;
    
    ofxNEATGenome* baby;
    Genome dead_genome;
    Genome baby_genome;
    
    ofxNEATImplementation() {
        target_fitness = -1;
        n_generations = -1;
        has_fitness_function = false;
        first_evaluation = true;
        best_fitness_ever = -DBL_MAX;
    }
  
    ~ofxNEATImplementation() {
        delete population;
        delete baby;
        delete template_genome;
    }
    
    void addStartingGenomeIDs() {
        for (unsigned int i = 0; i < parameters.PopulationSize; ++i) {
            genome_ids.push_back(i);
        }
    }

    void replaceGenomeID(unsigned int old_genome_id, unsigned int new_genome_id) {
        int pos = find(genome_ids.begin(), genome_ids.end(), old_genome_id) - genome_ids.begin();
        if (pos > parameters.PopulationSize) {
            ofLog(OF_LOG_ERROR) << " Genome ID: " << old_genome_id << " not found!!";
        }
        else {
            genome_ids[pos] = new_genome_id;
        }
        std::sort(genome_ids.begin(), genome_ids.end());
    }
    
    void setFitnessFunction(ofxNEATFitnessFunction& func) {
        has_fitness_function = true;
        fitness = &func;
    }
    
    void doEvolution() {
        if (!has_fitness_function) {
            ofLog(OF_LOG_ERROR, "No Fitness Function Set!");
            return;
        }
        while ((population->currentGeneration() < n_generations || n_generations == -1)
               && (best_fitness_ever < target_fitness || target_fitness == -1) ) {
            fullPopulationEvaluation();
            population->epoch();
        }
        ofLog(OF_LOG_NOTICE, (best_fitness_ever >= target_fitness && target_fitness != -1) ? "Target Reached" : "Evolution Stopped");
    }

    void rtTick(bool eval, int& deceased_id,  int& new_baby_id) {
        if (first_evaluation) {
            first_evaluation = false;
            if (eval) {
                fullPopulationEvaluation();
            }
            population->realTimeTick(dead_genome, baby_genome);
            baby = new ofxNEATGenome(baby_genome);
        }
        else {
            population->realTimeTick(dead_genome, baby_genome);
            baby->setGenome(baby_genome);
        }
        if (eval) {
            double f = fitness->evaluate(*baby);
            baby->genome().setObjectiveFitness(f);
            best_fitness_ever = (f > best_fitness_ever) ? f : best_fitness_ever;
            log(f);
        }
        deceased_id = dead_genome.ID();
        new_baby_id = baby_genome.ID();
        replaceGenomeID(deceased_id, new_baby_id);
    }
    
    void fullPopulationEvaluation() {
        double best_f_gen = -DBL_MAX;
        
        for(unsigned int i = 0; i < population->numberOfSpecies(); ++i) {
            for(unsigned int j = 0; j < population->numberOfIndividualsInSpeciesAtIndex(i); ++j) {
                ofxNEATGenome genome(population->speciesAtIndex(i).individualAtIndex(j));
                double f = fitness->evaluate(genome);
                population->speciesAtIndex(i).individualAtIndex(j).setObjectiveFitness(f);
                best_f_gen = (f > best_f_gen) ? f : best_f_gen;
            }
        }
        best_fitness_ever = (best_f_gen > best_fitness_ever) ? best_f_gen : best_fitness_ever;
        log(best_f_gen);
    }
    
    void log(double gen_fit) {
        if (DO_LOG) {
            ofLog(OF_LOG_NOTICE)<< "Evaluations: " << population->numberOfEvaluations()
                                << " Generation: " << population->currentGeneration()
                                << " Best Fitness: " << best_fitness_ever
                                << " Species: " << population->numberOfSpecies()
                                << " Population: " << population->numberOfGenomes();
        }
    }
};

ofxNEAT::ofxNEAT() : p_impl(new ofxNEATImplementation()) { }

ofxNEAT::~ofxNEAT() {
    delete p_impl;
}

void ofxNEAT::setTargetFitness(double target) {
    p_impl->target_fitness = target;
}

void ofxNEAT::setFitnessFunction(ofxNEATFitnessFunction &fitness) {
    p_impl->setFitnessFunction(fitness);
}

void ofxNEAT::initDefaultNEATParameters() {
    p_impl->parameters.neatDefaults();
}

void ofxNEAT::loadParameters(const string a_filename) {
    p_impl->parameters.Load(a_filename.c_str());
}

void ofxNEAT::saveParameters(const string a_filename) {
    p_impl->parameters.Save(a_filename.c_str());
}

void ofxNEAT::setupPopulation(unsigned int inputs, unsigned int hidden, unsigned int outputs) {
    Genome genome(0, inputs, hidden, outputs, true, UNSIGNED_SIGMOID, UNSIGNED_SIGMOID, 0, p_impl->parameters);
    p_impl->population = new Population(SINGLE_OBJECTIVE, genome, p_impl->parameters, true, 1.0);
    p_impl->addStartingGenomeIDs();
}

void ofxNEAT::setNumberOfGenerations(int gens) {
    p_impl->n_generations = gens;
}

unsigned int ofxNEAT::currentGeneration() const {
    return p_impl->population->currentGeneration();
}

unsigned int ofxNEAT::populationSize() const {
    return p_impl->parameters.PopulationSize;
}

vector<unsigned int>& ofxNEAT::genomeIds() {
    return p_impl->genome_ids;
}

double ofxNEAT::bestFitness() const
{
    return p_impl->best_fitness_ever;
}

void ofxNEAT::realTickWithoutEvaluation(int& deceased_id, int& new_baby_id) {
    p_impl->rtTick(false, deceased_id, new_baby_id);
}

void ofxNEAT::realTimeEvaluateFitnessAndTick(int& deceased_id, int& new_baby_id) {
    p_impl->rtTick(true, deceased_id, new_baby_id);
}

void ofxNEAT::threadedFunction() {
    p_impl->doEvolution();
}
