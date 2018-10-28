#ifndef TSP_GREEDY_H
#define TSP_GREEDY_H


#include "LocalSearch.h"

class Greedy : public LocalSearch {

public:
    std::string getName() override;
    void printParameters() override;

private:
    int search(std::vector<int>& solution) override;

};


#endif //TSP_GREEDY_H
