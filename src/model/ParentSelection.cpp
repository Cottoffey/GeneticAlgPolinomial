#include "headers/ParentSelection.hpp"
#include <iostream>
#include <random>
#include <cstdlib>
#include <time.h>

std::vector<Individual*> Panmixia::parentSelection (std::vector<Individual> & generation) {

    std::vector<Individual*> parents (2);

    int parent_1;
    int parent_2;

    srand (clock());

    do {
        parent_1 = rand() % generation.size();
        parent_2 = rand() % generation.size();
    } while (parent_1 == parent_2);

    parents[0] = &generation[parent_1];
    parents[1] = &generation[parent_2];

    std::cout << parent_1 << ' ' << parent_2 << std::endl;

    return parents;
}

std::vector<Individual*> Inbreeding::parentSelection (std::vector<Individual> & generation) {

    std::vector<Individual*> parents (2);

    srand (clock());

    int parent_1 = rand() % generation.size();
    int parent_2;

    if (parent_1 == 0)
        parent_2 = parent_1 + 1;
    else if (parent_1 == generation.size() - 1)
        parent_2 = parent_1 - 1;
    else {
        if (fabs (generation[parent_1-1].adaptability - generation[parent_1].adaptability) < fabs(generation[parent_1 + 1].adaptability - generation[parent_1].adaptability))
            parent_2 = parent_1 - 1;
        else 
            parent_2 = parent_1 + 1;
    }

    parents[0] = &generation[parent_1];
    parents[1] = &generation[parent_2];

    return parents;
}

std::vector<Individual*> Outbreeding::parentSelection (std::vector<Individual> & generation) {

    std::vector<Individual*> parents (2);

    srand (clock());

    int parent_1 = rand() % generation.size();
    int parent_2;

    if (parent_1 == 0)
        parent_2 = generation.size() - 1;
    else if (parent_1 == generation.size() - 1)
        parent_2 = 0;
    else {
        if (fabs (generation[0].adaptability - generation[parent_1].adaptability) > fabs(generation[generation.size() - 1].adaptability - generation[parent_1].adaptability))
            parent_2 = 0;
        else 
            parent_2 = generation.size() - 1;
    }

    parents[0] = &generation[parent_1];
    parents[1] = &generation[parent_2];

    return parents;
}
