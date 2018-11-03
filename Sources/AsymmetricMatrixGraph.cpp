#include "AsymmetricMatrixGraph.h"

#include <sstream>
#include <fstream>
#include <iostream>

AsymmetricMatrixGraph::AsymmetricMatrixGraph(unsigned size) {
    matrix.resize(size);
    for (int i = 0; i < size; i++) {
        matrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = random() % MAX_LENGTH + 1;
        }
    }
}


AsymmetricMatrixGraph::AsymmetricMatrixGraph(std::string filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "File not found";
        exit(0);
    }
    std::string line;
    int field = 0;
    int size = 0;

    while (getline(infile, line)) {
        if (line.rfind("DIMENSION:", 0) == 0) {
            unsigned long start = line.find_last_of(' ') + 1;
            size = stoi(line.substr(start, line.length() - start));
        }
        if (line == "EDGE_WEIGHT_SECTION") break;
    }
    for (int i = size; i != 0; i--) {
        std::vector<unsigned> row;
        for (int j = size; j != 0; j--) {
            infile >> field;
            row.push_back(field);
        }
        matrix.push_back(row);
    }
}


std::string AsymmetricMatrixGraph::getName() {
    return "AsymmetricMatrixGraph";
}

unsigned int AsymmetricMatrixGraph::getNumberOfNodes() {
    return matrix.size();
}

unsigned int AsymmetricMatrixGraph::distanceBetween(unsigned int a, unsigned int b) {
    return matrix[a][b];
}

bool AsymmetricMatrixGraph::areConnected(unsigned a, unsigned b) {
    return true;
}

AsymmetricMatrixGraph::operator std::string() {
    std::ostringstream result;
    result << "size: " << matrix.size() << "\n";
    for (unsigned i = 0; i < matrix.size(); i++) {
        result << "i: " << i << " ";
        for (unsigned j = 0; j < matrix.size(); j++) {
            result << j << "<" << distanceBetween(i, j) << ">, ";
        }
        result << "\n";
    }
    return result.str();
}

int AsymmetricMatrixGraph::findClosestNeighbour(unsigned node) {
    int distance = matrix[node][0];
    int closest = 0;
    for (unsigned i = 1; i < matrix.size(); i++) {
        if (matrix[node][i] < distance) {
            distance = matrix[node][i];
            closest = i;
        }
    }
    return closest;
}

void AsymmetricMatrixGraph::print() {
    for (auto& x: matrix) {
        for (auto& y: x) {
            std::cout << y << "\t";
        }
        std::cout << std::endl;
    }
}
