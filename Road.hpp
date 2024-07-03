#pragma once
#include "Player.hpp"

namespace ariel
{
    class Player; // Forward declaration
    class Road
    {
    private:
        Player *player;

    public:
        Road(Player *player);
        ~Road(){};
        Player *getPlayer();
    };
};