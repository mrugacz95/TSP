#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Population.h"

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
    std::cout << "last improved: " << improvedIteration << "\n";
    pathSolution = population.getBestAndClean();
}

std::string GeneticAlgorithm::getName() {
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
    std::cout << "iterations: " << iterations << " populationSize" << populationSize << "\n";
}
