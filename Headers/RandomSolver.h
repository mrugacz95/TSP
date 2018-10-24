#ifndef TSP_RANDOM_H
#define TSP_RANDOM_H


#include "Solver.h"

#include <algorithm>

class RandomSolver : public Solver {
public:
    explicit RandomSolver(unsigned int iterations);

    std::string getName() override;

    void printParameters() override;


    ~RandomSolver() override = default;
private:
    void solve() override;
    unsigned int iterations;
};


#endif //TSP_RANDOM_H
