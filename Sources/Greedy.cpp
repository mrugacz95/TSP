#include "Greedy.h"


int Greedy::search(std::vector<int>& solution) {
    for (int i=0; i < solution.size()-1; i++) {
        for (int j=i+1; j < solution.size(); j++) {
            int d = LocalSearch::delta(solution, i, j);
            if (d < 0) {
                std::swap(solution[i], solution[j]);
                return d;
            }
        }
    }
    return 0;
}

std::string Greedy::getName() {
    return "Greedy LS Solver";
}
