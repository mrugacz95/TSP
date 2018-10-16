#ifndef OK_TSP_MATRIXGRAPH_H
#define OK_TSP_MATRIXGRAPH_H


#include "Graph.h"
using namespace std;
class MatrixGraph : public Graph {
public:
    MatrixGraph(const MatrixGraph &graph);
    MatrixGraph(unsigned int size);
    MatrixGraph(unsigned int size, unsigned int maxLength);
    unsigned int distBetween(int a, int b) override;
    void print() override ;
    MatrixGraph &operator=(MatrixGraph &&other);
    unsigned int getSize() override;

    virtual unsigned getMaxLength() override;

private:
    vector<unsigned int> distances;
    unsigned int size;

};


#endif //OK_TSP_MATRIXGRAPH_H
