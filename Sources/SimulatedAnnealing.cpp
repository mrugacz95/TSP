//
// Created by Mrugi on 2015-11-15.
//

#include <profileapi.h>
#include "../Headers/SimulatedAnnealing.h"

minstd_rand0 SimulatedAnnealing::randomGenerator;
void SimulatedAnnealing::solve() {
    solution.resize(graph->getSize());
    for(int i=0;i<graph->getSize();i++){
        solution[i]=i;
    }
    int previousLength,nextLength;
    unsigned it=iterations;
    double random,probability;
    for(int it=2;it<iterations+2;it++) {
        for (int i = 0; i < graph->getSize() - 1; i++) {
            solution[i], solution[randomGenerator()% graph->getSize()];
        }
        int swapA = randomGenerator() % graph->getSize(), swapB = randomGenerator() % graph->getSize();
        previousLength=countSolutionLength(solution);
        swap(solution[swapA], solution[swapB]);
        nextLength=countSolutionLength(solution);
        if (nextLength>= previousLength){
            random =  (double)SimulatedAnnealing::randomGenerator() / (double)numeric_limits<INT32>::max();
            probability=exp((double)(nextLength=previousLength)/temperature(it));
            if(random*exp(iterations)>probability)
                swap(solution[swapA], solution[swapB]);
        }
        int l=countCurrentSolutionLength();
        //cout<<l<<" ";
        //printSolutionPath();
    }

}

string SimulatedAnnealing::getName() {
    return "SimulatedAnnealing";
}

SimulatedAnnealing::SimulatedAnnealing() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);
}

double SimulatedAnnealing::temperature(int i) {
    return graph->getMaxLength()/log(i);
}
