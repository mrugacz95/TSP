#ifndef OK_TSP_GRAPH_H
#define OK_TSP_GRAPH_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Graph {
public:
    int verticesNumber;

    virtual void print() = 0;

    virtual unsigned int getSize() = 0;

    virtual unsigned int distBetween(int a, int b) = 0;

    virtual unsigned getMaxLength() = 0;

protected:
    unsigned maxLength;
};


#endif //OK_TSP_GRAPH_H

