//
// Created by Mrugi on 2015-11-14.
//

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
