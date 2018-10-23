#include "Solver.h"

#include <limits>
#include <ctime>

void Solver::setGraph(Graph *graph) {
    this->graph = graph;
}

void Solver::printResults() {
    std::cout << getName() << " ";
    if (timeCounted)
        std::cout << solvingTime << " ";
    std::cout << "Graph size:" << graph->getNumberOfNodes() << " ";
    std::cout << " Lenght: " << countCurrentSolutionLength() << "\n";
    printParameters();
    std::cout << "\t\t\t\t\t";
    printSolutionPath();
    std::cout << "\n";
}

unsigned Solver::countSolutionLength(std::vector<int> &vec) {
    unsigned int length = 0;
    for (int i = 0; i < vec.size() - 1; i++)
        length += graph->distanceBetween(vec[i], vec[i + 1]);
    length += graph->distanceBetween(vec.front(), vec.back());
    return length;
}

void Solver::solveWithTimeCounting() {
    timeCounted = true;
    int counter = 0;
    clock_t begin = std::clock(), end;
    do {
        solve();
        counter++;
        end = clock();
    } while (end - begin < 60 && counter < 10);
    solvingTime = double(end - begin) / counter;
}

void Solver::simpleSolve() {
    timeCounted = false;
    solve();
}

bool Solver::operator<(Solver &rhs) {
    return solvingTime < rhs.getSolvingTime();
}

double Solver::getSolvingTime() const {
    return solvingTime;
}

unsigned Solver::countCurrentSolutionLength() {
    if (solution.empty())
        return std::numeric_limits<unsigned int>::max();

    return countSolutionLength(solution);
}


Solver::~Solver() {
    delete graph;
}

void Solver::printSolutionPath() {
    if (solution.empty()) {
        std::cout << "Not solved";
        return;
    }
    for (int v : solution)
        std::cout << v << ", ";
    std::cout << "\n";
}

void Solver::printParameters() {

}
