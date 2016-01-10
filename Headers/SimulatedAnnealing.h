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
    static minstd_rand0 randomGenerator;
    double temperature(int i);
private:
    unsigned int iterations=200;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
