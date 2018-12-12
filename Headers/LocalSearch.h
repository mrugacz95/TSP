#ifndef TSP_LOCALSEARCH_H
#define TSP_LOCALSEARCH_H


#include "Solver.h"
#include <random>

class LocalSearch : public Solver {

public:
    explicit LocalSearch(std::default_random_engine engine);
    void solve() override;
    void printParameters() override;

protected:
    int delta(std::vector<int> solution, int i, int j);
    virtual int search(std::vector<int>& solution) = 0;

    std::default_random_engine engine;
};


#endif //TSP_LOCALSEARCH_H
