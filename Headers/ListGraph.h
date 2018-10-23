#ifndef OK_TSP_LISTGRAPH_H
#define OK_TSP_LISTGRAPH_H

#include "Graph.h"
#include "Edge.h"

#include <vector>

class ListGraph : public Graph {
public:
    explicit ListGraph(unsigned size);

    std::string getName() override;

    bool areConnected(unsigned a, unsigned b) override;

    unsigned distanceBetween(unsigned int a, unsigned int b) override;

    int findClosestNeighbour(unsigned node) override;

    ~ListGraph() override;

    explicit operator std::string() override;

private:
    std::vector<std::vector<Edge>> neighbourList;
};


#endif //OK_TSP_LISTGRAPH_H
