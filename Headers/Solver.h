#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H


#include "Graph.h"

#include <iostream>
#include <vector>

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
    void printSolutionPath();

    /**
     * Prints used parameters
     */
    virtual void printParameters() = 0;

    virtual ~Solver() = default;

protected:
    double solvingTime;
    Graph *graph;
    std::vector<int> solution;

    virtual void solve() = 0;
    virtual unsigned countSolutionLength(std::vector<int> &vec);
};


#endif //TSP_SOLUTION_H
