#ifndef TSP_RANDOMGRAPHLOADER_H
#define TSP_RANDOMGRAPHLOADER_H


#include "GraphLoader.h"

class RandomGraphLoader : public GraphLoader {
public:
    Graph *load() override;
};


#endif //TSP_RANDOMGRAPHLOADER_H
