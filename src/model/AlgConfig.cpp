#include "headers/AlgConfig.hpp"

int AlgConfig::getIndividualsNumber(){
    return individuals_number;
}

void AlgConfig::getRange (double * min, double * max){
    *min = range_min;
    *max = range_max;
}

double AlgConfig::getMutationProbability (){
    return mutation_probability;
}

double AlgConfig::getMutationPar(){
    return mutation_par;
}

IRecombination* AlgConfig::getRecombination (){
    return recombination;
}
IParentSelection* AlgConfig::getParentSelection (){
    return parent_selection;
}

bool AlgConfig::setPolinomialParametrs  (std::vector<double> parametrs) {
    polinomial_parametrs = parametrs;
}

bool AlgConfig::setRange                (double min, double max) {
    range_max = max;
    range_min = min;
}

bool AlgConfig::setMutationParametrs    (int par, double probability){
    mutation_par = par;
    mutation_probability = probability;
}

bool AlgConfig::setExtreme              (int ext) {
    extreme = ext;
}

bool AlgConfig::setRecombination        (IRecombination* _recombination) {
    recombination = _recombination;
}

bool AlgConfig::setParentSelection      (IParentSelection* _parent_selection) {
    parent_selection = _parent_selection;
}

bool AlgConfig::setIndividualsNumber (int n) {
    individuals_number = n;
}

double AlgConfig::metric (double x) {
    double tmp = x;
    double res = polinomial_parametrs[0];

    for (int i = 1; i < 11; i++)
    {
        res += polinomial_parametrs[i] * tmp;
        tmp *= x;
    }
    return res;
}