#include <iostream>
#include "Headers/MatrixGraph.h"
#include "Headers/BruteForce.h"
#include "Headers/ClosestNeighbour.h"
#include "RandomSolver.h"
#include "Headers/GeneticAlgorithm/GeneticAlgorithm.h"
#include "Headers/Ants/AntsAlgorithm.h"
#include "Headers/SimulatedAnnealing.h"
#include "Headers/BranchAndBound.h"
#include "Headers/GraphLoader.h"
#include "Headers/RandomGraphLoader.h"

using namespace std;

int main() {
    int algorithm;
    srand((int) time(NULL));
    vector<MatrixGraph *> graphs;
    Solver *solver = nullptr;

    GraphLoader *graphLoader;
    cout << "Choose graph source:\n0 Random graph\n1 From file\n";
    int graphSource;
    cin >> graphSource;
    switch (graphSource) {
        case 1: //TODO implement loading from file
        default:
            graphLoader = new RandomGraphLoader();
            break;

    }
    do {
        cout
                << "Choose algorithm:\n0 BruteForce\n1 Random\n2 Branch and Bound\n3 Closest Neighbour\n4 Simulated Annealing\n5 AntsAlgorithm\n6 Geneticalgorithm\n-1 start\n";
        cin >> algorithm;
        switch (algorithm) {
            case 0:
                cout << "BruteForce added\n";
                solver = new BruteForce();
                break;
            case 1:
                cout << "Random added\n";
                solver = new RandomSolver(1000);
                break;
            case 2:
                cout << "Branch and Bound added\n";
                solver = new BranchAndBound();
                break;
            case 3:
                cout << "Closest neighbour added\n";
                solver = new ClosestNeighbour();
                break;
            case 4: {

                cout << "Simulated Annealing added\nChoose parameters: temperature, "
                        "number of iterations and cooling factor (-1) for default)";
                unsigned int iter;
                float temp, coolingFactor;
                cin >> temp;
                if (temp < 0) {
                    solver = new SimulatedAnnealing();
                    break;
                }
                cin >> iter >> coolingFactor;
                solver = new SimulatedAnnealing(iter, coolingFactor, temp);
                break;
            }
            case 5: {
                unsigned int iter, antsNum;
                float alpha, beta, rho;
                cout <<
                     "Ants Algorithm added\nChoose parameters number of ants, alpha, beta, rho and number of iterations (-1) for default)\n";
                cin >> antsNum;
                if (antsNum < 0) {
                    solver = new AntsAlgorithm();
                    break;
                }
                cin >> alpha >> beta >> rho >> iter;
                solver = new AntsAlgorithm(antsNum, iter, alpha, beta, rho);
                break;
            }
            case 6: {
                unsigned int iter, popSize;
                float mutSize;
                cout << "Genetic Algorithm added\nChoose parameters population size,"
                        " mut ratio and number of iterations (-1) for default)\n";
                cin >> popSize;
                if (popSize < 0) {
                    solver = new GeneticAlgorithm();
                    break;
                }
                cin >> mutSize >> iter;
                solver = new GeneticAlgorithm(popSize, mutSize, iter);
                break;
            }
            default:
                if (algorithm > 6)
                    cout << "Wrong number\n";
                algorithm = -1;
        }
    } while (algorithm >= 0);
    cout << "Started\n";
    Graph *graph = graphLoader->load();
    solver->setGraph(graph);
    solver->solveWithTimeCounting();
    solver->countCurrentSolutionLength();
    solver->printResults();
    graphs.clear();
    delete graph;

    return 0;
}