#include "../Headers/Random.h"

void Random::solve() {

    solution.resize(graph->getSize());
    for (int i = 0; i < solution.size(); i++)
        solution[i] = i;
    for (int i = 0; i < solution.size(); i++)
        swap(solution[i], solution[rand() % solution.size()]);
}

string Random::getName() {
    return "Random";
}
