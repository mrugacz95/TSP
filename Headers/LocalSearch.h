#ifndef TSP_LOCALSEARCH_H
#define TSP_LOCALSEARCH_H


#include "Solver.h"

class LocalSearch : public Solver {

public: 
    void solve() override;
    void printParameters() override;

protected:
    std::vector<int> deltaCounter;
    std::vector<int> jumpCounter;
    int delta(const std::vector<int> solution, const int i, const int j);
    virtual int search(std::vector<int>& solution) = 0;
};


#endif //TSP_LOCALSEARCH_H
