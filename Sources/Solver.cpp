#include "Solver.h"

#include <limits>
#include <ctime>
#include <numeric>

void Solver::setGraph(Graph *graph) {
    this->graph = graph;
}

void Solver::printResults() {
    std::cout << getName() << " ";
    if (meanSolvingTime > 0)
        std::cout << meanSolvingTime << " ";
    std::cout << "Graph size:" << graph->getNumberOfNodes() << " ";
    std::cout << " Lenght: " << countSolutionLength(solution) << "\n";
    std::cout << "TIME: " << meanSolvingTime << "\n";
    std::cout << "SIZE: " << graph->size << "\n";
    printParameters();
    printSolutionPath();
    printTimes();
    printScores();
}

unsigned Solver::countSolutionLength(std::vector<int> &vec) {
    unsigned int length = 0;
    for (int i = 0; i < vec.size() - 1; i++)
        length += graph->distanceBetween(vec[i], vec[i + 1]);
    length += graph->distanceBetween(vec.back(), vec.front());
    return length;
}

void Solver::start() {
    double accumulator = 0.0;
    clock_t begin, end;
    do {
        begin = std::clock();
        solve();
        end = clock();
        solvingTimes.push_back(double(end - begin) / CLOCKS_PER_SEC);
        accumulator += solvingTimes.back();
    //} while (accumulator < 60 && solvingTimes.size() < 10);
    } while (solvingTimes.size() < 10);
    meanSolvingTime = accumulator / solvingTimes.size();
}

bool Solver::operator<(Solver &rhs) {
    return meanSolvingTime < rhs.getSolvingTime();
}

double Solver::getSolvingTime() const {
    return meanSolvingTime;
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

void Solver::printTimes() {
    std::cout << "TIMES: ";
    for (auto& t : solvingTimes)
        std::cout << t << " ";
    std::cout << std::endl;
}

void Solver::printScores() {
    std::cout << "BEST SCORES: ";
    for (auto& score : bestScores) {
      std::cout << score << " ";
    }
    std::cout << std::endl;
    std::cout << "FIRST SCORES: ";
    for (auto& score : firstScores) {
      std::cout << score << " ";
    }
    std::cout << std::endl;
}
