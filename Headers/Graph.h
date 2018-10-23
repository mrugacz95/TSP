#ifndef OK_TSP_GRAPH_H
#define OK_TSP_GRAPH_H

#include <string>

class Graph {
public:
    /**
     * Returns graph's implementation name
     * @return graph's implementation name
     */
    virtual std::string getName() = 0;

    /**
     * Computes number of nodes in graph
     * @return number of nodes in graph
     */
    virtual unsigned int getNumberOfNodes() = 0;

    /**
     * Computes distance between two nodes, if these are not connected returns max value for unsigned int
     * @param a first node
     * @param b second node
     * @return distance between two nodes
     */
    virtual unsigned int distanceBetween(unsigned int a, unsigned int b) = 0;

    /**
     * Checks if two nodes a and b are connected
     * @param a first node
     * @param b second node
     * @return true if nodes are connected, false otherwise
     */
    virtual bool areConnected(unsigned a, unsigned b) = 0;

    /**
     * Retuens graph as string showing all connections and distances between nodes
     */
    virtual explicit operator std::string() = 0;

    /**
     * Returns closest neighbour for node in grpah
     * @param node Node to find closest neighbour
     * @return distance to closest neighbour
     */
    virtual int findClosestNeighbour(unsigned node) = 0;

    /**
     * Class destructor
     */
    virtual ~Graph() = default;

    const unsigned MAX_LENGTH = 100;
};


#endif //OK_TSP_GRAPH_H

