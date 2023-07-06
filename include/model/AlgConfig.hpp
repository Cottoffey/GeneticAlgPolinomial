#ifndef ALGCONFIG
#define ALGCONFIG
#include "Recombination.hpp"
#include "ParentSelection.hpp"
#include <vector>


class AlgConfig {
private:

    int                  individuals_number;  
    std::vector<double>  polinomial_parametrs;
    double               range_min;
    double               range_max;
    int                  mutation_par;
    double               mutation_probability;
    IRecombination*      recombination;
    IParentSelection*    parent_selection;

public:

    AlgConfig () = default;

    double              calculatePolinom (double x);
    std::vector<double> calculatePolinom (std::vector<double>);

    // Setters
    void setIndividualsNumber    (int number);
    void setPolinomialParametrs  (std::vector<double> parametrs);
    void setRange                (double min, double max);
    void setMutationParametrs    (int par, double probability);
    void setRecombination        (IRecombination* _recombination);
    void setParentSelection      (IParentSelection* _parent_selection);

    // Getters 
    int                 getIndividualsNumber    ();
    void                getRange                (double * min, double * max);
    double              getMutationProbability  ();
    double              getMutationPar          ();
    IRecombination*     getRecombination        ();
    IParentSelection*   getParentSelection      ();
};

#endif