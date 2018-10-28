#include "Solver.h"

#include <limits>
#include <ctime>
#include <sstream>
#include <Solver.h>
#include <fstream>


void Solver::setGraph(Graph *graph) {
    this->graph = graph;
}

void Solver::printResults() {
    std::cout << getName() << " ";
    if (solvingTime > 0)
        std::cout << "Time (ms):" << solvingTime << " ";
    std::cout << "Graph size:" << graph->getNumberOfNodes() << " ";
    std::cout << " Length: " << countSolutionLength(solution) << "\n";
    printParameters();
    std::cout << "\t\t\t\t\t";
    getSolutionPath();
    std::cout << "\n";
}

unsigned Solver::countSolutionLength(std::vector<int> &vec) {
    unsigned int length = 0;
    for (int i = 0; i < vec.size() - 1; i++)
        length += graph->distanceBetween(vec[i], vec[i + 1]);
    length += graph->distanceBetween(vec.front(), vec.back());
    return length;
}

void Solver::start() {
    int counter = 0;
    clock_t begin = std::clock(), end;
    do {
        solve();
        counter++;
        end = clock();
    } while (end - begin < 60 && counter < 10);
    solvingTime = double(end - begin) / counter;
}

bool Solver::operator<(Solver &rhs) {
    return solvingTime < rhs.getSolvingTime();
}

double Solver::getSolvingTime() const {
    return solvingTime;
}

std::string Solver::getSolutionPath() {
    if (solution.empty()) {
        return "Not solved";
    }
    std::ostringstream result;
    for (int v : solution)
        result << v << " ";
    return result.str();
}

void Solver::saveToFile(std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::out);
    if (!file.good()) {
        std::cout << "Couldn't not open file";
        return;
    }
    file << getName() << "\n";
    file << getSolvingTime() << "\n";
    file << graph->getNumberOfNodes() << "\n";
    file << countSolutionLength(solution) << "\n";
    file << getSolutionPath() << "\n";

    file.close();
}