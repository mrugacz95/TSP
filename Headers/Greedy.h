#ifndef TSP_GREEDY_H
#define TSP_GREEDY_H


#include "LocalSearch.h"

class Greedy : public LocalSearch {

public:
    explicit Greedy(std::default_random_engine engine);
    std::string getName() override;

private:
    int search(std::vector<int>& solution) override;

    std::default_random_engine engine;
};


#endif //TSP_GREEDY_H
