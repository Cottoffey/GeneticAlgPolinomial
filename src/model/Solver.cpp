#include "headers/Solver.hpp"
#include <random>
#include <algorithm>
#include <iostream>

bool cmp (Individual first, Individual second){
    if (first.adaptability < second.adaptability)
        return true;
    return false;
}

Solver::Solver (AlgConfig* _config) : config (_config), generation(0) {
    std::default_random_engine generator;
    double min, max;
    config->getRange (&min, &max);
    std::uniform_real_distribution distribution (min, max);

    for (int i = 0; i < config->getIndividualsNumber(); i++)
    {
        Individual tmp (distribution (generator));
        generation.push_back (tmp);
    }

    setAdaptability (generation);
    std::sort (generation.begin(), generation.end(), cmp);
}

void Solver::mutation (std::vector<Individual> & gen){

    std::default_random_engine generator;
    generator.seed (clock());
    std::uniform_real_distribution<double> distribution (0, 1);

    double min, max;
    config->getRange (&min, &max);

    double alpha = 0.5 * (max - min);
    double delta, tmp;
    double m = config->getMutationPar();
    double chance = config->getMutationProbability();

    for (auto elem : gen) {
        if (distribution (generator) < chance){

            delta = 0;
            tmp = 0.5;

            for (int i = 1; i <= m; i++) {
                if (distribution (generator) < 1./m)
                    delta += tmp;
                tmp /= 2.;
            }
            std::cout << delta << std::endl;

            if (distribution (generator) < 0.5)
                elem.gen -= delta * alpha;
            else
                elem.gen += delta * alpha;
        }
    }
}

void Solver::setAdaptability (std::vector<Individual> & _generation) {

    for (int i = 0; i < _generation.size(); i++)
        _generation[i].adaptability = config->metric (_generation[i].gen);
}


void Solver::calculateStep () {

    std::vector<Individual> des_gen;
    std::vector<Individual> des_pair;

    // Parents selection and recombination
    for (int i = 0; i < generation.size(); i++) {
        des_pair = config->getRecombination()->recombination (config->getParentSelection()->parentSelection (generation));
        des_gen.insert (des_gen.end(), des_pair.begin(), des_pair.end());
    }

    // Mutation 
    mutation (des_gen);

    // Selection 
    setAdaptability (des_gen);
    generation.insert (generation.begin(), des_gen.begin(), des_gen.end());
    std::sort(generation.begin(), generation.end(), cmp);
    generation.erase (generation.begin() + config->getIndividualsNumber(), generation.end());
}

void Solver::getBestSolution (double * x, double * y) {
    *x = generation[0].gen;
    *y = generation[0].adaptability;
}

double Solver::getAverageSolution () {
    double res = 0;
    for (auto elem : generation){
        res += elem.adaptability;
    }

    return res / generation.size();
}