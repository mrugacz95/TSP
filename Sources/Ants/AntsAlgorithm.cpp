#include "Ants/AntsAlgorithm.h"
#include "Ants/Ant.h"

void AntsAlgorithm::solve() {
    vector<Ant *> ants;
    EdgePheromone edgePheromone(graph->getNumberOfNodes(), 1.f);
    EdgePheromone pheromoneDelta(graph->getNumberOfNodes(), 0.f);
    ants.resize(antsNum);
    for (int i = 0; i < ants.size(); i++)
        ants[i] = new Ant(AntsAlgorithm::alpha, AntsAlgorithm::beta, graph, &edgePheromone);
    for (int it = 0; it < iterations; it++) {
        for (Ant *ant : ants)
            ant->walk();
        pheromoneDelta.reset(0.f);
        for (Ant *ant : ants)
            ant->updatePheromone(&pheromoneDelta);
        double newPheromoneValue;
        for (int i = 0; i < graph->getNumberOfNodes() - 1; i++) {
            newPheromoneValue =
                    (1 - rho) * edgePheromone.getPheromone(i, i + 1) + pheromoneDelta.getPheromone(i, i + 1);
            edgePheromone.setPheromone(i, i + 1, newPheromoneValue);
        }
    }
    best = ants[0];
    for (int i = 1; i < ants.size(); i++)
        if (best->getLength() > ants[i]->getLength()) {
            best = ants[i];
        }


    for (Ant *a : ants)
        if (a != best)
            delete (a);
    solution = best->getPath();
}

string AntsAlgorithm::getName() {
    return "AntsAlgorithm";
}

AntsAlgorithm::AntsAlgorithm() {
    AntsAlgorithm::alpha = 1.0f;
    AntsAlgorithm::beta = 3.0f;
    AntsAlgorithm::rho = 0.6f;
}

AntsAlgorithm::~AntsAlgorithm() {
    delete (best);

}

AntsAlgorithm::AntsAlgorithm(unsigned antsNum, unsigned iterations, float alpha, float beta, float rho) {
    this->antsNum = antsNum;
    this->iterations = iterations;
    this->alpha = alpha;
    this->beta = beta;
    this->rho = rho;
}

void AntsAlgorithm::printParameters() {
    std::cout << "antsNum: " << antsNum << " iterations: " << iterations << " alpha:" << alpha << " beta: " << beta
              << " rho: " << rho << "\n";
}
