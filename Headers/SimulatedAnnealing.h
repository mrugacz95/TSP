#ifndef OK_TSP_SIMULATEDANNEALING_H
#define OK_TSP_SIMULATEDANNEALING_H


#include <random>

#include "Solver.h"

class SimulatedAnnealing : public Solver {
public:
    void solve() override;

    std::string getName() override;

    SimulatedAnnealing();

    SimulatedAnnealing(int Lk, float coolingFactor, float startTemperature);

    void temperatureDrop();

    void printParameters() override;

private:
    int search(std::vector<int>& solution);
    int delta(const std::vector<int> solution, const int i, const int j);
    float startTemperature;
    float temperature;
    float coolingFactor;
    int Lk;
    int acc, noacc;
    std::vector<int> deltaCounter;
    std::vector<int> jumpCounter;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
