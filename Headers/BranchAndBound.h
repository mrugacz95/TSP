#ifndef TSP_IMPROVEDBRUTEFORCE_H
#define TSP_IMPROVEDBRUTEFORCE_H


#include "Solver.h"

class BranchAndBound : public Solver {
    public:
    std::string getName() override;

    private:
        void solve() override;

    std::vector<bool> visited;
    std::vector<int> tmpSolution;
        unsigned bestSolutionLength;
        void dfs(int a, unsigned currentLength);
};


#endif //TSP_IMPROVEDBRUTEFORCE_H
