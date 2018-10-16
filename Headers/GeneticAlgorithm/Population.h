//
// Created by Mrugi on 2016-01-06.
//

#ifndef OK_TSP_POPULATION_H
#define OK_TSP_POPULATION_H

#include "Path.h"

class Population {
public:
    Population(unsigned int populationSize, float mutationSize, Graph *graph);

    void sortPopulation();

    Path *get(int i);

    void makeNewPopulation();

    void print();

    ~Population();

    Path *getBestAndClean();

private:
    minstd_rand0 randomGenerator;
    unsigned int populationSize;
    vector<Path *> population;
};

#endif //OK_TSP_POPULATION_H
