#ifndef OK_TSP_CLOSESTNEIGHBOUR_H
#define OK_TSP_CLOSESTNEIGHBOUR_H


#include "Solver.h"

class ClosestNeighbour : public Solver {
    public:
        void solve() override;
        string getName() override;

    private:
        vector<bool> visited;
        void dfs(int v);
};


#endif //OK_TSP_CLOSESTNEIGHBOUR_H
