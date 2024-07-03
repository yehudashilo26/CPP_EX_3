#include "Hexagon.hpp"

namespace ariel
{
    Hexagon::Hexagon(vector<Node *> nodes, CardType resource, size_t diceNumber) : nodes(move(nodes)), resource(resource), diceNumber(diceNumber), hasRobber(false){};

    Node *Hexagon::getNode(size_t index)
    {
        return nodes.at(index);
    }

    const CardType &Hexagon::getResource()
    {
        return resource;
    }

    void Hexagon::setHasRobber(bool hasRobber)
    {
        this->hasRobber = hasRobber;
    }

    bool Hexagon::getHasRobber() const
    {
        return hasRobber;
    }

    vector<Node *> Hexagon::getNodes()
    {
        return {nodes[0], nodes[ONE], nodes[TWO], nodes[THREE], nodes[FOUR], nodes[FIVE]};
    }

    ostream &operator<<(ostream &os, const Hexagon &hexagon)
    {
        os << "Hexagon: " << endl;
        os << "Resource: " << (int)hexagon.resource << endl;
        os << "Dice Number: " << hexagon.diceNumber << endl;

        return os;
    }
} // namespace ariel