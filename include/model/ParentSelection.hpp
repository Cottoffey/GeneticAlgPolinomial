#ifndef PARENTSELECTION
#define PARENTSELECTION

#include "Individual.hpp"
#include <vector>

class IParentSelection {
public:

    virtual std::vector<Individual*> parentSelection (std::vector<Individual> & generation) = 0;
};

class Panmixia : virtual public IParentSelection {
public:

    std::vector<Individual*> parentSelection (std::vector<Individual> & generation) override;
};

class Inbreeding :  virtual public IParentSelection {
public:

    std::vector<Individual*> parentSelection (std::vector<Individual> & generation) override;
};

class Outbreeding : virtual public IParentSelection {
public:

    std::vector<Individual*> parentSelection (std::vector<Individual> & generation) override;
};

#endif