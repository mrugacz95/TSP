#ifndef OK_TSP_RANDOM_H
#define OK_TSP_RANDOM_H


#include "Solver.h"
#include <algorithm>
class Random : public Solver {
    public:
        void solve() override;
        string getName() override;
};


#endif //OK_TSP_RANDOM_H
