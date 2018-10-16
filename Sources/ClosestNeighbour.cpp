#include "../Headers/ClosestNeighbour.h"

void ClosestNeighbour::solve() {
    visited.resize(graph->getSize(), false);
    for(auto b : visited)
        b = false;
    solution.clear();
    dfs(0);
}

void ClosestNeighbour::dfs(int v) {
    solution.push_back(v);
    if(solution.size() == graph->getSize())
        return;
    visited[v]=true;
    int closest=-1,currDist,destiny;
    for(int i=0;i<graph->getSize();i++) {
        if(visited[i]) continue;
        if(v ==i) continue;
        currDist = graph->distBetween(v, i);
        if (closest > currDist || closest == -1 ){
            closest=currDist;
            destiny=i;
        }
    }
    dfs(destiny);
    return;
}

string ClosestNeighbour::getName() {
    return "ClosestNeighbour";
}
