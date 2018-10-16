//
// Created by Mrugi on 2015-11-15.
//

#include "../../Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "../../Headers/GeneticAlgorithm/Path.h"
#include "../../Headers/GeneticAlgorithm/Population.h"

void GeneticAlgorithm::solve() {

    Population population(populationSize, mutationSize, graph);
    population.sortPopulation();
    unsigned int improved = population.get(0)->getLength();
    int it = iterations;
    bool wasImproved = false;
    int improvedIteration = 0;
    int iteration = 0;
    while (it--) {
        iteration++;
        population.makeNewPopulation();
        if (improved > population.get(0)->getLength() && it < 10) {
            it = 10;
            improved = population.get(0)->getLength();
            improvedIteration = iteration;
        }
    }
    cout << "last improved: " << improvedIteration << "\n";
    pathSolution = population.getBestAndClean();
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

GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize, float mutationSize, int iterations) {
    this->populationSize = populationSize;
    this->iterations = iterations;
    this->mutationSize = mutationSize;
}

GeneticAlgorithm::GeneticAlgorithm() {
    iterations = 5000;
    populationSize = 80;
    mutationSize = 0.09;
}

void GeneticAlgorithm::printParameters() {
    cout << "iterations: " << iterations << " populationSize" << populationSize << "\n";
}
