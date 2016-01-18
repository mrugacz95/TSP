//
// Created by Mrugi on 2015-11-23.
//

#include "../../Headers/Ants/AntsAlgorithm.h"
#include "../../Headers/Ants/Ant.h"
minstd_rand0 AntsAlgorithm::randomGenerator;
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
        double newPheromoneValue;
        for (int i = 0; i < graph->getSize() - 1; i++) {
            newPheromoneValue =
                    (1 - rho) * edgePheromone.getPheromone(i, i + 1) + pheromoneDelta.getPheromone(i, i + 1);
            edgePheromone.setPheromone(i, i + 1, newPheromoneValue);
        }
    }
    best=ants[0];
    for(int i=1;i< ants.size();i++)
        if (best->getLength() > ants[i]->getLength()) {
            best = ants[i];
        }


    for(Ant* a : ants)
        if(a!=best)
            delete (a);
}
string AntsAlgorithm::getName() {
    return "AntsAlgorithm";
}

AntsAlgorithm::AntsAlgorithm() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);

    AntsAlgorithm::alpha=1.0f;
    AntsAlgorithm::beta=3.0f;
    AntsAlgorithm::rho=0.6f;
}

unsigned AntsAlgorithm::countCurrentSolutionLength() {
    return best->getLength();
}

void AntsAlgorithm::printSolutionPath() {
    best->print();
}

AntsAlgorithm::~AntsAlgorithm() {
    delete(best);

}

AntsAlgorithm::AntsAlgorithm(unsigned antsNum, unsigned iterations, float alpha, float beta, float rho) {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);
    this->antsNum = antsNum;
    this->iterations = iterations;
    this -> alpha = alpha;
    this->beta = beta;
    this->rho = rho;
}

void AntsAlgorithm::printParameters() {
    cout<<"antsNum: "<<antsNum<<" iterations: "<<iterations<<" alpha:"<<alpha<<" beta: "<<beta<<" rho: "<<rho<<"\n";
}
