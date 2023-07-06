#include "../../include/model/AlgConfig.hpp"

#include <iostream>

int AlgConfig::getIndividualsNumber()
{
    return individuals_number;
}

void AlgConfig::getRange(double *min, double *max)
{
    *min = range_min;
    *max = range_max;
}

double AlgConfig::getMutationProbability()
{
    return mutation_probability;
}

double AlgConfig::getMutationPar()
{
    return mutation_par;
}

IRecombination *AlgConfig::getRecombination()
{
    return recombination;
}
IParentSelection *AlgConfig::getParentSelection()
{
    return parent_selection;
}

void AlgConfig::setPolinomialParametrs(std::vector<double> parametrs)
{
    polinomial_parametrs = parametrs;
}

void AlgConfig::setRange(double min, double max)
{
    range_max = max;
    range_min = min;
}

void AlgConfig::setMutationParametrs(int par, double probability)
{
    mutation_par = par;
    mutation_probability = probability;
}

void AlgConfig::setRecombination(IRecombination *_recombination)
{
    recombination = _recombination;
}

void AlgConfig::setParentSelection(IParentSelection *_parent_selection)
{
    parent_selection = _parent_selection;
}

void AlgConfig::setIndividualsNumber(int n)
{
    individuals_number = n;
}

double AlgConfig::calculatePolinom(double x)
{
    double tmp = x;
    double res = polinomial_parametrs[0];

    for (int i = 1; i < 11; i++)
    {
        // std::cout << "Parametrs " << polinomial_parametrs[i] << " tmp " << tmp << std::endl;
        res += polinomial_parametrs[i] * tmp;
        tmp *= x;
    }
    return res;
}

std::vector<double> AlgConfig::calculatePolinom(std::vector<double> x)
{
    std::vector<double> res;

    for (int i = 0; i < x.size(); i++)
    {
        res.push_back(0);
        double tmp = x[i];
        res[i] = polinomial_parametrs[0];
        for (int j = 1; j < 11; j++)
        {
            res[i] += polinomial_parametrs[j] * tmp;
            tmp *= x[i];
        }
    }

    return res;
}