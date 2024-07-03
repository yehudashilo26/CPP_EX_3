#include "Player.hpp"

namespace ariel
{
    void Player::rollDice()
    {
        game->rollDice(*this);
    }

    void Player::buildRoad(size_t index1, size_t index2)
    {
        game->buildRoad(this, index1, index2);
    }

    void Player::buildSettlement(size_t index)
    {
        game->buildSettlement(this, index, SettlementType::Settlement);
    }

    void Player::buildCity(size_t index)
    {
        game->buildSettlement(this, index, SettlementType::City);
    }

    void Player::buyDevelopmentCard()
    {
        game->buyDevelopmentCard(this);
    }

    void Player::playDevelopmentCard(CardType type)
    {
        game->playDevelopmentCard(this, type);
    }

    void Player::playDevelopmentCard(CardType type, CardType type2)
    {
        game->playMonopolyCard(this, type2);
    }

    void Player::playDevelopmentCard(CardType type, CardType type2, CardType type3)
    {
        game->playYearofPlentyCard(this, type2, type3);
    }

    void Player::trade(Player *player, map<CardType, size_t> &given, map<CardType, size_t> &asked)
    {
        game->trade(this, player, given, asked);
    }

    void Player::trade(CardType given, CardType asked)
    {
        game->trade(this, given, asked);
    }
    void Player::respondeToTrade(bool response)
    {
        game->respondeToTrade(this, response);
    }

    void Player::stealCard(Player *player, CardType type)
    {
        // game->stealCard(this, player, type);
    }

    void Player::displayCards()
    {
        if (cards.empty() && revealdeCards.empty())
        {
            cout << name << " has no cards." << endl;
            return;
        }

        cout << name << " has the following cards: ";
        for (auto it = cards.begin(); it != cards.end(); it++)
        {
            cout << (**it);
            if (it != cards.end() - ONE)
            {
                cout << ", ";
            }
        }
        cout << endl;

        if (!revealdeCards.empty())
        {
            cout << name << " has the following revealed cards: ";
            for (auto it = revealdeCards.begin(); it != revealdeCards.end(); it++)
            {
                cout << (**it);
                if (it != revealdeCards.end() - ONE)
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    void Player::placeStartPosition(size_t index1, size_t index2)
    {
        game->chooseStartSettlement(this, index1);
        game->chooseStartRoad(this, index1, index2);
    }

    void Player::endTurn()
    {
        game->endTurn(this);
    }

    size_t Player::getCardAmount(CardType type)
    {
        size_t amount = 0;
        for (size_t i = 0; i < cards.size(); i++)
        {
            if (cards[i]->getType() == type)
            {
                amount++;
            }
        }
        return amount;
    }

    void Player::throwCards(map<CardType, size_t> &cards)
    {
        game->throwCards(this, cards);
    }
}; // namespace ariel
