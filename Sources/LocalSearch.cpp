#include "LocalSearch.h"
#include <random>
#include <algorithm>
#include <numeric>

int LocalSearch::delta(const std::vector<int> solution, const int i, const int j) {
    deltaCounter.back()++;
    int a = (i - 1 + solution.size()) % solution.size();
    int b = i + 1;
      int c = j - 1;
    int d = (j + 1) % solution.size();
    int result = 0;
    result += graph->distanceBetween(solution[a], solution[i]);
    result += graph->distanceBetween(solution[i], solution[b]);
    result += graph->distanceBetween(solution[c], solution[j]);
    result += graph->distanceBetween(solution[j], solution[d]);
    result -= graph->distanceBetween(solution[a], solution[j]);
    result -= graph->distanceBetween(solution[j], solution[b]);
    result -= graph->distanceBetween(solution[c], solution[i]);
    result -= graph->distanceBetween(solution[i], solution[d]);
    return -result;
}

void LocalSearch::solve() {
    deltaCounter.push_back(0);
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
    while(bestScore < prevScore) { // && deltaCounter.back() < 10000) {
        prevScore = bestScore;
        bestScore += search(solution);
    }
    bestScores.push_back(bestScore);
}

void LocalSearch::printParameters() {
    std::cout << "DELTAS: ";
    for (auto& delta : deltaCounter) {
      std::cout << delta << " ";
    }
    std::cout << std::endl;
    std::cout << "BEST SCORES: ";
    for (auto& score : bestScores) {
      std::cout << score << " ";
    }
    std::cout << std::endl;
}
