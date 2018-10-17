#ifndef TSP_GRAPHLOADER_H
#define TSP_GRAPHLOADER_H


#include "Graph.h"

class GraphLoader {
public:
    virtual Graph *load() = 0;
};


#endif //TSP_GRAPHLOADER_H
