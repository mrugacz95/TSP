#include "../Headers/BruteForce.h"

void BruteForce::solve() {
    vector<int> tmp;
    tmp.resize(graph->getSize());
    for(int i=0;i<tmp.size();i++)
        tmp[i]=i;
    unsigned length, bestLength = ~0UL>>1;
    do{
        length =0;
        length += countSolutionLength(tmp);
        length +=graph->distBetween(tmp.front(),tmp.back());
        if(length < bestLength) {
            bestLength = length;
            solution = tmp;
        }
    }while (next_permutation(tmp.begin(),tmp.end()));
    return;
}

string BruteForce::getName() {
    return "BruteForce";
}
