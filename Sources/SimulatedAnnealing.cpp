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
    double random,probability;
    int accepted=0,noacc=0;
    temperature = startTemperature;
    for(int it=2;it<iterations+2;it++) {
        for (int i = 0; i < graph->getSize() - 1; i++) {
            solution[i], solution[randomGenerator()% graph->getSize()];
        }
        int swapA = randomGenerator() % graph->getSize(), swapB = randomGenerator() % graph->getSize();
        previousLength=countSolutionLength(solution);
        swap(solution[swapA], solution[swapB]);
        nextLength=countSolutionLength(solution);
        if (nextLength>previousLength){
            random =  (double)SimulatedAnnealing::randomGenerator() / (double)numeric_limits<INT32>::max();
            double delta = (previousLength-nextLength);
            double power=(previousLength-nextLength)/ temperature;
            probability=exp((previousLength-nextLength)/ temperature);
            if(random>probability) {//no accepted
                swap(solution[swapA], solution[swapB]);
                noacc++;
            }
            else{
                accepted++;
                cout<<"--------------- from"<<previousLength<<" to:"<<nextLength<<"\n";
            }
        }
        if(temperature * coolingFactor<0)
            cout<<"wtf\n";
        temperature*=coolingFactor;
        int l=countCurrentSolutionLength();
        cout<<l<<" ";
        printSolutionPath();
    }
    cout<<"acc"<<accepted<<" n:"<<noacc;

}

string SimulatedAnnealing::getName() {
    return "SimulatedAnnealing";
}

SimulatedAnnealing::SimulatedAnnealing() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);
}

double SimulatedAnnealing::temperatureFunc(int i) {
    return graph->getMaxLength()/log(i);
}

SimulatedAnnealing::SimulatedAnnealing(unsigned int iterations, float coolingFactor, float startTemperture) {
    this->iterations=iterations;
    this->coolingFactor = coolingFactor;
    this->startTemperature = startTemperture;

}

void SimulatedAnnealing::printParameters() {
    cout<<"iterations: "<<iterations<<" coolongFactor"<<coolingFactor<<" startTemperature"<<startTemperature<<"\n";
}
