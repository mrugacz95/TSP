#include "../Headers/Edge.h"

Edge::Edge(int destiny, int lenght) {
    this->destiny = destiny;
    this->lenght = lenght;
}
int Edge::getDestiny() { return destiny; }
int Edge::getLength() { return lenght; }