#include "Road.hpp"

namespace ariel
{
    Road::Road(Player *player) : player(player) {}

    Player *Road::getPlayer()
    {
        return player;
    }
} // namespace ariel