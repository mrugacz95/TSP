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
    // calculate initial temperature
    setTemperature(solution);
    // search until no prgress
    while (noProgress < 10*Lk && temperature > 0.0001) {
        int last_best = bestScore;
        bestScore += search(solution); 
        if (bestScore >= last_best) noProgress++;
        jumpCounter.back()++;
        if (bestScore < seriuosBestScore) {
            seriuosBestScore = bestScore;
            seriousBestSolution = solution;
            noProgress = 0;
        }
    }
    solution = seriousBestSolution;
    bestScores.push_back(seriuosBestScore);
}

void SimulatedAnnealing::setTemperature(std::vector<int> solution) {
    int K = 100;
    int size = K*(solution.size()-1)*(solution.size()-1)/2;
    int dmin = 0;
    int sum = 0;
    int it = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> diff;
    for (int k=0; k < K; k++) {
        for (int i=0; i < solution.size()-1; i++) {
            for (int j=i+1; j < solution.size(); j++) {
                int d = delta(solution, i, j);
                if (d > 0) {
                    //std::cout << "DELTA: " << d << std::endl;
                    sum += d;
                    it++;
                }
                diff.push_back(d);
            }
        }
        std::shuffle(solution.begin(), solution.end(), g);
    }
    float davg = sum / float(it);
    float ratio = it / float(size);
    //std::cout << "RAT: " << ratio <<std::endl;
    //std::cout << "DAVG: " << davg <<std::endl;
    //std::cout << "TEMP: " << -davg / log((ratio-0.05)/ratio) <<std::endl;
    this->temperature = -davg / log((ratio-0.05)/ratio);
    this->startTemperature = this->temperature;
}

int SimulatedAnnealing::search(std::vector<int>& solution) {
    for (int i=0; i < solution.size()-1; i++) {
        for (int j=i+1; j < solution.size(); j++) {
            if (deltaCounter.back() % Lk == Lk - 1) temperatureDrop();
            int d = delta(solution, i, j);
            if (d < 0) {
                std::swap(solution[i], solution[j]);
                return d;
            }
            else if (d > 0){
                if (exp(-d/temperature) > rand() / float(RAND_MAX)) {
                    acc++;
                    std::swap(solution[i], solution[j]);
                    return d;
                } 
                noacc++;
            }
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
    if (abs(i-j) == 1) {
      result += graph->distanceBetween(solution[j], solution[d]);
      result -= graph->distanceBetween(solution[a], solution[j]);
      result -= graph->distanceBetween(solution[j], solution[i]);
      result -= graph->distanceBetween(solution[i], solution[d]);
    }
    else if (abs(i-j) == solution.size()-1) {
      result += graph->distanceBetween(solution[c], solution[j]);
      result -= graph->distanceBetween(solution[c], solution[i]);
      result -= graph->distanceBetween(solution[i], solution[j]);
      result -= graph->distanceBetween(solution[j], solution[b]);
    }
    else {
      result += graph->distanceBetween(solution[c], solution[j]);
      result += graph->distanceBetween(solution[j], solution[d]);
      result -= graph->distanceBetween(solution[a], solution[j]);
      result -= graph->distanceBetween(solution[j], solution[b]);
      result -= graph->distanceBetween(solution[c], solution[i]);
      result -= graph->distanceBetween(solution[i], solution[d]);
    }
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

SimulatedAnnealing::SimulatedAnnealing(int Lk, float coolingFactor) {
    this->coolingFactor = coolingFactor;
    this->Lk = Lk;
}

void SimulatedAnnealing::printParameters() {
    std::cout << "Lk: " << Lk << " coolongFactor:" << coolingFactor << " startTemperature:"
              << startTemperature << " end temperature: " << temperature << " Accepted worse: " << acc << " Discarded worse: " << noacc << "\n";
}
