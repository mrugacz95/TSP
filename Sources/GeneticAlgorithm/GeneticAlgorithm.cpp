#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Population.h"

void GeneticAlgorithm::solve() {

    Population population(populationSize, mutationSize, graph);
    population.sortPopulation();
    unsigned int improved = population.get(0)->getLength();
    int it = iterations;
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
    solution = pathSolution->getPath();
}

std::string GeneticAlgorithm::getName() {
    return "GeneticAlgorithm";
}

GeneticAlgorithm::~GeneticAlgorithm() {
    delete (pathSolution);
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
