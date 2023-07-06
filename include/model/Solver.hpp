#ifndef SOLVER
#define SOLVER

#include "AlgConfig.hpp"
#include <vector>

class Solver {
private: 

    std::vector<Individual>  generation;
    AlgConfig*               config;

    void mutation           (std::vector<Individual> &);
    void setAdaptability    (std::vector<Individual> &);

public:

    Solver ();
    void init (AlgConfig*);

    void calculateStep ();

    std::vector<double> getGensMin ();
    std::vector<double> getGensMax ();

    std::vector<double> getBestIndivid ();

    double getAverageAdaptability ();
};

#endif