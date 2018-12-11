#include "SymmetricMatrixGraph.h"
#include "BruteForce.h"
#include "ClosestNeighbour.h"
#include "RandomSolver.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Ants/AntsAlgorithm.h"
#include "SimulatedAnnealing.h"
#include "BranchAndBound.h"
#include "AsymmetricMatrixGraph.h"
#include "Greedy.h"
#include "Steepest.h"
#include <ctime>

int main() {
    int algorithm;
    std::vector<SymmetricMatrixGraph *> graphs;
    std::string outputFile;
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

    std::cout << "Provide output file path\n";
    std::cin >> outputFile;

    std::cout << "Provide seed\n";
    unsigned int seed = 422;
    std::cin >> seed;
    if (seed == 0) {
        seed = (unsigned) time(nullptr);
    }
    srand(seed);
    std::default_random_engine engine;
    engine.seed(seed);

    std::cout << "Choose algorithm:\n0 BruteForce\n1 Random\n2 Branch and Bound"
                 "\n3 Closest Neighbour\n4 Simulated Annealing\n5 AntsAlgorithm"
                 "\n6 Geneticalgorithm\n7 Greedy\n8 Steepest\n-1 start\n";
    std::cin >> algorithm;
    switch (algorithm) {
        case 0:
            std::cout << "BruteForce added\n";
            solver = new BruteForce();
            break;
        case 1:
            std::cout << "Random added\n";
            solver = new RandomSolver(10); // experimentally found formula
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
                         "and cooling factor (-1) for default)";
            float coolingFactor;
            cin >> coolingFactor;
            solver = new SimulatedAnnealing((graph->getSize()-1)*(graph->getSize()-1)/2, coolingFactor);
            break;
        }
        case 5: {
            unsigned int iter, antsNum;
//            float alpha, beta, rho;
//            std::cout <<
//                      "Ants Algorithm added\nChoose parameters number of ants, alpha, beta, rho and number of iterations (-1) for default)\n";
//            cin >> antsNum;
//            if (antsNum < 0) {
                solver = new AntsAlgorithm();
//                break;
//            }
//            cin >> alpha >> beta >> rho >> iter;
//            solver = new AntsAlgorithm(antsNum, iter, alpha, beta, rho);
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
        case 7:
            std::cout << "Greedy added\n";
            solver = new Greedy(engine);
            break;
        case 8:
            std::cout << "Steepest added\n";
            solver = new Steepest(engine);
            break;
        default:
            std::cout << "Wrong number\n";
            return 0;
    }
    std::cout << "Started\n";
    solver->setGraph(graph);
    solver->start();
    solver->getSolvingTime();
    solver->printResults();
    solver->saveToFile(outputFile);
    graphs.clear();
    delete graph;

    return 0;
}
