#pragma once
#include <vector>
using namespace std;

#include "Card.hpp"
#include "Catan.hpp"

namespace ariel
{
    class Catan; // Forward declaration

    class Player
    {
    private:
        string name;
        size_t id;
        Catan *game;
        vector<Card *> cards;
        vector<Card *> revealdeCards;

        // friend void Catan::addCard(Card *card);
        // friend void Catan::removeCard(Card *card);
        size_t getCardAmount(CardType type);

    public:
        Player(string name) : name(name), game(nullptr){
            static size_t counter = 0;
            id = counter++;

            revealdeCards = vector<Card *>();
        };

        ~Player()
        {
            
        }

        void rollDice();
        void endTurn();
        void placeStartPosition(size_t index1, size_t index2);
        void buildRoad(size_t index1, size_t index2);
        void buildSettlement(size_t index);
        void buildCity(size_t index);
        void buyDevelopmentCard();
        void playDevelopmentCard(CardType type);
        void playDevelopmentCard(CardType type, CardType type2); // For Monopoly
        void playDevelopmentCard(CardType type, CardType type2, CardType type3); // For Year of Plenty
        void trade(Player *player, map<CardType, size_t> &given, map<CardType, size_t> &asked);
        void trade(CardType given, CardType asked);
        void respondeToTrade(bool response);
        void stealCard(Player *player, CardType type);
        void throwCards(map<CardType, size_t> &cards);
        size_t getID() { return id; }
        // helper functions
        void displayCards();

        friend class Catan;
    };
};