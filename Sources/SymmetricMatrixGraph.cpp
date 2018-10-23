#include "SymmetricMatrixGraph.h"

#include <iostream>
#include <sstream>

SymmetricMatrixGraph::SymmetricMatrixGraph(unsigned int size) {
    this->size = size;
    distances.resize(size * (size - 1) / 2);
    for (unsigned int &i : distances) {
        i = rand() % MAX_LENGTH + 1;
    }
}

unsigned int SymmetricMatrixGraph::distanceBetween(unsigned int a, unsigned int b) {
    if (a >= b) {
        if (a == b) return std::numeric_limits<unsigned int>::max();
        return distances[(a * (a - 1)) / 2 + b];
    } else
        return distances[(b * (b - 1)) / 2 + a];
}

std::string SymmetricMatrixGraph::getName() {
    return "SymmetricMatrixGraph";
}

SymmetricMatrixGraph::operator std::string() {
    std::ostringstream result;
    result << "size: " << distances.size() << " " << size << " " << size * (size + 1) / 2 + size - 2 << "\n";
    for (unsigned i = 0; i < size; i++) {
        result << "i: " << i << " ";
        for (unsigned j = 0; j < size; j++) {
            result << j << "<" << distanceBetween(i, j) << ">, ";
        }
        result << "\n";
    }
    return result.str();
}

unsigned int SymmetricMatrixGraph::getNumberOfNodes() { return size; }

SymmetricMatrixGraph::~SymmetricMatrixGraph() {
    distances.clear();
}

bool SymmetricMatrixGraph::areConnected(unsigned a, unsigned b) {
    return true;
}

int SymmetricMatrixGraph::findClosestNeighbour(unsigned node) {
    int distance = distanceBetween(node, 0);
    int closest = 0;
    for (unsigned i = 1; i < size; i++) {
        unsigned newDistance = distanceBetween(node, i);
        if (newDistance < distance) {
            distance = newDistance;
            closest = i;
        }
    }
    return closest;
}

