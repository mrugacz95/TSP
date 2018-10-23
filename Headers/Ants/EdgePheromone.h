#ifndef TSP_EDGEPHEROMONES_H
#define TSP_EDGEPHEROMONES_H

#include <vector>

class EdgePheromone {
public:
    EdgePheromone(int size, float initValue);

    double getPheromone(int a, int b);

    void setPheromone(int a, int b, double amount);

    void addPheromone(int a, int b, double amount);

    void reset(float value);

private:
    std::vector<double> pheromones;

};

#endif //TSP_EDGEPHEROMONES_H
