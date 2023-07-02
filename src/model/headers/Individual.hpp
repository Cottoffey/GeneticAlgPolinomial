#ifndef INDIVIDUAL
#define INDIVIDUAL

class Individual {
public:
    double gen;
    double adaptability;

    Individual () {};
    Individual (double _gen) : gen(_gen) {}
};

#endif