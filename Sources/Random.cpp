//
// Created by Mrugi on 2015-11-14.
//

#include <profileapi.h>
#include "../Headers/Random.h"

void Random::solve() {

    minstd_rand0 randomGenerator;
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    randomGenerator.seed((unsigned)time.QuadPart);
    solution.resize(graph->getSize());
    for(int i=0;i< solution.size();i++)
        solution[i]=i;
    for(int i=0;i<solution.size();i++)
        swap(solution[i],solution[randomGenerator()%solution.size()]);
}

string Random::getName() {
    return "Random";
}
