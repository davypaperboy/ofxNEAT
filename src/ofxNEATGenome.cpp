//
//  ofxNEATGenome.cpp
//  exampleSimpleXOR
//
//  Created by Davy Smith on 10/04/2015.
//
//

#include "ofxNEATGenome.h"
#include "Genome.h"

class ofxNEATGenomeImplementation {
    public:
    ofxNEATGenomeImplementation(NEAT::Genome genome) : m_genome(genome) {
    
    }
    
    NEAT::Genome m_genome;
    NEAT::NeuralNetwork network;
    
    void buildNetwork() {
        m_genome.buildPhenotype(network);
    }
    
    const std::vector<double> activate(std::vector<double> inputs) {
        network.Flush();
        m_genome.CalculateDepth();
        network.Input(inputs);
        for (unsigned int i = 0; i < m_genome.depth(); i++) {
            network.Activate();
        }
        return network.Output();
    }
};


ofxNEATGenome::ofxNEATGenome(NEAT::Genome genome) : p_impl(new ofxNEATGenomeImplementation(genome)) {}

ofxNEATGenome::~ofxNEATGenome() {
    delete p_impl;
}

NEAT::Genome& ofxNEATGenome::genome() {
    return p_impl->m_genome;
}

void ofxNEATGenome::setGenome(NEAT::Genome& genome) {
    p_impl->m_genome = genome;
}

void ofxNEATGenome::buildPhenotype() {
    p_impl->buildNetwork();
}

std::vector<double> ofxNEATGenome::activate(std::vector<double> inputs) {
    return p_impl->activate(inputs);
}
