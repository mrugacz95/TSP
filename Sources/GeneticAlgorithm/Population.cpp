#include "../../Headers/GeneticAlgorithm/Population.h"

Population::Population(unsigned int populationSize,float mutationSize,Graph* graph) {
    this->populationSize=populationSize;
    population.resize(populationSize);
    for(int i=0;i<populationSize;i++)
        population[i]=new Path(graph->getSize(),mutationSize,graph);
}

void Population::sortPopulation() {
    sort(population.begin(),population.end(),Path::pathComp);
}

Path* Population::get(int i) {
    return population[i];
}

Population::~Population() {
    for(Path* p : population)
        delete(p);
    population.clear();
}

void Population::makeNewPopulation() {
    int elite = (int)round(0.15f*populationSize);
    for(int i=1;i<elite;i++){
        Path* mother = get(i);
        Path* father = get(randomGenerator()%populationSize);
        population.push_back(new Path(mother,father));
        //population.back()->mutationScramble();
        population.back()->mutationInversion();
    }
    sortPopulation();
    while(population.size()>populationSize) {
        delete (population.back());
        population.pop_back();
    }

}

void Population::print() {
    for(Path* p : population) {
        cout<<p->getLength()<<" ";
        p->print();
    }
    cout<<"\n";
}

Path *Population::getBestAndClean() {
    Path* best = population.front();
    while(population.size()>1) {
        delete (population.back());
        population.pop_back();
    }
    population.pop_back();
    return best;
}
