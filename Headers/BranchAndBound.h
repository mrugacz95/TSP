//
// Created by Mrugi on 2015-11-14.
//

#ifndef OK_TSP_IMPROVEDBRUTEFORCE_H
#define OK_TSP_IMPROVEDBRUTEFORCE_H


#include "Solver.h"

class BranchAndBound : public Solver {
    public:
        string getName() override;

    private:
        void solve() override;
        vector<bool> visited;
        vector<int> tmpSolution;
        unsigned bestSolutionLength;
        void dfs(int a, unsigned currentLength);
};


#endif //OK_TSP_IMPROVEDBRUTEFORCE_H
