//
// Created by Marcin Mrugas on 17.10.2018.
//

#include <RandomGraphLoader.h>
#include <MatrixGraph.h>

Graph *RandomGraphLoader::load() {
    return new MatrixGraph(10);
}
