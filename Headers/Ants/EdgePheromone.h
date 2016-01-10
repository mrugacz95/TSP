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
    double getPheromone(int a, int b);
    void setPheromone(int a, int b, double amount);
    void addPheromone(int a, int b, double amount);

    void reset(float value);

private:
    vector<double> pheromones;

};
#endif //OK_TSP_EDGEPHEROMONES_H
