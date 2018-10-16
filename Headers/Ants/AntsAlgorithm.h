#ifndef OK_TSP_ANTSALGORITHM_H
#define OK_TSP_ANTSALGORITHM_H

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


    virtual void printParameters() override;

    void printSolutionPath() override;

    virtual unsigned countCurrentSolutionLength() override;

    static minstd_rand0 randomGenerator;
    float alpha;
    float beta;
    float rho;
private:
    unsigned antsNum=20;
    int iterations=100;
    Ant* best;
};


#endif //OK_TSP_ANTSALGORITHM_H
