#ifndef OK_TSP_SOLUTION_H
#define OK_TSP_SOLUTION_H


#include "Graph.h"
#include "../Headers/Graph.h"
#include <thread>
using namespace std;
class Solver {
    public:
        void simpleSolve();
        void solveWithTimeCounting();
        virtual string getName()=0;
        void setGraph(Graph* graph);
        virtual void printResults();
        bool operator< (Solver &rhs);
        double getSolvingTime() const;
        virtual void printSolutionPath();
        virtual unsigned countCurrentSolutionLength();
        virtual void printParameters();
        ~Solver();
    protected:
        virtual void solve()=0;
        bool timeCounted;
        double solvingTime;
        Graph* graph;
        vector<int> solution;

    virtual unsigned countSolutionLength(std::vector<int>& vec);
};


#endif //OK_TSP_SOLUTION_H
