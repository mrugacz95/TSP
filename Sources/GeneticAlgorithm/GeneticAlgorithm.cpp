//
// Created by Mrugi on 2015-11-15.
//

#include "../../Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "../../Headers/GeneticAlgorithm/Path.h"
#include "../../Headers/GeneticAlgorithm/Population.h"

void GeneticAlgorithm::solve() {

    Population population(50,graph);
    population.sortPopulation();
    int best = population.get(0)->getLength();
    int improved;
    while(iterations--){

        population.makeNewPopulation();
        improved=population.get(0)->getLength();
    }
    pathSolution=population.getBestAndClean();
}
string GeneticAlgorithm::getName() {
    return "GeneticAlgorithm";
}



Path GeneticAlgorithm::crossoverOrder(Path mother, Path father) {

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
