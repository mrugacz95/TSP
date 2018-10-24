#ifndef TSP_GENETICALGORITHM_H
#define TSP_GENETICALGORITHM_H

#include "Solver.h"
#include "Path.h"

#include <algorithm>

class GeneticAlgorithm : public Solver {

public:
    void solve() override;

    std::string getName() override;

    unsigned countCurrentSolutionLength();


    GeneticAlgorithm();

    GeneticAlgorithm(unsigned int populationSize, float mutationSize, int iterations);

    void printParameters() override;

    ~GeneticAlgorithm() override;

private:
    Path *pathSolution;
    float mutationChance;
    float mutationSize; // percent of gene mutation
    unsigned int populationSize = 20;
    int eliteSize; // gens that will not be crossed over
    int iterations = 100;
};


#endif //TSP_GENETICALGORITHM_H
