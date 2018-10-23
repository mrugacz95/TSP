#include "SimulatedAnnealing.h"

#include <limits>

void SimulatedAnnealing::solve() {
    solution.resize(graph->getNumberOfNodes());
    for (int i = 0; i < graph->getNumberOfNodes(); i++) {
        solution[i] = i;
    }
    int previousLength, nextLength;
    double random, probability;
    acc = 0, noacc = 0;
    temperature = startTemperature;
    for (int it = 2; it < iterations + 2; it++) {
        for (int i = 0; i < graph->getNumberOfNodes() - 1; i++) {
            solution[i], solution[rand() % graph->getNumberOfNodes()];
        }
        int swapA = rand() % graph->getNumberOfNodes(), swapB = rand() % graph->getNumberOfNodes();
        previousLength = countSolutionLength(solution);
        std::swap(solution[swapA], solution[swapB]);
        nextLength = countSolutionLength(solution);
        if (nextLength > previousLength) {
            random = (double) rand() / (double) std::numeric_limits<int>::max();
            probability = exp((previousLength - nextLength) / temperature);
            if (random > probability) {//no accepted
                std::swap(solution[swapA], solution[swapB]);
                noacc++;
            } else {
                acc++;
            }
        }
        temperature *= coolingFactor;
    }

}

std::string SimulatedAnnealing::getName() {
    return "SimulatedAnnealing";
}

SimulatedAnnealing::SimulatedAnnealing() {
}

double SimulatedAnnealing::temperatureFunc(int i) {
    return graph->MAX_LENGTH / log(i);
}

SimulatedAnnealing::SimulatedAnnealing(unsigned int iterations, float coolingFactor, float startTemperture) {
    this->iterations = iterations;
    this->coolingFactor = coolingFactor;
    this->startTemperature = startTemperture;

}

void SimulatedAnnealing::printParameters() {
    std::cout << "iterations: " << iterations << " coolongFactor:" << coolingFactor << " startTemperature:"
              << startTemperature << " Accepted worse: " << acc << " Discarded worse: " << noacc << "\n";
}
