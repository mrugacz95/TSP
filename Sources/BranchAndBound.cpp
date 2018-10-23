#include "BranchAndBound.h"

void BranchAndBound::solve() {
    bestSolutionLength = std::numeric_limits<unsigned>::max();
    visited.resize(graph->getNumberOfNodes(), false);
    tmpSolution.clear();
    for (int i = 0; i < graph->getNumberOfNodes(); i++)
        dfs(i,0);
}

void BranchAndBound::dfs(int a, unsigned currentLength) {

    tmpSolution.push_back(a);
    if (tmpSolution.size() == graph->getNumberOfNodes()) {
        currentLength += graph->distanceBetween(tmpSolution.front(), tmpSolution.back());
        if (currentLength < bestSolutionLength) {
            bestSolutionLength = currentLength;
            solution = tmpSolution;
        }
        tmpSolution.pop_back();
        return;
    }
    visited[a]=true;
    int currDist;
    for (int i = 0; i < graph->getNumberOfNodes(); i++) {
        if(visited[i]) continue;
        currDist = graph->distanceBetween(a, i);
        if(currentLength + currDist < bestSolutionLength)
            dfs(i, currentLength + currDist);

    }
    visited[a]=false;
    tmpSolution.pop_back();
}

std::string BranchAndBound::getName() {
    return "BranchAndBound";
}