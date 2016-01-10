#include <iostream>
#include "Headers/MatrixGraph.h"
#include "Headers/BruteForce.h"
#include "Headers/ClosestNeighbour.h"
#include "Headers/Random.h"
#include "Headers/ImprovedBruteForce.h"
#include "Headers/Utilities.h"
#include "Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "Headers/Ants/AntsAlgorithm.h"
#include "Headers/SimulatedAnnealing.h"

using namespace std;
void fun(){
    cout<<"123\n";
}
int main() {
    srand((unsigned)time(NULL));
    double start,finish;
    MatrixGraph graph(20, 1000);
    vector<Solver *> solversList;
    //solversList.push_back(new BruteForce());
    solversList.push_back(new Random());
    //solversList.push_back(new ImprovedBruteForce());
    solversList.push_back(new ClosestNeighbour());
    solversList.push_back(new AntsAlgorithm());
    solversList.push_back(new GeneticAlgorithm(75,150));
    solversList.push_back(new GeneticAlgorithm());
    solversList.push_back(new SimulatedAnnealing(100,.9f,10000));

    for (Solver *s : solversList)
    s->setGraph(&graph);
    vector<thread> threads;
    start=clock();
    for (Solver *s : solversList) {
        threads.push_back(s->solveAsync());
    }
    for(thread& t : threads){
        t.join();
    }
    finish=clock();
    for (Solver *s : solversList) {

        s->countCurrentSolutionLength();
    }
    sort(solversList.begin(),solversList.end(), Utilities::compLengthAndTime );
    for(auto s : solversList)
        s->printSolution();
    cout<<"\t\t\t\t\tMulti threading Executed in time"<<((double)(finish-start))/CLOCKS_PER_SEC;
    return 0;
}