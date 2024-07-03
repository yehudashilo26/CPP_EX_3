#include "Node.hpp"

namespace ariel
{
    size_t Node::nodeCounter = ONE;

    Node::Node() : settlement(nullptr), id(nodeCounter++) {};

    Settlement *Node::getSettlement()
    {
        return settlement;
    }

    void Node::setSettlement(Settlement *settlement)
    {
        this->settlement = settlement;
    }

    int Node::getColor() const
    {
        return color;
    }

    void Node::setColor(int color)
    {
        this->color = color;
    }

    bool Node::isOccupied()
    {
        return settlement != nullptr;
    }

    size_t Node::getId() const
    {
        return id;
    }

    Node::~Node()
    {
        delete settlement;
    }
} // namespace ariel