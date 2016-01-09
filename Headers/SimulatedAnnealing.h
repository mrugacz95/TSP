//
// Created by Mrugi on 2015-11-15.
//

#ifndef OK_TSP_SIMULATEDANNEALING_H
#define OK_TSP_SIMULATEDANNEALING_H


#include "Solver.h"

class SimulatedAnnealing : public Solver {
    void solve() override;

public:
    virtual string getName() override;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
