#include <algorithm>
#include "../../Headers/GeneticAlgorithm/Path.h"

Path::Path(unsigned int size, float mutationSize, Graph* graph) {
    this->mutationSize=mutationSize;
    this->graph=graph;
    path.resize(size);
    for(int i=0;i< path.size();i++)
        path[i]=i;
    for(int i=0;i<path.size();i++)
        swap(path[i],path[randomGenerator()%path.size()]);
    countLength();
}

bool Path::contains(int vertex) {
    for(int v : path)
        if(v == vertex) return true;
    return false;
}
unsigned int Path::getLength() {
    return length;
}

bool Path::operator<(Path&& rhs) {
    return length<rhs.length;
}

Path::Path(Path* mother, Path* father) {
    unsigned int size=mother->path.size();
    this->path.resize(size,-1);
    int from=randomGenerator()%size,to=randomGenerator()%size;
    for(int i=0;i<size;i++){
        if(from <= to && i>= from && i<=to){
            path[i]=mother->path[i];
        }
        else if(from > to && (i>=from || i<=to )) {
            path[i]=mother->path[i];
        }
    }
    int j=(to+1)%size;
    for(int i=j;i!=from;i=(i+1)%size){
        while(contains(father->path[j]) && j!=to){
            j++;
            j%=size;
        }
        path[i]=father->path[j++];
        j%=size;
    }
    this->graph=mother->graph;
    countLength();
}

void Path::print() {
    for(int v:path)
        cout<<v<<", ";
    cout<<"\n";
}

void Path::mutationInversion() {
    int from=randomGenerator()%path.size(),
            to=(from+(int)round(mutationSize*path.size()))%path.size(),
            swapsNum=(from+to)/2-from;
    for(int i =0;i<swapsNum;i++)
        swap(path[(from+i)%path.size()],path[(to+path.size()-i)%path.size()]);
}

void Path::mutationScramble() {
    int changesNum;
    if(mutationSize==0)
        changesNum=1;
    else
        changesNum= (int)ceil(mutationSize*(double)path.size());
    for(int i=0;i< changesNum;i++){
        swap(path[randomGenerator()%path.size()],path[randomGenerator()%path.size()]);
    }

}

void Path::countLength() {
    length=0;
    for(int i=0;i<path.size()-1;i++)
        length+=graph->distBetween(path[i],path[i+1]);
    length+=graph->distBetween(path.front(),path.back());
}

bool Path::pathComp(Path *lhs, Path *rhs) {
    return lhs->getLength()<rhs->getLength();
}

Path::Path(Path *source,Graph* graph) {
    this->graph = graph;
    for(int i=0;i<source->path.size();i++)
    this->path.push_back(source->path[i]);
    countLength();
}
