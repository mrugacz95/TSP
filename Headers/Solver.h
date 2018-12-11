#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H


#include "Graph.h"

#include <iostream>
#include <vector>
#include <limits>

class Solver {
public:
    /**
     * Starts solution optimization
     */
    void start();

    /**
     * Returns solver implementation name
     * @return
     */
    virtual std::string getName() = 0;

    /**
     * Graph setter
     * @param graph Graph with distances to find solution
     */
    void setGraph(Graph *graph);

    /**
     * prints found results
     */
    void printResults();

    /**
     * prints scores
     */
    void printScores();

    /**
     * prints solving times
     */
    void printTimes();

    /**
     * Operator which allows to compare solvers by time
     * @param rhs other solver
     * @return
     */
    bool operator<(Solver &rhs);

    /**
     * Returns solution time
     * @return solution time
     */
    double getSolvingTime() const;

    /**
     * Prints found path
     */
    std::string getSolutionPath();

    /**
     * Prints used parameters
     */
    virtual void printParameters() = 0;

    virtual ~Solver() = default;

    void saveToFile(std::string filename);

    int delta(std::vector<int> solution, unsigned i, unsigned j);

    virtual unsigned countSolutionLength(std::vector<int> &vec);

protected:
    double meanSolvingTime;
    std::vector<double> solvingTimes;
    Graph *graph;
    std::vector<int> solution;
    std::vector<int> bestScores;
    std::vector<int> firstScores;

    virtual void solve() = 0;

    unsigned deltaCounter = 0;
};


#endif //TSP_SOLUTION_H
