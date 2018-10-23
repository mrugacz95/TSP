#ifndef TSP_ASYMMETRICMATRIXGRAPH_H
#define TSP_ASYMMETRICMATRIXGRAPH_H


#include "Graph.h"

#include <vector>

class AsymmetricMatrixGraph : public Graph {
public:
    explicit AsymmetricMatrixGraph(unsigned size);

    explicit AsymmetricMatrixGraph(std::string filename);

    std::string getName() override;

    unsigned int getNumberOfNodes() override;

    unsigned int distanceBetween(unsigned int a, unsigned int b) override;

    bool areConnected(unsigned a, unsigned b) override;

    explicit operator std::string() override;

    int findClosestNeighbour(unsigned node) override;

private:
    std::vector<std::vector<unsigned>> matrix;
};


#endif //TSP_ASYMMETRICMATRIXGRAPH_H
