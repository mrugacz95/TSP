#include "../Headers/ListGraph.h"

ListGraph::ListGraph() {
    this->verticesNumber = 20;
    for (int i = 0; i < verticesNumber; ++i) {
        std::vector<Edge> list;
        for (int j = 0; j < verticesNumber / 2; ++j) {
            list.push_back(Edge(rand()% verticesNumber, rand()% verticesNumber %100+1));
        }
        neighbourList.push_back(list);
    }
}
void ListGraph::print() {
    for (int i = 0; i < neighbourList.size(); ++i) {
        std::cout<<i<<": ";
        for (int j = 0; j < neighbourList[i].size(); ++j) {
            std::cout<<neighbourList[i][j].getDestiny()<<"<l:"<<neighbourList[i][j].getLength()<<">, ";
        }
        std::cout<<"\n";
    }
}

bool ListGraph::areConnected(int a, int b) {
    for (int i = 0; i < neighbourList[a].size(); ++i) {
        if (neighbourList[a][i].getDestiny()==b)
            return true;
    }
    return false;
}

unsigned int ListGraph::distBetween(int a, int b) {
    for (int i = 0; i < neighbourList[a].size(); ++i) {
        if (neighbourList[a][i].getDestiny()==b)
            return neighbourList[a][i].getLength();
    }
    return -1;
}

std::vector<Edge> ListGraph::getVertNeighbours(int a) {
    return std::vector<Edge>();
}


int ListGraph::findClosestNeighbour(int v) {
    if(neighbourList[v].empty())
        return -1;
    int closest=neighbourList[v][0].getLength();
    int n;
    for(int i=1;i<neighbourList[v].size();i++){
        if(neighbourList[v][i].getLength() < closest) {
            closest = neighbourList[v][i].getLength();
            n=i;
        }
        return n;
    }


}
