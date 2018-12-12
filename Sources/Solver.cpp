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
    for (int i = 0; i < vec.size() - 1; i++) {
        length += graph->distanceBetween(vec[i], vec[i + 1]);
    }
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
    for (auto &t : solvingTimes)
        std::cout << t << " ";
    std::cout << std::endl;
}

void Solver::printScores() {
    std::cout << "BEST SCORES: ";
    for (auto &score : bestScores) {
        std::cout << score << " ";
    }
    std::cout << std::endl;
    std::cout << "FIRST SCORES: ";
    for (auto &score : firstScores) {
        std::cout << score << " ";
    }
    std::cout << std::endl;
}


int Solver::delta(const std::vector<int> solution, unsigned i, unsigned int j) {
    if (i > j) std::swap(i,j);
    deltaCounter++;
    int a = (i + solution.size() - 1) % solution.size();
    int b = (i + 1) % solution.size();
    int c = (j + solution.size() - 1) % solution.size();
    int d = (j + 1) % solution.size();
    int result = 0;

    result += graph->distanceBetween(solution[a], solution[i]);
    result += graph->distanceBetween(solution[i], solution[b]);
    if (abs((int) (i - j)) == 1) {
        result += graph->distanceBetween(solution[j], solution[d]);
        result -= graph->distanceBetween(solution[a], solution[j]);
        result -= graph->distanceBetween(solution[j], solution[i]);
        result -= graph->distanceBetween(solution[i], solution[d]);
    } else if (abs((int) (i - j)) == solution.size() - 1) {
        result += graph->distanceBetween(solution[c], solution[j]);
        result -= graph->distanceBetween(solution[c], solution[i]);
        result -= graph->distanceBetween(solution[i], solution[j]);
        result -= graph->distanceBetween(solution[j], solution[b]);
    } else {
        result += graph->distanceBetween(solution[c], solution[j]);
        result += graph->distanceBetween(solution[j], solution[d]);
        result -= graph->distanceBetween(solution[a], solution[j]);
        result -= graph->distanceBetween(solution[j], solution[b]);
        result -= graph->distanceBetween(solution[c], solution[i]);
        result -= graph->distanceBetween(solution[i], solution[d]);
    }
    return -result;
}
