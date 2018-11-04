#include "ClosestNeighbour.h"

void ClosestNeighbour::solve() {
    visited.resize(graph->getNumberOfNodes());
    std::fill(visited.begin(), visited.end(), false);
    solution.clear();
    dfs(rand() % graph->getNumberOfNodes());
}

void ClosestNeighbour::dfs(int v) {
    solution.push_back(v);
    if (solution.size() == graph->getNumberOfNodes()) {
        bestScores.push_back(countSolutionLength(solution));
        return;
    }
    visited[v] = true;
    int closest = std::numeric_limits<int>::max(), currDist, destiny;
    for (int i = 0; i < graph->getNumberOfNodes(); i++) {
        if (visited[i]) continue;
        if (v == i) continue;
        currDist = graph->distanceBetween(v, i);
        if (closest > currDist) {
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
