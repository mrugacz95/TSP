
#include <RandomSolver.h>

RandomSolver::RandomSolver(unsigned int iterations) {
    this->iterations = iterations;
}

void RandomSolver::solve() {

    vector<int> tmpSolution(graph->getSize());
    for (int i = 0; i < tmpSolution.size(); i++)
        tmpSolution[i] = i;
    unsigned int bestLength = std::numeric_limits<unsigned>::max();
    vector<int> bestSolution;
    for (int iter = 0; iter < iterations; iter++) {
        // shuffle
        for (unsigned long i = tmpSolution.size() - 1; i > 1; i--) {
            swap(tmpSolution[i], tmpSolution[rand() % i]);
        }
        unsigned length = countSolutionLength(tmpSolution);
        if (bestLength > length) {
            bestLength = length;
            solution = tmpSolution;
        }
    }
}

string RandomSolver::getName() {
    return "Random Solver";
}
