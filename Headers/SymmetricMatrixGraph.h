#ifndef TSP_SYMMETRICMATRIXGRAPH_H
#define TSP_SYMMETRICMATRIXGRAPH_H

#include "Graph.h"

#include <vector>

class SymmetricMatrixGraph : public Graph {
public:
    explicit SymmetricMatrixGraph(unsigned int size);

    unsigned int distanceBetween(unsigned int a, unsigned int b) override;

    std::string getName() override;

    unsigned int getNumberOfNodes() override;

    ~SymmetricMatrixGraph() override;

    explicit operator std::string() override;

    bool areConnected(unsigned a, unsigned b) override;

    int findClosestNeighbour(unsigned node) override;

    unsigned int getSize() override;

private:
    std::vector<unsigned int> distances;
    unsigned int size;

};


#endif //TSP_SYMMETRICMATRIXGRAPH_H
