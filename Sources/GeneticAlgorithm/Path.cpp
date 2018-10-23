#include "GeneticAlgorithm/Path.h"

#include <algorithm>
#include <iostream>

Path::Path(unsigned int size, float mutationSize, Graph *graph) {
    this->mutationSize = mutationSize;
    this->graph = graph;
    path.resize(size);
    for (int i = 0; i < path.size(); i++)
        path[i] = i;
    for (int i = 0; i < path.size(); i++)
        std::swap(path[i], path[rand() % path.size()]);
    countLength();
}

bool Path::contains(int vertex) {
    for (int v : path)
        if (v == vertex) return true;
    return false;
}

unsigned int Path::getLength() {
    return length;
}

bool Path::operator<(Path &&rhs) {
    return length < rhs.length;
}

Path::Path(Path *mother, Path *father) {
    unsigned int size = mother->path.size();
    this->path.resize(size, -1);
    int from = rand() % size, to = rand() % size;
    for (int i = 0; i < size; i++) {
        if (from <= to && i >= from && i <= to) {
            path[i] = mother->path[i];
        } else if (from > to && (i >= from || i <= to)) {
            path[i] = mother->path[i];
        }
    }
    int j = (to + 1) % size;
    for (int i = j; i != from; i = (i + 1) % size) {
        while (contains(father->path[j]) && j != to) {
            j++;
            j %= size;
        }
        path[i] = father->path[j++];
        j %= size;
    }
    this->graph = mother->graph;
    countLength();
}

void Path::print() {
    for (int v:path)
        std::cout << v << ", ";
    std::cout << "\n";
}

void Path::mutationInversion() {
    int from = rand() % path.size(),
            to = (from + (int) round(mutationSize * path.size())) % path.size(),
            swapsNum = (from + to) / 2 - from;
    for (int i = 0; i < swapsNum; i++)
        std::swap(path[(from + i) % path.size()], path[(to + path.size() - i) % path.size()]);
}

void Path::mutationScramble() {
    int changesNum;
    if (mutationSize == 0)
        changesNum = 1;
    else
        changesNum = (int) ceil(mutationSize * (double) path.size());
    for (int i = 0; i < changesNum; i++) {
        std::swap(path[rand() % path.size()], path[rand() % path.size()]);
    }

}

void Path::countLength() {
    length = 0;
    for (int i = 0; i < path.size() - 1; i++)
        length += graph->distanceBetween(path[i], path[i + 1]);
    length += graph->distanceBetween(path.front(), path.back());
}

bool Path::pathComp(Path *lhs, Path *rhs) {
    return lhs->getLength() < rhs->getLength();
}

Path::Path(Path *source, Graph *graph) {
    this->graph = graph;
    for (int i = 0; i < source->path.size(); i++)
        this->path.push_back(source->path[i]);
    countLength();
}
