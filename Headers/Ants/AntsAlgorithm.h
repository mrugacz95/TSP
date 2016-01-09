//
// Created by Mrugi on 2015-11-23.
//

#ifndef OK_TSP_ANTSALGORITHM_H
#define OK_TSP_ANTSALGORITHM_H


#include <profileapi.h>
#include <random>
#include "../Solver.h"


using namespace std;
class AntsAlgorithm : public Solver {
public:
    AntsAlgorithm();
    void solve() override;
    string getName() override;

    virtual void printSolution() override;

    virtual unsigned countCurrentSolutionLength() override;

    static minstd_rand0 randomGenerator;
    static float alpha;
    static float beta;
    static float rho;
private:
    int antsNum=20;
    int iterations=100;
    unsigned int solutionLength;
};


#endif //OK_TSP_ANTSALGORITHM_H
