#include "../../include/model/Recombination.hpp"
#include <time.h>
#include <random>

std::vector<Individual> IntermediateRecombination::recombination(std::vector<Individual *> parents, double left_border, double right_border)
{
    std::vector<Individual> descendants(2);

    std::default_random_engine generator;
    generator.seed(clock());
    std::uniform_real_distribution<double> distribution(-0.25, 1.25);

    double coeff;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            do
            {
                coeff = distribution(generator);
            } while (parents[0]->gens[j] + coeff * (parents[1]->gens[j] - parents[0]->gens[j]) <= left_border ||
                     parents[0]->gens[j] + coeff * (parents[1]->gens[j] - parents[0]->gens[j]) >= right_border);

            descendants[i].gens[j] = parents[0]->gens[j] + coeff * (parents[1]->gens[j] - parents[0]->gens[j]);
        }
    }
    return descendants;
}

std::vector<Individual> LinealRecombination::recombination(std::vector<Individual *> parents, double left_border, double right_border)
{
    std::vector<Individual> descendants(2);

    std::default_random_engine generator;
    generator.seed(clock());
    std::uniform_real_distribution<double> distribution(-0.25, 1.25);

    double coeff;
    for (int i = 0; i < 2; i++)
    {

        do
        {
            coeff = distribution(generator);
        } while (parents[0]->gens[0] + coeff * (parents[1]->gens[0] - parents[0]->gens[0]) <= left_border ||
                 parents[0]->gens[0] + coeff * (parents[1]->gens[0] - parents[0]->gens[0]) >= right_border ||
                 parents[0]->gens[1] + coeff * (parents[1]->gens[1] - parents[0]->gens[1]) <= left_border ||
                 parents[0]->gens[1] + coeff * (parents[1]->gens[1] - parents[0]->gens[1]) >= right_border);

        descendants[i].gens[0] = parents[0]->gens[0] + coeff * (parents[1]->gens[0] - parents[0]->gens[0]);
        descendants[i].gens[1] = parents[0]->gens[1] + coeff * (parents[1]->gens[1] - parents[0]->gens[1]);
    }

    return descendants;
}
