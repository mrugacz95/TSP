#ifndef OK_TSP_RANDOM_H
#define OK_TSP_RANDOM_H


#include "Solver.h"
#include <algorithm>

class RandomSolver : public Solver {
public:
    RandomSolver(unsigned int iterations);

    void solve() override;

    string getName() override;

private:
    unsigned int iterations;
};


#endif //OK_TSP_RANDOM_H
