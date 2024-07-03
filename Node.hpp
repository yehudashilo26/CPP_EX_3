#pragma once
#include "Settlement.hpp"

namespace ariel
{

    class Settlement; // Forward declaration
    class Node
    {
    static size_t nodeCounter;

    private:
        Settlement *settlement;
        size_t id;
        int color = 0;

    public:
        Node();
        ~Node();
        Settlement *getSettlement();
        void setSettlement(Settlement *settlement);
        int getColor() const;
        void setColor(int color);
        bool isOccupied();
        size_t getId() const;
    };

} // namespace ariel
