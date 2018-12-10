#ifndef TSP_STEEPEST_H
#define TSP_STEEPEST_H


#include "LocalSearch.h"
#include <random>

class Steepest : public LocalSearch {

public:
    explicit Steepest(std::default_random_engine engine);
    std::string getName() override;

private:
    int search(std::vector<int>& solution) override;

    std::default_random_engine engine;

};


#endif //TSP_STEEPEST_H
