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
    public:
        void solve() override;
        std::string getName() override;
        unsigned countCurrentSolutionLength() override;

        virtual void printSolutionPath() override;
        GeneticAlgorithm();
        GeneticAlgorithm(unsigned int populationSize, int iterations);
        ~GeneticAlgorithm();


    virtual void printParameters() override;

private:
        Path* pathSolution;
        float mutationChance;
        float mutationSize; //percent of gene mutation
        unsigned int populationSize=5;
        int eliteSize; //gens that will not be crossed over
    int iterations=100;
};


#endif //OK_TSP_GENETICALGORITHM_H
