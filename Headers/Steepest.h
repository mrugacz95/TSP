#ifndef TSP_STEEPEST_H
#define TSP_STEEPEST_H


#include "LocalSearch.h"

class Steepest : public LocalSearch {

public:
    std::string getName() override;
    void printParameters() override;

private:
    int search(std::vector<int>& solution) override;

};


#endif //TSP_STEEPEST_H
