#ifndef TSP_RANDOM_H
#define TSP_RANDOM_H


#include "Solver.h"

#include <algorithm>

class RandomSolver : public Solver {
public:
    RandomSolver(unsigned seed, unsigned maxTime);

    std::string getName() override;

    void printParameters() override;

    ~RandomSolver() override = default;
private:
    void solve() override;

    unsigned int maxTime;
    unsigned seed;
};


#endif //TSP_RANDOM_H
