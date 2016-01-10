//
// Created by Mrugi on 2015-11-23.
//

#ifndef OK_TSP_ANTSALGORITHM_H
#define OK_TSP_ANTSALGORITHM_H


#include <profileapi.h>
#include <random>
#include "../Solver.h"

class Ant;
using namespace std;
class AntsAlgorithm : public Solver {
public:
    AntsAlgorithm();
    AntsAlgorithm(unsigned antsNum, unsigned iterations, float alpha, float beta, float rho);
    ~AntsAlgorithm();
    void solve() override;
    string getName() override;

    void printSolutionPath();

    virtual unsigned countCurrentSolutionLength() override;

    static minstd_rand0 randomGenerator;
    static float alpha;
    static float beta;
    static float rho;
private:
    unsigned antsNum=20;
    int iterations=100;
    Ant* best;
};


#endif //OK_TSP_ANTSALGORITHM_H
