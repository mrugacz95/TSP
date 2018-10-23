#ifndef TSP_EDGE_H
#define TSP_EDGE_H


class Edge {
public:
    Edge(unsigned int destiny, unsigned int length);

    unsigned int getLength();

    unsigned int getDestiny();

private:
    unsigned int length;
    unsigned int destiny;

};


#endif //TSP_EDGE_H
