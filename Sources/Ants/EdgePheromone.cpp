//
// Created by Mrugi on 2016-01-09.
//

#include "../../Headers/Ants/EdgePheromone.h"

EdgePheromone::EdgePheromone(int size, float initValue) {
    pheromones.resize((unsigned)size*(size-1)/2);
    reset(initValue);
}
float EdgePheromone::getPheromone(int a, int b) {

    if (a >= b) {
        if (a == b) return 0;
        return pheromones[(a * (a - 1)) / 2 + b];
    }
    else
        return pheromones[(b * (b - 1)) / 2 + a];
}
void EdgePheromone::setPheromone(int a, int b, float amount){
    if (a >= b)
        pheromones[(a * (a - 1)) / 2 + b]=amount;
    else
        pheromones[(b * (b - 1)) / 2 + a]=amount;
}

void EdgePheromone::addPheromone(int a, int b, float amount) {
    if (a >= b)
        pheromones[(a * (a - 1)) / 2 + b]+=amount;
    else
        pheromones[(b * (b - 1)) / 2 + a]+=amount;
}

void EdgePheromone::reset(float value) {
    for(int i=0;i<pheromones.size();i++)
        pheromones[i]=value;
}
//
//EdgePheromone::~EdgePheromone() {
//    pheromones.clear();
//}
