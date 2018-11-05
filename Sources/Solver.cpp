#include "Solver.h"

#include <limits>
#include <ctime>
#include <numeric>
#include <sstream>
#include <Solver.h>
#include <fstream>


void Solver::setGraph(Graph *graph) {
    this->graph = graph;
}

void Solver::printResults() {
    std::cout << getName() << " ";
    if (meanSolvingTime > 0)
        std::cout << "Time (ms):" << meanSolvingTime << " ";
    std::cout << "Graph size:" << graph->getNumberOfNodes() << " ";
    std::cout << " Lenght: " << countSolutionLength(solution) << "\n";
    std::cout << "TIME: " << meanSolvingTime << "\n";
    std::cout << "SIZE: " << graph->getSize() << "\n";
    printParameters();
    std::cout << "\t\t\t\t\t";
    getSolutionPath();
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
    } while (solvingTimes.size() < 300);
    meanSolvingTime = accumulator / solvingTimes.size();
}

bool Solver::operator<(Solver &rhs) {
    return meanSolvingTime < rhs.getSolvingTime();
}

double Solver::getSolvingTime() const {
    return meanSolvingTime;
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
