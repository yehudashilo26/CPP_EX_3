#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Player.hpp"

namespace ariel
{
    class Player;

    enum class CardType
    {
        NONE,
        WHEAT,
        WOOD,
        BRICK,
        SHEEP,
        ORE,
        KNIGHT,
        VICTORY_POINT,
        ROAD_BUILDING,
        MONOPOLY,
        YEAR_OF_PLENTY,
        BIGGEST_ARMY,
        LONGEST_ROAD
    };

    class Card
    {
    protected:
        CardType type;

    public:
        Card(CardType type) : type(type) {}
        virtual ~Card() = default; // virtual destructor to allow derived classes to be destructed properly
        CardType getType();
        static string cardTypeToString(CardType type);

        friend ostream &operator<<(ostream &os, const CardType type);
        friend ostream &operator<<(ostream &os, const Card &card);
        virtual void activate() = 0; // pure virtual function (abstract)
    };

    class ResourceCard : public Card
    {
    public:
        ResourceCard(CardType type);
        void activate() override {}; // override the pure virtual function , the function is not needed in this class
    };

    class DevelopmentCard : public Card
    {
    public:
        DevelopmentCard(CardType type);
        virtual void activate() = 0;
    };

    class KnightCard : public DevelopmentCard
    {
    public:
        KnightCard() : DevelopmentCard(CardType::KNIGHT) {}
        void activate() override;
    };

    class VictoryPointCard : public DevelopmentCard
    {
    public:
        VictoryPointCard() : DevelopmentCard(CardType::VICTORY_POINT) {}
        void activate() override;
    };

    class RoadBuildingCard : public DevelopmentCard
    {
    public:
        RoadBuildingCard() : DevelopmentCard(CardType::ROAD_BUILDING) {}
        void activate() override;
    };

    class MonopolyCard : public DevelopmentCard
    {
    public:
        MonopolyCard() : DevelopmentCard(CardType::MONOPOLY) {}
        void activate() override;
    };

    class YearOfPlentyCard : public DevelopmentCard
    {
    public:
        YearOfPlentyCard() : DevelopmentCard(CardType::YEAR_OF_PLENTY) {}
        void activate() override;
    };

    class BiggestArmyCard : public DevelopmentCard
    {
    private:
        Player *player;

    public:
        BiggestArmyCard() : DevelopmentCard(CardType::BIGGEST_ARMY) {};
        void activate() override;
        Player *getPlayer();
        void setPlayer(Player *player);
    };

    class LongestRoadCard : public DevelopmentCard
    {
        Player *player;

    public:
        LongestRoadCard() : DevelopmentCard(CardType::LONGEST_ROAD) {}
        void activate() override;
        Player *getPlayer();
        void setPlayer(Player *player);
    };

    class Deck
    {
    private:
        map<CardType, size_t> developmentCardsCount;
        vector<DevelopmentCard *> developmentCards;

    public:
        Deck();
        ~Deck();
        void addCard(DevelopmentCard *card);
        DevelopmentCard *draw();
    };
};

#endif // CARD_HPP