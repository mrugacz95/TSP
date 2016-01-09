//
// Created by Mrugi on 2016-01-09.
//

#ifndef OK_TSP_EDGEPHEROMONES_H
#define OK_TSP_EDGEPHEROMONES_H

#include <vector>
using namespace std;
class EdgePheromone{
public:
    EdgePheromone(int size, float initValue);
    float getPheromone(int a, int b);
    void setPheromone(int a, int b, float amount);
    void addPheromone(int a, int b, float amount);

    void reset(float value);

private:
    vector<float> pheromones;

};
#endif //OK_TSP_EDGEPHEROMONES_H
