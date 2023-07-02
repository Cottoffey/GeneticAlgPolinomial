#ifndef ALGCONFIG
#define ALGCONFIG
#include "Recombination.hpp"
#include "ParentSelection.hpp"
#include <vector>


class AlgConfig {
private:

    int                  individuals_number;  
    // int                  generations_number;
    std::vector<double>  polinomial_parametrs;
    double               range_min;
    double               range_max;
    int                  mutation_par;
    double               mutation_probability;
    int                  extreme;
    IRecombination*      recombination;
    IParentSelection*    parent_selection;

public:

    AlgConfig () = default;

    double metric (double x);

    // Setters
    bool setIndividualsNumber    (int number);
    // // bool setGenerationsNumber    (int number);
    bool setPolinomialParametrs  (std::vector<double> parametrs);
    bool setRange                (double min, double max);
    bool setMutationParametrs    (int par, double probability);
    bool setExtreme              (int ext);
    bool setRecombination        (IRecombination* _recombination);
    bool setParentSelection      (IParentSelection* _parent_selection);

    // Getters 
    int getIndividualsNumber();
    void getRange (double * min, double * max);
    double getMutationProbability ();
    double getMutationPar();
    IRecombination* getRecombination ();
    IParentSelection* getParentSelection ();
};

#endif