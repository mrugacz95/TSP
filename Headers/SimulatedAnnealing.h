#ifndef OK_TSP_SIMULATEDANNEALING_H
#define OK_TSP_SIMULATEDANNEALING_H


#include <random>

#include "Solver.h"

class SimulatedAnnealing : public Solver {
public:
    void solve() override;

    std::string getName() override;

    SimulatedAnnealing();

    SimulatedAnnealing(unsigned int iterations, float coolingFactor, float startTemperture);

    double temperatureFunc(int i);

    void printParameters() override;

private:
    unsigned int iterations = 1000;
    float startTemperature;
    float temperature;
    float coolingFactor;
    int acc, noacc;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
