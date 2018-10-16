//
// Created by Mrugi on 2015-11-15.
//

#ifndef OK_TSP_GENETICALGORITHM_H
#define OK_TSP_GENETICALGORITHM_H

#include "../Solver.h"
#include "Path.h"
#include <algorithm>

class GeneticAlgorithm : public Solver {

public:
    void solve() override;

    std::string getName() override;

    unsigned countCurrentSolutionLength() override;

    void printSolutionPath() override;

    GeneticAlgorithm();

    GeneticAlgorithm(unsigned int populationSize, float mutationSize, int iterations);

    void printParameters() override;

    ~GeneticAlgorithm();
private:
    Path *pathSolution;
    float mutationChance;
    float mutationSize; // percent of gene mutation
    unsigned int populationSize = 20;
    int eliteSize; // gens that will not be crossed over
    int iterations = 100;
};


#endif //OK_TSP_GENETICALGORITHM_H
