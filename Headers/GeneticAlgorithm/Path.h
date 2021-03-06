//
// Created by Mrugi on 2016-01-06.
//

#ifndef OK_TSP_PATH_H
#define OK_TSP_PATH_H

using namespace std;
#include <vector>
#include <random>
#include "../MatrixGraph.h"

class Path{
    public:
        Path(unsigned int size, Graph* graph);
        Path(Path* mother, Path* father);
        Path(Path* source,Graph*graph);
        bool contains(int vertex);
        unsigned int getLength();
        bool operator<(Path&& path);
        void mutationInversion(int mutationSize);
        void mutationScramble(float mutationSize);
        void print();
        static bool pathComp(Path* lhs,Path* rhs);
    private:
        minstd_rand0 randomGenerator;
        unsigned int length;
        Graph* graph;
        vector<int> path;
        void countLength();
    };
#endif //OK_TSP_PATH_H
