#include "ListGraph.h"

#include <sstream>
#include <limits>

ListGraph::ListGraph(unsigned size) {
    for (int i = 0; i < size; ++i) {
        std::vector<Edge> list;
        for (int j = 0; j < size / 2; ++j) {
            list.push_back(Edge(rand() % size, rand() % size % MAX_LENGTH + 1));
        }
        neighbourList.push_back(list);
    }
}

ListGraph::operator std::string() {
    std::ostringstream result;
    for (int i = 0; i < neighbourList.size(); ++i) {
        result << i << ": ";
        for (auto &j : neighbourList[i]) {
            result << j.getDestiny() << "<l:" << j.getLength() << ">, ";
        }
        result << "\n";
    }
    return result.str();
}

std::string ListGraph::getName() {
    return "ListGraph";
}

bool ListGraph::areConnected(unsigned a, unsigned b) {
    for (auto &i : neighbourList[a]) {
        if (i.getDestiny() == b)
            return true;
    }
    return false;
}

unsigned int ListGraph::distanceBetween(unsigned int a, unsigned int b) {
    for (auto &i : neighbourList[a]) {
        if (i.getDestiny() == b)
            return i.getLength();
    }
    return std::numeric_limits<unsigned int>::max();
}

int ListGraph::findClosestNeighbour(unsigned node) {
    if (neighbourList[node].empty())
        return -1;
    Edge closest = neighbourList[node][0];
    for (auto edge = neighbourList[node].begin(); edge != neighbourList[node].end(); edge++) {
        if (edge->getLength() < closest.getLength()) {
            closest = *edge;
        }
    }
    return closest.getDestiny();
}

ListGraph::~ListGraph() {
    for (auto &neighbour : neighbourList) {
        neighbour.clear();
    }
    neighbourList.clear();
}
