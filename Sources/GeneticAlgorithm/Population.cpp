//
// Created by Mrugi on 2016-01-06.
//

#include "../../Headers/GeneticAlgorithm/Population.h"
#include <algorithm>
#include <profileapi.h>

Population::Population(unsigned int populationSize,Graph* graph) {
    this->populationSize=populationSize;
    population.resize(populationSize);
    for(int i=0;i<populationSize;i++)
        population[i]=new Path(graph->getSize(),graph);

    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);
}

void Population::sortPopulation() {
    sort(population.begin(),population.end(),Path::pathComp);
}

Path* Population::get(int i) {
    return population[i];
}

Population::~Population() {
    for(Path* p : population)
        delete(p);
    population.clear();
}

void Population::makeNewPopulation() {
    for(int i=1;i<populationSize-1;i++){
        Path* mother = get(i);
        Path* father = get(randomGenerator()%populationSize);
        population.push_back(new Path(mother,father));
        population.back()->mutationScramble(0);
    }
    sortPopulation();
    while(population.size()>populationSize) {
        delete (population.back());
        population.pop_back();
    }

}

void Population::print() {
    for(Path* p : population) {
        cout<<p->getLength()<<" ";
        p->print();
    }
    cout<<"\n";
}

Path *Population::getBestAndClean() {
    Path* best = population.front();
    while(population.size()>1) {
        delete (population.back());
        population.pop_back();
    }
    population.pop_back();
    return best;
}
