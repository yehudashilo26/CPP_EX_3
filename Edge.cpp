#include "Edge.hpp"

namespace ariel
{
    Road *Edge::getRoad()
    {
        return road;
    }

    Node *Edge::getNode1()
    {
        return node1;
    }

    Node *Edge::getNode2()
    {
        return node2;
    }

    void Edge::setRoad(Road *road)
    {
        this->road = road;
    }

    Edge::~Edge()
    {
        delete road;
    }
} // namespace ariel

