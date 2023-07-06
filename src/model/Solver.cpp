#include "../../include/model/Solver.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <time.h>

bool cmp(Individual first, Individual second)
{
    if (first.adaptability > second.adaptability)
        return true;
    return false;
}

Solver::Solver() : generation(0) {}

void Solver::init(AlgConfig *_config)
{
    generation.clear();

    config = _config;

    double min, max;
    config->getRange(&min, &max);

    std::default_random_engine generator;
    generator.seed(clock());
    std::uniform_real_distribution distribution(min, max);

    for (int i = 0; i < config->getIndividualsNumber(); i++)
    {
        Individual tmp(distribution(generator), distribution(generator));
        generation.push_back(tmp);
    }

    setAdaptability(generation);
    std::sort(generation.begin(), generation.end(), cmp);
}

void Solver::mutation(std::vector<Individual> &gen)
{
    std::default_random_engine generator;
    generator.seed(clock());
    std::uniform_real_distribution<double> distribution(0, 1);
    srand(clock());

    double min, max;
    config->getRange(&min, &max);

    double alpha = 0.5 * (max - min);
    double delta, tmp;
    double m = config->getMutationPar();
    double chance = config->getMutationProbability();

    for (auto elem : gen)
    {
        if (distribution(generator) < chance)
        {

            delta = 0;
            tmp = 0.5;

            for (int i = 1; i <= m; i++)
            {
                if (distribution(generator) < 1. / m)
                    delta += tmp;
                tmp /= 2.;
            }

            int index = rand() % 2;
            if (rand() % 2 == 0)
            {
                if (elem.gens[index] - delta * alpha > min)
                    elem.gens[index] -= delta * alpha;
            }
            else
            {
                if (elem.gens[index] + delta * alpha < max)
                    elem.gens[index] += delta * alpha;
            }
        }
    }
}

void Solver::setAdaptability(std::vector<Individual> &_generation)
{
    for (int i = 0; i < _generation.size(); i++)
    {
        _generation[i].adaptability = config->calculatePolinom(_generation[i].gens[1]) - config->calculatePolinom(_generation[i].gens[0]);
        // std::cout << generation[i].adaptability << std::endl;
    }
}

void Solver::calculateStep()
{
    std::vector<Individual> des_gen;
    std::vector<Individual> des_pair;

    // Parents selection and recombination
    double left_border, right_border;
    config->getRange(&left_border, &right_border);

    for (int i = 0; i < generation.size(); i++)
    {
        des_pair = config->getRecombination()->recombination(config->getParentSelection()->parentSelection(generation), left_border, right_border);
        des_gen.insert(des_gen.end(), des_pair.begin(), des_pair.end());
    }

    // Mutation
    mutation(des_gen);

    // Selection
    setAdaptability(des_gen);
    generation.insert(generation.begin(), des_gen.begin(), des_gen.end());
    std::sort(generation.begin(), generation.end(), cmp);
    generation.erase(generation.begin() + config->getIndividualsNumber(), generation.end());
}

std::vector<double> Solver::getGensMin()
{
    std::vector<double> result;
    for (int i = 0; i < generation.size(); i++)
    {

        result.push_back(generation[i].gens[0]);
    }
    // std::cout << "GET GENS MIN" << std::endl;
    return result;
}

std::vector<double> Solver::getGensMax()
{
    std::vector<double> result;
    for (int i = 0; i < generation.size(); i++)
    {

        result.push_back(generation[i].gens[1]);
    }

    return result;
}

std::vector<double> Solver::getBestIndivid()
{
    return generation[0].gens;
}

double Solver::getAverageAdaptability()
{
    double sum = 0;

    for (int i = 0; i < generation.size(); i++)
        sum += generation[i].adaptability;

    return sum / generation.size();
}