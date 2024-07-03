#include "Settlement.hpp"

namespace ariel
{
    Settlement::Settlement(Player *player) : player(player), type(SettlementType::Settlement){};

    Player *Settlement::getPlayer()
    {
        return player;
    };

    SettlementType Settlement::getType()
    {
        return type;
    };

    void Settlement::upgrade()
    {
        type = SettlementType::City;
    }
}; // namespace ariel