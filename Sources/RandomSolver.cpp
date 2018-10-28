#include "RandomSolver.h"
#include <algorithm>
#include <random>
#include <RandomSolver.h>

void RandomSolver::solve() {

    std::vector<int> tmpSolution(graph->getNumberOfNodes());
    for (int i = 0; i < tmpSolution.size(); i++)
        tmpSolution[i] = i;
    unsigned int bestLength = std::numeric_limits<unsigned>::max();
    std::vector<int> bestSolution;
    auto random_engine = std::default_random_engine(seed);
    std::clock_t start = clock();
    solution = tmpSolution;
    while (start + this->maxTime >= clock()) {
        std::shuffle(tmpSolution.begin(), tmpSolution.end(), random_engine);
        unsigned length = countSolutionLength(tmpSolution);
        if (bestLength > length) {
            bestLength = length;
            solution = tmpSolution;
        }
    }
}

std::string RandomSolver::getName() {
    return "Random Solver";
}

RandomSolver::RandomSolver(unsigned seed, unsigned maxTime) {
    this->seed = seed;
    this->maxTime = maxTime;
}
