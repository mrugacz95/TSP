#ifndef OK_TSP_PATH_H
#define OK_TSP_PATH_H

using namespace std;

#include <vector>
#include <random>
#include "../MatrixGraph.h"

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
    minstd_rand0 randomGenerator;
    unsigned int length;
    Graph *graph;
    vector<int> path;
    float mutationSize;

    void countLength();
};

#endif //OK_TSP_PATH_H
