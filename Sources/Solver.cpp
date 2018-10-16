#include "../Headers/Solver.h"

void Solver::setGraph(Graph *graph) {
    this->graph = graph;
}

void Solver::printResults() {
    cout << getName() << " ";
    if (timeCounted)
        cout << solvingTime << " ";
    cout << "Graph size:" << graph->getSize() << " ";
    cout << " Lenght: " << countCurrentSolutionLength() << "\n";
    printParameters();
    cout << "\t\t\t\t\t";
    printSolutionPath();
    cout << "\n";
}

unsigned Solver::countSolutionLength(std::vector<int> &vec) {
    unsigned int length = 0;
    for (int i = 0; i < vec.size() - 1; i++)
        length += graph->distBetween(vec[i], vec[i + 1]);
    length += graph->distBetween(vec.front(), vec.back());
    return length;
}

void Solver::solveWithTimeCounting() {
    timeCounted = true;
    int counter = 0;
    clock_t begin = clock(), end;
    do {
        solve();
        counter++;
        end = clock();
    } while (end - begin < 60 && counter < 10);
    solvingTime = double(end - begin) / counter;
}

void Solver::simpleSolve() {
    timeCounted = false;
    solve();
}

bool Solver::operator<(Solver &rhs) {
    return solvingTime < rhs.getSolvingTime();
}

double Solver::getSolvingTime() const {
    return solvingTime;
}

unsigned Solver::countCurrentSolutionLength() {
    if (solution.empty())
        return ~0UL;

    return countSolutionLength(solution);
}

thread Solver::solveAsync() {
    return thread([=] { solveWithTimeCounting(); });
}


Solver::~Solver() {
    delete (graph);
}

void Solver::printSolutionPath() {
    if (solution.empty()) {
        cout << "Not solved";
        return;
    }
    for (int v : solution)
        cout << v << ", ";
    cout << "\n";
}

void Solver::printParameters() {
    return;
}
