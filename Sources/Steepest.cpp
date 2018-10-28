#include "Steepest.h"


int Steepest::search(std::vector<int>& solution) {
    int max_d = 0;
    int max_i = 0, max_j = 0;
    for (int i=0; i < solution.size()-1; i++) {
        for (int j=i+1; j < solution.size(); j++) {
            int d = LocalSearch::delta(solution, i, j);
            if (d < 0) {
                max_d = d;
                max_i = i;
                max_j = j;
            }
        }
    }
    std::swap(solution[max_i], solution[max_j]);
    return max_d;
}

std::string Steepest::getName() {
    return "Steepest LS Solver";
}

void Steepest::printParameters() {

}
