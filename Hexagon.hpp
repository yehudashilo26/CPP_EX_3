#pragma once
#include "Node.hpp"

namespace ariel
{
    enum class CardType;
    class Hexagon
    {
    private:
        vector<Node *> nodes;
        CardType resource;
        size_t diceNumber;
        bool hasRobber;

    public:
        Hexagon(vector<Node *> nodes, CardType resource, size_t diceNumber);
        Node *getNode(size_t index);
        vector<Node *> getNodes();
        const CardType &getResource();
        void setHasRobber(bool hasRobber);
        bool getHasRobber() const;
        
        size_t getDiceNumber() { return diceNumber; }

        friend ostream &operator<<(ostream &os, const Hexagon &hexagon);
    };

} // namespace ariel