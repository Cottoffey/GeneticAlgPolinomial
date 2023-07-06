#ifndef INDIVIDUAL
#define INDIVIDUAL
#include <vector>

class Individual {
public:
    std::vector<double> gens;
    double              adaptability;

    Individual () : gens(2) {};
    
    Individual (double _gen_min, double _gen_max) : gens (2) {
        
        gens[0] = _gen_min;
        gens[1] = _gen_max;
    }
};

#endif