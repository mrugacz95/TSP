#ifndef TSP_BRUTEFORCE_H
#define TSP_BRUTEFORCE_H


#include "Graph.h"
#include "Solver.h"

#include <algorithm>

class BruteForce :public Solver {
    public:
        void solve() override;

    std::string getName() override;
};


#endif //TSP_BRUTEFORCE_H
