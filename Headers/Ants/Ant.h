#ifndef TSP_ANT_H
#define TSP_ANT_H

#include "Graph.h"
#include "EdgePheromone.h"

#include <vector>

class Ant {
public:
    Ant(float alpha, float beta, Graph *graph, EdgePheromone *edgePheromone);

    void walk();

    void updatePheromone(EdgePheromone *pheromoneDelta);

    unsigned int countLength();

    static bool antComp(Ant *lhs, Ant *rhs);

    unsigned int getLength();

    void print();

    std::vector<int> getPath();

private:
    unsigned int length;
    Graph *graph;
    std::vector<int> path;
    float alpha, beta;

    int chooseVertex();

    EdgePheromone *edgePheromone;
    std::vector<int> visited;
    std::vector<double> vertexProbability;
};

#endif //TSP_ANT_H
