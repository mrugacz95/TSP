//
// Created by Mrugi on 2016-01-08.
//

#include <c++/cmath>
#include "../../Headers/Ants/Ant.h"
#include "../../Headers/Ants/AntsAlgorithm.h"

Ant::Ant(float alpha, float beta, Graph *graph, EdgePheromone *edgePheromone) {
this->graph=graph;
    visited.resize(graph->getSize());
    this->edgePheromone=edgePheromone;
    this->alpha=alpha;
    this->beta=beta;
    vertexProbability.resize(graph->getSize(),0.f);
}

void Ant::walk() {
    path.clear();
    path.push_back(0);
    for(int i=1;i<visited.size();i++)
        visited[i]= false;
    visited[0]= true;
    for(int i=0;i<graph->getSize()-1;i++) {
        path.push_back(chooseVertex());
        visited[path.back()]=true;
    }
}

int Ant::chooseVertex() {
    double probabilitySum=0;
    double distanceAtractiveness;
    double pheromonAtractiveness;
    for(int i =1; i <graph->getSize(); i++) {
        if(!visited[i]){
            pheromonAtractiveness=pow(edgePheromone->getPheromone(path.back(), i),AntsAlgorithm::alpha);
            distanceAtractiveness=pow(1.f/graph->distBetween(path.back(),i),AntsAlgorithm::beta);
            vertexProbability[i]=distanceAtractiveness*pheromonAtractiveness;

            probabilitySum+= vertexProbability[i];
            if(vertexProbability[i]>0 && probabilitySum ==0)
                cout<<"bulshit\n";
        }
        else
            vertexProbability[i]=0;
    }
    if(probabilitySum==0)
        cout<<"ants wtf\n";
    for(int i =1; i <graph->getSize(); i++){
        vertexProbability[i]/=probabilitySum;
        if(isnan(vertexProbability[i]) || (!visited[i] && pow(1.f/graph->distBetween(path.back(),i),AntsAlgorithm::beta)*pow(edgePheromone->getPheromone(path.back(), i),AntsAlgorithm::alpha)==0)){ //TODO usunąć
            int dist=graph->distBetween(path.back(),i);
            distanceAtractiveness=pow(1.f/graph->distBetween(path.back(),i),AntsAlgorithm::beta);
            double pheromone = edgePheromone->getPheromone(path.back(), i);
            pheromonAtractiveness=pow(edgePheromone->getPheromone(path.back(), i),AntsAlgorithm::alpha);
            double wynik = distanceAtractiveness*pheromonAtractiveness;
            vertexProbability[i]=0.000001;
        }
    }
    double random =  (double)AntsAlgorithm::randomGenerator() / (double)numeric_limits<INT32>::max();
    probabilitySum=0;

    for(int i=0;i<vertexProbability.size();i++) {
        probabilitySum += vertexProbability[i];
        if(probabilitySum>=random)
            return i;
    }
    return -1;
}

void Ant::updatePheromone(EdgePheromone *pheromoneDelta) {
    float pheromoneDisposed = 1.f / countLength();
    for(int i=0;i<path.size()-1;i++)
        pheromoneDelta->addPheromone(path[i],path[i+1],pheromoneDisposed);
    pheromoneDelta->addPheromone(path.front(),path.back(),pheromoneDisposed);

}
unsigned int Ant::countLength(){
    length = 0;
    for(int i=0;i<path.size()-1;i++)
        length +=graph->distBetween(path[i],path[i+1]);
    length += graph->distBetween(path.front(),path.back());
    return length;
}

bool Ant::antComp(Ant *lhs, Ant *rhs) {
    return lhs->length<rhs->length;
}

unsigned int Ant::getLength() {
    return length;
}


void Ant::print() {
    for(int v :path)
        cout<<v<<", ";
    cout<<"\n";
}
