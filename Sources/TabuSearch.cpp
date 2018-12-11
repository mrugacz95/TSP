#include "TabuSearch.h"
#include <numeric>
#include <TabuSearch.h>
#include <algorithm>

TabuSearch::TabuSearch(unsigned k, unsigned cadence) {
    this->k = k;
    this->cadence = cadence;
}

std::string TabuSearch::getName() {
    return "TabuSearch";
}

void TabuSearch::printParameters() {

}

void TabuSearch::solve() {
    // init solution
    solution.resize(graph->getSize());
    std::iota(solution.begin(), solution.end(), 0);
    std::shuffle(solution.begin(), solution.end(), engine);

    //init tabu array
    tabu.resize(graph->getSize() - 1);
    for (unsigned i = 1; i < graph->getSize(); ++i) {
        tabu[i - 1].resize(graph->getSize() - i);
    }
    unsigned notImproved = 0;
    std::vector<Move> nextMoves;
    nextMoves.resize(k * 10, Move(0, 0, 0));
    while (notImproved < 10) {
        // generate next k moves
        for (int i = 0; i < k * 10; ++i) {
            nextMoves[i].from = engine() % graph->getSize();
            do {
                nextMoves[i].to = engine() % graph->getSize();
            } while (nextMoves[i].to == nextMoves[i].from);
            nextMoves[i].delta = delta(solution, nextMoves[i].from, nextMoves[i].to);
        }
        // sort moves
        std::sort(nextMoves.begin(), nextMoves.end());
        // apply moves
        bool improved = false;
        for (int i = 0; i < k; ++i) {
            if (nextMoves[i].delta > 0) {
                break;
            }
            if (getTabu(nextMoves[i].from, nextMoves[i].to) == 0) {
                setTabu(nextMoves[i].from, nextMoves[i].to, cadence);
                std::swap(solution[nextMoves[i].from], solution[nextMoves[i].to]);
                improved = true;
            }
        }
        if (!improved)
            notImproved++;
        // decrease cadence
        for (int i = 0; i < graph->getSize() - 1; ++i) {
            for (int j = 0; j < graph->getSize() - i - 1; ++j) {
                tabu[i][j] = (((int) tabu[i][j]) - 1 > 0) ? tabu[i][j] - 1 : 0;
            }
        }
    }
}

unsigned int TabuSearch::countSolutionLength(std::vector<int> &vec) {
    return Solver::countSolutionLength(vec);
}

void TabuSearch::setTabu(unsigned a, unsigned b, unsigned val) {
    if (a < b) {
        tabu[a][b - a - 1] = val;
    } else {
        tabu[b][a - b - 1] = val;
    }
}

unsigned TabuSearch::getTabu(unsigned a, unsigned b) {
    if (a < b) {
        return tabu[a][b - a - 1];
    } else {
        return tabu[b][a - b - 1];
    }
}

