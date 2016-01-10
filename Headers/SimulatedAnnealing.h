//
// Created by Mrugi on 2015-11-15.
//

#ifndef OK_TSP_SIMULATEDANNEALING_H
#define OK_TSP_SIMULATEDANNEALING_H


#include <random>
#include "Solver.h"

class SimulatedAnnealing : public Solver {
public:
    void solve() override;
    virtual string getName() override;
    SimulatedAnnealing();
    SimulatedAnnealing(unsigned int iterations, float coolingFactor, float startTemperture);
    static minstd_rand0 randomGenerator;
    double temperatureFunc(int i);

    virtual void printParameters() override;

private:
    unsigned int iterations=200;
    float startTemperature;
    float temperature;
    float coolingFactor;
    int acc,noacc;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
