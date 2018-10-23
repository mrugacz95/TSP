#include "Edge.h"

Edge::Edge(unsigned int destiny, unsigned int length) {
    this->destiny = destiny;
    this->length = length;
}

unsigned int Edge::getDestiny() { return destiny; }

unsigned int Edge::getLength() { return length; }