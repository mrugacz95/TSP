//
// Created by Mrugi on 2015-10-29.
//

#ifndef OK_TSP_EDGE_H
#define OK_TSP_EDGE_H


class Edge{
public:
    Edge(int destiny, int lenght);
    int getLength();
    int getDestiny();
private:
    int lenght;
    int destiny;

};


#endif //OK_TSP_EDGE_H
