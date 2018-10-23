#include "BruteForce.h"

#include <limits>

void BruteForce::solve() {
    std::vector<int> tmp;
    tmp.resize(graph->getNumberOfNodes());
    for (int i = 0; i < tmp.size(); i++)
        tmp[i] = i;
    unsigned length, bestLength = std::numeric_limits<unsigned int>::max();
    do {
        length = 0;
        length += countSolutionLength(tmp);
        length += graph->distanceBetween(tmp.front(), tmp.back());
        if (length < bestLength) {
            bestLength = length;
            solution = tmp;
        }
    } while (next_permutation(tmp.begin(), tmp.end()));
    return;
}

std::string BruteForce::getName() {
    return "BruteForce";
}
