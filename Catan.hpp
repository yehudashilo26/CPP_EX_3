#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Numbers.hpp"
#include <algorithm>

#define NUM_OF_PLAYERS THREE
#define LONGESTROAD FIVE
namespace ariel
{
    // Forward declarations
    class Player;
    class Card;
    class Board;
    class Deck;
    class Node;
    class Edge;
    class BiggestArmyCard;
    class LongestRoadCard;
    enum class SettlementType;

    class Catan
    {
    private:
        Board *board;
        std::vector<Player *> players;
        std::map<Player *, size_t> points;
        std::map<Player *, map<CardType, size_t>> trade_values;
        Player *currentPlayer;
        size_t dice = 0;
        Deck *deck;
        BiggestArmyCard *biggest_army_card;
        LongestRoadCard *longest_road_card;
        size_t longest_road = FIVE; // The length of the longest road (Start value is FIVE for getting the card by the rules).

        // Trade variables
        Player *tradeAsker;               // The player that has asked for a trade
        Player *tradeReceiver;            // The player that has been asked for a trade
        CardType given;                   // The card type that the player is giving
        CardType asked;                   // The card type that the player is asking for
        map<CardType, size_t> givenCards; // The cards that the player is giving
        map<CardType, size_t> askedCards; // The cards that the player is asking for

        // Helper Params
        bool tradeOffered = false;
        bool tradeResponse = false;
        bool hasRolled = false;
        bool rolled_7 = false;
        bool playedDevCard = false;
        bool robberActivated = false;
        bool lastChooseRound = false;
        bool gameStarted = false;
        Player *lastPlayer = nullptr;
        size_t RoadBuildActivated = 0;

        void nextTurn();
        void checkWin();
        void checkRobber();
        void checkTurn(Player *player);
        bool playerExists(Player *player);
        static bool isOccupied(Node *node);
        bool isBuildable(Node *node);
        bool haveRoadToNode(Player *player, size_t index1);
        void checkCardsAfterThrow();
        void updateTradeValues(Player *player, CardType type);
        void checkBiggestArmy();
        void checkLongestRoad(Edge *edge);
        void dfsLongestRoad(Player *player, Edge *edge, size_t length);
        void addPoints(Player *player, size_t points);
        void removePoints(Player *player, size_t points);
        static void revealCard(Player *player, CardType card);
        static void addCard(Player *player, CardType type, size_t amount);
        static void removeCard(Player *player, CardType type, size_t amount);

        vector<vector<int>> edgesToAdjMatrix(map<Node *, map<Node *, Edge *>> edges);

    public:
        Catan();
        ~Catan();
        void addPlayer(Player *player);
        
        void rollDice(Player &player);
        void buildRoad(Player *player, size_t node1, size_t node2);
        void buildSettlement(Player *player, size_t node, SettlementType settlementType);
        void buyDevelopmentCard(Player *player);
        void playDevelopmentCard(Player *player, CardType type);
        void playMonopolyCard(Player *player, CardType type);                     // For Monopoly
        void playYearofPlentyCard(Player *player, CardType type, CardType type2); // For Year of Plenty
        void trade(Player *player, CardType given, CardType asked);
        void trade(Player *player, Player *asked_player,const map<CardType, size_t> &given,const map<CardType, size_t> &asked);
        void respondeToTrade(Player *player, bool response);
        void stealCard(Player *player, Player *steal_player, CardType type);
        void displayBoard();
        void startGame();
        void ChooseStartingPlayer();
        void chooseStartSettlement(Player *player, size_t node);
        void chooseStartRoad(Player *player, size_t node1, size_t node2);
        void endTurn(Player *player);
        void throwCards(Player *player, map<CardType, size_t> &cards);
        void util_showCards();
    };

};