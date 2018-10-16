#ifndef OK_TSP_ANT_H
#define OK_TSP_ANT_H

#include "../Graph.h"
#include "EdgePheromone.h"
#include <vector>
using namespace std;
class Ant{
public:
    Ant(float alpha, float beta, Graph *graph, EdgePheromone *edgePheromone);
    void walk();

    void updatePheromone(EdgePheromone *pheromoneDelta);
    unsigned int countLength();
    static bool antComp(Ant* lhs, Ant* rhs);
    unsigned int getLength();
    void print();

private:
    unsigned int length;
    Graph* graph;
    vector<int> path;
    float alpha,beta;
    int chooseVertex();
    EdgePheromone* edgePheromone;
    vector<int> visited;
    vector<double> vertexProbability;
};
#endif //OK_TSP_ANT_H
