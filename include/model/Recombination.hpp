#ifndef RECOMBINATION 
#define RECOMBINATION

#include "Individual.hpp"
#include <vector>

class IRecombination {
public:

    virtual std::vector<Individual> recombination (std::vector<Individual*> parents, double left_border, double right_border) = 0;

};

class LinealRecombination : virtual public IRecombination {
public:

    std::vector<Individual> recombination (std::vector<Individual*> parents, double left_border, double right_border) override;
};

class IntermediateRecombination : virtual public IRecombination {
public:

    std::vector<Individual> recombination (std::vector<Individual*> parents, double left_border, double right_border) override;
};

#endif
