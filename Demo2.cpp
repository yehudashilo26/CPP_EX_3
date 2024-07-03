#include "Catan.hpp"
#include <unistd.h>
using namespace ariel;

int main(int argc, char const *argv[])
{

    Catan game;

    Player player1("Yoni");
    Player player2("Gil");
    Player player3("Nadav");

    game.addPlayer(&player1);
    game.addPlayer(&player2);
    game.addPlayer(&player3);

    game.ChooseStartingPlayer();

    player1.placeStartPosition(FIFTEEN, ELEVEN); // first index is the settlement, second is where the road leads to.
    player2.placeStartPosition(THIRTYSEVEN, THIRTYTWO);
    player3.placeStartPosition(TWENTYTHREE, SEVENTEEN);

    try
    {
        player3.placeStartPosition(THIRTYSEVEN, FORTYFIVE);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    player1.placeStartPosition(THIRTEEN, EIGHTEEN);
    player2.placeStartPosition(THIRTYFIVE, FORTY);
    player3.placeStartPosition(TWENTYFIVE, THIRTYONE);

    player1.displayCards();
    player2.displayCards();
    player3.displayCards();

    player1.rollDice();
    player1.endTurn();
    player2.rollDice();
    player2.endTurn();
    player3.rollDice();

    player1.displayCards();
    player2.displayCards();
    player3.displayCards();

    // player3.buildRoad(THIRTYONE, THIRTYSIX);
    player3.endTurn();

    // player3.displayCards();

    player1.rollDice();
    player1.endTurn();
    player2.rollDice();
    player2.endTurn();
    player3.rollDice();

    player3.endTurn();

    // player1.displayCards();
    // player3.displayCards();
    try
    {
        player1.buildRoad(EIGHTEEN, TWENTYFOUR); // Should throw an exception cannot build road before rolling the dice;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        player1.buildSettlement(TWENTYFOUR); // Should throw an exception cannot build settlement before rolling the dice;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        player1.endTurn(); // Should throw an exception cannot end turn before rolling the dice or using a development card;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    player1.rollDice();
    player1.buildRoad(EIGHTEEN, TWENTYFOUR);
    player1.displayCards();

    player1.buyDevelopmentCard();
    try
    {
        player2.playDevelopmentCard(CardType::VICTORY_POINT); 
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    player1.displayCards();

    player1.endTurn();
    player2.displayCards();

    player2.buyDevelopmentCard();
    player2.displayCards();
    try
    {
        player2.playDevelopmentCard(CardType::VICTORY_POINT);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    player2.rollDice();
    player2.endTurn();

    player3.rollDice();
    player3.endTurn();
    game.util_showCards();

    player1.rollDice();
    player1.trade(CardType::BRICK, CardType::ORE);
    player1.endTurn();
    game.util_showCards();

    player2.rollDice();
    game.util_showCards();
    player2.trade(CardType::WOOD, CardType::SHEEP);
    player2.endTurn();

    player3.rollDice();
    game.util_showCards();

    map<CardType, size_t> given = {{CardType::WOOD, TWO}};
    map<CardType, size_t> asked = {{CardType::ORE, ONE}};
    player3.trade(&player1, given, asked);
    try
    {
        player3.endTurn();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    player1.respondeToTrade(true);
    game.util_showCards();

    player3.buyDevelopmentCard();
    game.util_showCards();

    player3.endTurn();

    player1.rollDice();
    player1.playDevelopmentCard(CardType::MONOPOLY , CardType::WOOD);
    player1.endTurn();

    player2.rollDice();
    game.util_showCards();
    player2.playDevelopmentCard(CardType::YEAR_OF_PLENTY , CardType::WOOD , CardType::BRICK);
    game.util_showCards();
}
