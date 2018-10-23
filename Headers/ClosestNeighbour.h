#ifndef TSP_CLOSESTNEIGHBOUR_H
#define TSP_CLOSESTNEIGHBOUR_H


#include "Solver.h"

#include <vector>

class ClosestNeighbour : public Solver {
    public:
        void solve() override;

    std::string getName() override;

    private:
    std::vector<bool> visited;
        void dfs(int v);
};


#endif //TSP_CLOSESTNEIGHBOUR_H
