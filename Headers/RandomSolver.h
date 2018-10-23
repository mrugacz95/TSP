#ifndef TSP_RANDOM_H
#define TSP_RANDOM_H


#include "Solver.h"

#include <algorithm>

class RandomSolver : public Solver {
public:
    explicit RandomSolver(unsigned int iterations);

    void solve() override;

    std::string getName() override;

private:
    unsigned int iterations;
};


#endif //TSP_RANDOM_H
