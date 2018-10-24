#include "ClosestNeighbour.h"

void ClosestNeighbour::solve() {
    visited.resize(graph->getNumberOfNodes(), false);
    solution.clear();
    dfs(0);
}

void ClosestNeighbour::dfs(int v) {
    solution.push_back(v);
    if (solution.size() == graph->getNumberOfNodes())
        return;
    visited[v] = true;
    int closest = -1, currDist, destiny;
    for (int i = 0; i < graph->getNumberOfNodes(); i++) {
        if (visited[i]) continue;
        if (v == i) continue;
        currDist = graph->distanceBetween(v, i);
        if (closest > currDist || closest == -1) {
            closest = currDist;
            destiny = i;
        }
    }
    dfs(destiny);
}

std::string ClosestNeighbour::getName() {
    return "ClosestNeighbour";
}

void ClosestNeighbour::printParameters() {

}
