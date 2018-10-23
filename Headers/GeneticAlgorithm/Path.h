#ifndef TSP_PATH_H
#define TSP_PATH_H

#include "SymmetricMatrixGraph.h"

#include <vector>
#include <random>

class Path {
public:
    Path(unsigned int size, float mutationSize, Graph *graph);

    Path(Path *mother, Path *father);

    Path(Path *source, Graph *graph);

    bool contains(int vertex);

    unsigned int getLength();

    bool operator<(Path &&path);

    void mutationInversion();

    void mutationScramble();

    void print();

    static bool pathComp(Path *lhs, Path *rhs);

private:
    unsigned int length;
    Graph *graph;
    std::vector<int> path;
    float mutationSize;

    void countLength();
};

#endif //TSP_PATH_H
