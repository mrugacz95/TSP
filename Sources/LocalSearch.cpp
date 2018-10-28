#include "LocalSearch.h"
#include <random>
#include <algorithm>
#include <numeric>

int LocalSearch::delta(const std::vector<int> solution, const int i, const int j) {
    int a = (i - 1 + solution.size()) % solution.size();
    int b = i + 1;
    int c = j - 1;
    int d = (j + 1) % solution.size();
    int result = 0;
    result += graph->distanceBetween(solution[a], solution[i]);
    result += graph->distanceBetween(solution[i], solution[b]);
    result += graph->distanceBetween(solution[j], solution[d]);
    result -= graph->distanceBetween(solution[a], solution[j]);
    result -= graph->distanceBetween(solution[j], solution[b]);
    result -= graph->distanceBetween(solution[i], solution[d]);
    if (j-i != 1) {
        result += graph->distanceBetween(solution[c], solution[j]);
        result -= graph->distanceBetween(solution[c], solution[i]);
    }
    return -result;
}

void LocalSearch::solve() {
    graph->print();
    // prepare permutation
    solution.resize(graph->getNumberOfNodes());
    std::iota(solution.begin(), solution.end(), 0);
    // shuffle it
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(solution.begin(), solution.end(), g);
    // assess initial solution
    int bestScore = countSolutionLength(solution);
    int prevScore = bestScore + 1;
    // search until no prgress
    while(bestScore < prevScore) {
        prevScore = bestScore;
        bestScore += search(solution);
    }
}

