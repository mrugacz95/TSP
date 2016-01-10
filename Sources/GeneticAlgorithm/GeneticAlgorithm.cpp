//
// Created by Mrugi on 2015-11-15.
//

#include "../../Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "../../Headers/GeneticAlgorithm/Path.h"
#include "../../Headers/GeneticAlgorithm/Population.h"

void GeneticAlgorithm::solve() {

    Population population(populationSize,graph);
    population.sortPopulation();
    unsigned int improved=population.get(0)->getLength();
    while(iterations--){

        population.makeNewPopulation();
        if(improved>population.get(0)->getLength() && iterations<10) iterations=10;
        improved=population.get(0)->getLength();
    }
    pathSolution=population.getBestAndClean();
}
string GeneticAlgorithm::getName() {
    return "GeneticAlgorithm";
}


unsigned GeneticAlgorithm::countCurrentSolutionLength() {
    return pathSolution->getLength();
}

GeneticAlgorithm::~GeneticAlgorithm() {
    delete (pathSolution);
}

void GeneticAlgorithm::printSolutionPath() {
    pathSolution->print();
}
GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize, int iterations) {
    this->populationSize = populationSize;
    this->iterations = iterations;
}
