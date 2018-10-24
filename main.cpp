#include "SymmetricMatrixGraph.h"
#include "BruteForce.h"
#include "ClosestNeighbour.h"
#include "RandomSolver.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Ants/AntsAlgorithm.h"
#include "SimulatedAnnealing.h"
#include "BranchAndBound.h"
#include "AsymmetricMatrixGraph.h"

int main() {
    int algorithm;
    srand(422);
    std::vector<SymmetricMatrixGraph *> graphs;
    Solver *solver = nullptr;
    Graph *graph;
    std::cout << "Choose graph source:\n0 Random graph\n1 From file\n";
    int graphSource;
    std::cin >> graphSource;
    switch (graphSource) {
        case 0:
            unsigned size;
            std::cout << "Provide graph size\n";
            std::cin >> size;
            graph = new AsymmetricMatrixGraph(size);
            break;
        default:
            std::cout << "Provide file path\n";
            std::string filename;
            std::cin >> filename;
            graph = new AsymmetricMatrixGraph(filename);
            break;

    }
    std::cout << "Choose algorithm:\n0 BruteForce\n1 Random\n2 Branch and Bound"
                 "\n3 Closest Neighbour\n4 Simulated Annealing\n5 AntsAlgorithm"
                 "\n6 Geneticalgorithm\n-1 start\n";
    std::cin >> algorithm;
    switch (algorithm) {
        case 0:
            std::cout << "BruteForce added\n";
            solver = new BruteForce();
            break;
        case 1:
            std::cout << "Random added\n";
            solver = new RandomSolver(1000);
            break;
        case 2:
            std::cout << "Branch and Bound added\n";
            solver = new BranchAndBound();
            break;
        case 3:
            std::cout << "Closest neighbour added\n";
            solver = new ClosestNeighbour();
            break;
        case 4: {

            std::cout << "Simulated Annealing added\nChoose parameters: temperature, "
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
            std::cout <<
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
            std::cout << "Genetic Algorithm added\nChoose parameters population size,"
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
            std::cout << "Wrong number\n";
            return 0;
    }
    std::cout << "Started\n";
    solver->setGraph(graph);
    solver->start();
    solver->getSolvingTime();
    solver->printResults();
    graphs.clear();
    delete graph;

    return 0;
}