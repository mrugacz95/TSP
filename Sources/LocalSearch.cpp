#include "LocalSearch.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <LocalSearch.h>


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
    jumpCounter.push_back(0);
    // prepare permutation
    solution.resize(graph->getNumberOfNodes());
    std::iota(solution.begin(), solution.end(), 0);
    // shuffle it
    std::shuffle(solution.begin(), solution.end(), engine);
    // assess initial solution
    int bestScore = countSolutionLength(solution);
    firstScores.push_back(bestScore);
    int prevScore;
    // search until no progress
    do {
        prevScore = bestScore;
        bestScore += search(solution);
        jumpCounter.back()++;
    } while (bestScore < prevScore);
    bestScores.push_back(bestScore);
}

void LocalSearch::printParameters() {
    std::cout << "DELTAS: ";
    for (auto &delta : deltaCounter) {
        std::cout << delta << " ";
    }
    std::cout << std::endl;
    std::cout << "JUMPS: ";
    for (auto &jump : jumpCounter) {
        std::cout << jump << " ";
    }
    std::cout << std::endl;
}

LocalSearch::LocalSearch(std::default_random_engine engine) {
    this->engine = engine;
}
