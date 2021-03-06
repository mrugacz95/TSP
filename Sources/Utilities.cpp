//
// Created by Mrugi on 2015-11-14.
//


#include "../Headers/Solver.h"
#include "../Headers/Utilities.h"

bool Utilities::compLengthAndTime(Solver* lhs, Solver* rhs) {
    return (lhs->countCurrentSolutionLength()==rhs->countCurrentSolutionLength())?
               (lhs->getSolvingTime()<rhs->getSolvingTime())
                  :
               (lhs->countCurrentSolutionLength()<rhs->countCurrentSolutionLength());
}
