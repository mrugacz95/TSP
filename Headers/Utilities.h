//
// Created by Mrugi on 2015-11-14.
//

#ifndef OK_TSP_UTILITIES_H
#define OK_TSP_UTILITIES_H


#include "Solver.h"
#include <random>
class Utilities {
    public:
        static bool compLengthAndTime(Solver* lhs, Solver* rhs);
        static minstd_rand0 randomGenerator;
};


#endif //OK_TSP_UTILITIES_H
