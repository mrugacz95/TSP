#ifndef OK_TSP_LISTGRAPH_H
#define OK_TSP_LISTGRAPH_H


#include "Graph.h"
#include "Edge.h"

//TODO zrezygnowac albo poprawic
class ListGraph : public Graph {
public:
    ListGraph();

    void print() override;

    bool areConnected(int a, int b);

    unsigned int distBetween(int a, int b) override;

    std::vector<Edge> getVertNeighbours(int a);

    int findClosestNeighbour(int v);

    ~ListGraph();

private:
    std::vector<std::vector<Edge> > neighbourList;
};


#endif //OK_TSP_LISTGRAPH_H
