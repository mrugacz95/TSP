//
// Created by Mrugi on 2015-10-28.
//

#ifndef OK_TSP_GRAPH_H
#define OK_TSP_GRAPH_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
class Graph{
    public:
        int verticesNumber;
        virtual void print()=0;
        virtual unsigned int getSize()=0;
        virtual unsigned int distBetween(int a, int b)=0;
};

#endif //OK_TSP_GRAPH_H

