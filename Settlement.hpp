#pragma once
#include "Player.hpp"

namespace ariel
{
    class Player; // Forward declaration

    enum class SettlementType
    {
        Settlement,
        City
    };

    class Settlement
    {
    private:
        Player *player;
        SettlementType type;

    public:
        Settlement(Player *player);
        Player *getPlayer();
        SettlementType getType();
        void upgrade();
    };

} // namespace ariel