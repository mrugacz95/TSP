#include <iostream>
#include "Headers/MatrixGraph.h"
#include "Headers/BruteForce.h"
#include "Headers/ClosestNeighbour.h"
#include "Headers/Random.h"
#include "Headers/Utilities.h"
#include "Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "Headers/Ants/AntsAlgorithm.h"
#include "Headers/SimulatedAnnealing.h"
#include "Headers/BranchAndBound.h"

using namespace std;
void fun(){
    cout<<"123\n";
}
int main() {
    int choose;
    int algorithm;
    int nodes;
    srand((unsigned)time(NULL));
    vector<MatrixGraph*> graphs;
    vector<Solver *> solversList;
    cout<<"Add graphs (-1 to stop)\n";
    cin>>nodes;
    while(nodes>0){
        graphs.push_back(new MatrixGraph(nodes,1000));
        cout<<"Added graph with "<<nodes<<" nodes\n";
        cin>>nodes;
    }
    do {
        cout <<"Choose algorithm\n 0-BruteForce\n1-Random\n2-Branch and Bound\n3-Closest Neighbour\n4-Simulated Anealing\n5-AntsAlgorithm\n6-Geneticalgorithm\n0< start\n";
                cin >> algorithm;
                switch (algorithm) {
                    case 0:
                        cout << "BruteForce added\n";
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new BruteForce());
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    case 1:
                        cout << "Random added\n";
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new Random());
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    case 2:
                        cout << "Branch and Bound added\n";
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new BranchAndBound());
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    case 3:
                        cout << "Closest neighbour added\n";
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new ClosestNeighbour());
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    case 4: {

                        cout <<"Simulated Anealing added\nChoose parameters: temperature, number of interations and cooling factor (-1 -1 -1) for default)";
                        int iter;
                        float temp, coolingFactor;
                        cin >> temp;
                        if (temp < 0) {
                            for (MatrixGraph *graph : graphs) {
                                solversList.push_back(new SimulatedAnnealing());
                                solversList.back()->setGraph(graph);
                            }
                            break;
                        }
                        cin >> iter >> coolingFactor;
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new SimulatedAnnealing(iter, coolingFactor, temp));
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    }
                    case 5: {
                        int iter, antsNum;
                        float alpha, beta, rho;
                        cout <<
                        "Ants Algoriyhm addedn\nChoose parameters number of ants, alpha, beta , rho and number of interations (-1) for default)\n";
                        cin >> antsNum;
                        if (antsNum < 0) {
                            for (MatrixGraph *graph : graphs) {
                                solversList.push_back(new AntsAlgorithm());
                                solversList.back()->setGraph(graph);
                            }
                            break;
                        }
                        cin >> alpha >> beta >> rho >> iter;
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new AntsAlgorithm(antsNum, iter, alpha, beta, rho));
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    }
                    case 6: {
                        int iter, popSize;
                        cout <<
                        "Genetic Algorithm added\nChoose parameters population size and number of interations (-1) for default)\n";
                        cin >> popSize ;
                        if (popSize < 0) {
                            for (MatrixGraph *graph : graphs) {
                                solversList.push_back(new GeneticAlgorithm());
                                solversList.back()->setGraph(graph);
                            }
                            break;
                        }
                        cin >> iter;
                        for (MatrixGraph *graph : graphs) {
                            solversList.push_back(new GeneticAlgorithm(popSize, iter));
                            solversList.back()->setGraph(graph);
                        }
                        break;
                    }
                    default:
                        if(algorithm>6)
                            cout << "Wrong number\n";
                        algorithm=-1;
                        break;
                }
    }while(algorithm>=0);
    cout<<"start\n";
    double start,finish;
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
    for(int i=0;i<solversList.size();i++) {
        cout<<i+1<<". ";
        solversList[i]->printResults();
    }
    cout<<"\t\t\t\t\tMulti threading Executed in time"<<((double)(finish-start))/CLOCKS_PER_SEC;
    graphs.clear();
    solversList.clear();

    return 0;
}