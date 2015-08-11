//
//  ofxNEATGenome.h
//  exampleSimpleXOR
//
//  Created by Davy Smith on 10/04/2015.
//
//

#pragma once

#include "ofMain.h"

class ofxNEATGenomeImplementation;

namespace NEAT { class Genome; }

class ofxNEATGenome
{
    public:
    
    ofxNEATGenome(NEAT::Genome genome);
    ~ofxNEATGenome();
    
    NEAT::Genome& genome();
    void setGenome(NEAT::Genome& genome);
    
    void buildPhenotype();
    std::vector<double> activate(std::vector<double> inputs);
    
    private:
    
    ofxNEATGenomeImplementation* p_impl;
    
};
