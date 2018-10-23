#ifndef TSP_ANTSALGORITHM_H
#define TSP_ANTSALGORITHM_H

#include "Solver.h"

class Ant;
using namespace std;
class AntsAlgorithm : public Solver {
public:
    AntsAlgorithm();
    AntsAlgorithm(unsigned antsNum, unsigned iterations, float alpha, float beta, float rho);
    ~AntsAlgorithm();
    void solve() override;

    std::string getName() override;


    void printParameters() override;

    void printSolutionPath() override;

    unsigned countCurrentSolutionLength() override;

    float alpha;
    float beta;
    float rho;
private:
    unsigned antsNum=20;
    int iterations=100;
    Ant* best;
};


#endif //TSP_ANTSALGORITHM_H
