#include "SimulatedAnnealing.h"

#include <random>
#include <algorithm>
#include <limits>

void SimulatedAnnealing::solve() {
    temperature = startTemperature;
    deltaCounter.push_back(0);
    jumpCounter.push_back(0);
    // prepare permutation
    solution.resize(graph->getNumberOfNodes());
    std::iota(solution.begin(), solution.end(), 0);
    // shuffle it
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(solution.begin(), solution.end(), g);
    // assess initial solution
    int bestScore = countSolutionLength(solution);
    firstScores.push_back(bestScore);
    int prevScore = bestScore + 1;
    int seriuosBestScore = bestScore;
    std::vector<int> seriousBestSolution(solution);
    int noProgress = 0;
    // search until no prgress
    while (noProgress < 100000) {
        bestScore += search(solution); 
        jumpCounter.back()++;
        if (bestScore < seriuosBestScore) {
            seriuosBestScore = bestScore;
            seriousBestSolution = solution;
            noProgress = 0;
        }
        noProgress++;
    }
    solution = seriousBestSolution;
    bestScores.push_back(seriuosBestScore);
}

int SimulatedAnnealing::search(std::vector<int>& solution) {
    for (int i=0; i < solution.size()-1; i++) {
        for (int j=i+1; j < solution.size(); j++) {
            if (deltaCounter.back() % Lk == Lk - 1) temperatureDrop();
            int d = delta(solution, i, j);
            if (d <= 0) {
                std::swap(solution[i], solution[j]);
                return d;
            }
            if (exp(-d/temperature) > rand() / (double) std::numeric_limits<int>::max()) {
                acc++;
                std::swap(solution[i], solution[j]);
                return d;
            } 
            noacc++;
        }
    }
    return 0;
}

int SimulatedAnnealing::delta(const std::vector<int> solution, const int i, const int j) {
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

std::string SimulatedAnnealing::getName() {
    return "SimulatedAnnealing";
}

SimulatedAnnealing::SimulatedAnnealing() {
}

void SimulatedAnnealing::temperatureDrop() {
    temperature *= coolingFactor;
}

SimulatedAnnealing::SimulatedAnnealing(int Lk, float coolingFactor, float startTemperature) {
    this->coolingFactor = coolingFactor;
    this->startTemperature = startTemperature;
    this->temperature = startTemperature;
    this->Lk = Lk;
}

void SimulatedAnnealing::printParameters() {
    std::cout << "Lk: " << Lk << " coolongFactor:" << coolingFactor << " startTemperature:"
              << startTemperature << " end temperature: " << temperature << " Accepted worse: " << acc << " Discarded worse: " << noacc << "\n";
}
