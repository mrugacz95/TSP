#ifndef OK_TSP_SIMULATEDANNEALING_H
#define OK_TSP_SIMULATEDANNEALING_H


#include <random>

#include "Solver.h"

class SimulatedAnnealing : public Solver {
public:
    void solve() override;

    std::string getName() override;

    SimulatedAnnealing();

    SimulatedAnnealing(int Lk, float coolingFactor);

    void temperatureDrop();

    void printParameters() override;

private:
    int search(std::vector<int>& solution);
    int delta(const std::vector<int> solution, int i, int j);
    void setTemperature(std::vector<int> solution);
    float startTemperature;
    float temperature;
    float coolingFactor;
    int Lk;
    int acc, noacc;
    std::vector<int> deltaCounter;
    std::vector<int> jumpCounter;
};


#endif //OK_TSP_SIMULATEDANNEALING_H
