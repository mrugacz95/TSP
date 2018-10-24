#ifndef TSP_BRUTEFORCE_H
#define TSP_BRUTEFORCE_H


#include "Graph.h"
#include "Solver.h"

#include <algorithm>

class BruteForce : public Solver {
public:
    std::string getName() override;

    void printParameters() override;

    ~BruteForce() override = default;

protected:
    void solve() override;

};


#endif //TSP_BRUTEFORCE_H
