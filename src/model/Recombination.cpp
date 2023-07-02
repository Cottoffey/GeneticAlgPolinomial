#include "headers/Recombination.hpp"
#include <time.h>
#include <random>

std::vector<Individual> LinealRecombination::recombination (std::vector<Individual*> parents) {
    
    std::vector<Individual> descendants (2);

    std::default_random_engine generator;
    generator.seed (clock());
    std::uniform_real_distribution<double> distribution (-0.25, 1.25);

    descendants[0].gen = parents[0]->gen + distribution(generator) * (parents[1]->gen - parents[0]->gen);
    descendants[1].gen = parents[0]->gen + distribution(generator) * (parents[1]->gen - parents[0]->gen);
    
    return descendants;
}

