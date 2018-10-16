#include "../Headers/MatrixGraph.h"

MatrixGraph::MatrixGraph(unsigned int size) {
    this->size=size;
    distances.resize(size*(size-1)/2);
    for(unsigned int& i : distances){
        i=rand()+1;
    }
    maxLength=UINT16_MAX;
}
MatrixGraph::MatrixGraph(unsigned int size, unsigned int maxLength) {
    this->size=size;
    distances.resize(size*(size-1)/2);
    for(unsigned int& i : distances){
        i=rand()%maxLength+1;
    }
    this->maxLength=maxLength;
}
unsigned int MatrixGraph::distBetween(int a, int b) {

    if (a >= b) {
        if (a == b) return (~0UL)>>1;
        return distances[(a * (a - 1)) / 2 + b];
    }
    else
        return distances[(b * (b - 1)) / 2 + a];
}

void MatrixGraph::print() {
    cout<<"size: "<<distances.size()<<" "<<size<<" "<<size*(size+1)/2+size-2<<"\n";
    for(int i=0;i<size;i++) {
        cout<<"i: "<<i<<" ";
        for (int j = 0; j < size; j++) {
            cout << j << "<"<<distBetween(i,j)<<">, ";
        }
        cout<<"\n";
    }
}

unsigned int MatrixGraph::getSize() { return size; }

MatrixGraph &MatrixGraph::operator=(MatrixGraph &&other){
    return *this;
}

MatrixGraph::MatrixGraph(const MatrixGraph& graph) {
    this->distances = graph.distances;
}

unsigned MatrixGraph::getMaxLength() {
    return maxLength;
}
