//
// Created by Mrugi on 2015-11-09.
//

#ifndef OK_TSP_BRUTEFORCE_H
#define OK_TSP_BRUTEFORCE_H


#include "Graph.h"
#include "Solver.h"
#include <algorithm>

class BruteForce :public Solver {
    public:
        void solve() override;
        string getName() override;
};


#endif //OK_TSP_BRUTEFORCE_H
