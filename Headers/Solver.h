#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H


#include "Graph.h"

#include <iostream>
#include <vector>

class Solver {
public:
    void simpleSolve();

    void solveWithTimeCounting();

    virtual std::string getName() = 0;

    void setGraph(Graph *graph);

    virtual void printResults();

    bool operator<(Solver &rhs);

    double getSolvingTime() const;

    virtual void printSolutionPath();

    virtual unsigned countCurrentSolutionLength();

    virtual void printParameters();

    ~Solver();

protected:
    virtual void solve() = 0;

    bool timeCounted;
    double solvingTime;
    Graph *graph;
    std::vector<int> solution;

    virtual unsigned countSolutionLength(std::vector<int> &vec);
};


#endif //TSP_SOLUTION_H
