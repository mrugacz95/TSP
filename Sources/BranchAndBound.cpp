#include "../Headers/BranchAndBound.h"

void BranchAndBound::solve() {
    bestSolutionLength=~0UL;
    visited.resize(graph->getSize(),false);
    tmpSolution.clear();
    for(int i=0;i<graph->getSize();i++)
        dfs(i,0);
}

void BranchAndBound::dfs(int a, unsigned currentLength) {

    tmpSolution.push_back(a);
    if(tmpSolution.size() == graph->getSize()) {
        currentLength += graph->distBetween(tmpSolution.front(), tmpSolution.back());
        if (currentLength < bestSolutionLength) {
            bestSolutionLength = currentLength;
            solution = tmpSolution;
        }
        tmpSolution.pop_back();
        return;
    }
    visited[a]=true;
    int currDist;
    for(int i=0;i<graph->getSize();i++) {
        if(visited[i]) continue;
        currDist = graph->distBetween(a, i);
        if(currentLength + currDist < bestSolutionLength)
            dfs(i, currentLength + currDist);

    }
    visited[a]=false;
    tmpSolution.pop_back();
    return;
}

string BranchAndBound::getName() {
    return "BranchAndBound";
}