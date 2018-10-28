#ifndef TSP_POPULATION_H
#define TSP_POPULATION_H

#include "Path.h"
#include <algorithm>

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
    unsigned int populationSize;
    std::vector<Path *> population;
};

#endif //TSP_POPULATION_H
