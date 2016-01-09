//
// Created by Mrugi on 2015-11-23.
//

#include "../../Headers/Ants/AntsAlgorithm.h"
#include "../../Headers/Ants/Ant.h"
minstd_rand0 AntsAlgorithm::randomGenerator;
float AntsAlgorithm::alpha=1.0f;
float AntsAlgorithm::beta=3.0f;
float AntsAlgorithm::rho=0.5f;
void AntsAlgorithm::solve() {
    vector<Ant*> ants;
    EdgePheromone edgePheromone(graph->getSize(), 1.f);
    EdgePheromone pheromoneDelta(graph->getSize(), 0.f);
    ants.resize(antsNum);
    for(int i=0;i<ants.size();i++)
        ants[i]=new Ant(AntsAlgorithm::alpha,AntsAlgorithm::beta,graph,&edgePheromone);
    for(int it=0;it<iterations;it++) {
        for (Ant *ant : ants)
            ant->walk();
        pheromoneDelta.reset(0.f);
        for (Ant *ant : ants)
            ant->updatePheromone(&pheromoneDelta);
        float newPheromoneValue;
        for (int i = 0; i < graph->getSize() - 1; i++) {
            newPheromoneValue =
                    (1 - rho) * edgePheromone.getPheromone(i, i + 1) + pheromoneDelta.getPheromone(i, i + 1);
            edgePheromone.setPheromone(i, i + 1, newPheromoneValue);
        }
    }
    for(int i=0;i< ants.size();i++)
        if(solutionLength>ants[i]->getLength()) solutionLength=ants[i]->getLength();

//    for(Ant* a : ants)
//        delete (a);
//    ants.clear();
}
string AntsAlgorithm::getName() {
    return "AntsAlgorithm";
}

AntsAlgorithm::AntsAlgorithm() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);

}

unsigned AntsAlgorithm::countCurrentSolutionLength() {
    return solutionLength;
}

void AntsAlgorithm::printSolution() {
    cout<<"mrowka\n";
}
