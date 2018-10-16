#include <cmath>
#include "../../Headers/Ants/Ant.h"
#include "../../Headers/Ants/AntsAlgorithm.h"

Ant::Ant(float alpha, float beta, Graph *graph, EdgePheromone *edgePheromone) {
    this->graph = graph;
    visited.resize(graph->getSize());
    this->edgePheromone = edgePheromone;
    this->alpha = alpha;
    this->beta = beta;
    vertexProbability.resize(graph->getSize(), 0.f);
}

void Ant::walk() {
    path.clear();
    path.push_back(0);
    for (int i = 1; i < visited.size(); i++)
        visited[i] = false;
    visited[0] = true;
    for (int i = 0; i < graph->getSize() - 1; i++) {
        path.push_back(chooseVertex());
        visited[path.back()] = true;
    }
}

int Ant::chooseVertex() {
    double probabilitySum = 0;
    double distanceAttractiveness;
    double pheromoneAttractiveness;
    for (int i = 1; i < graph->getSize(); i++) {
        if (!visited[i]) {
            pheromoneAttractiveness = pow(edgePheromone->getPheromone(path.back(), i), alpha);
            distanceAttractiveness = pow(1.f / graph->distBetween(path.back(), i), beta);
            vertexProbability[i] = distanceAttractiveness * pheromoneAttractiveness;

            probabilitySum += vertexProbability[i];
            if (vertexProbability[i] > 0 && probabilitySum == 0)
                cout << "bulshit\n";
        } else
            vertexProbability[i] = 0;
    }
    if (probabilitySum == 0)
        cout << "ants wtf\n";
    for (int i = 1; i < graph->getSize(); i++) {
        vertexProbability[i] /= probabilitySum;
    }
    double random = (double) rand() / (double) RAND_MAX;
    probabilitySum = 0;

    for (int i = 0; i < vertexProbability.size(); i++) {
        probabilitySum += vertexProbability[i];
        if (probabilitySum >= random)
            return i;
    }
    return -1;
}

void Ant::updatePheromone(EdgePheromone *pheromoneDelta) {
    float pheromoneDisposed = 1.f / countLength();
    for (int i = 0; i < path.size() - 1; i++)
        pheromoneDelta->addPheromone(path[i], path[i + 1], pheromoneDisposed);
    pheromoneDelta->addPheromone(path.front(), path.back(), pheromoneDisposed);

}

unsigned int Ant::countLength() {
    length = 0;
    for (int i = 0; i < path.size() - 1; i++)
        length += graph->distBetween(path[i], path[i + 1]);
    length += graph->distBetween(path.front(), path.back());
    return length;
}

bool Ant::antComp(Ant *lhs, Ant *rhs) {
    return lhs->length < rhs->length;
}

unsigned int Ant::getLength() {
    return length;
}


void Ant::print() {
    for (int v :path)
        cout << v << ", ";
    cout << "\n";
}
