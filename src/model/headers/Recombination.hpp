#ifndef RECOMBINATION 
#define RECOMBINATION

#include "Individual.hpp"
#include <vector>

class IRecombination {
public:

    virtual std::vector<Individual> recombination (std::vector<Individual*> parents) = 0;

};

class LinealRecombination : virtual public IRecombination {
public:

    std::vector<Individual> recombination (std::vector<Individual*> parents) override;
};

#endif
