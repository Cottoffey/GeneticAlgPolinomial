#ifndef SOLVER
#define SOLVER

#include "AlgConfig.hpp"
#include <vector>

class Solver {
public: 

    std::vector<Individual> generation;
    AlgConfig*              config;

    void mutation (std::vector<Individual> &);
    void setAdaptability (std::vector<Individual> &);

public:
    Solver (AlgConfig * _config);
    
    void calculateStep ();
    void getBestSolution (double * x, double * y);
    double getAverageSolution ();
};

#endif