#include "Catan.hpp"

namespace ariel
{
    Catan::Catan()
    {
        board = new Board();
        deck = new Deck();
        biggest_army_card = new BiggestArmyCard();
        longest_road_card = new LongestRoadCard();
        // viewer = new Viewer(board); Gui is not implemented yet
        srand(THREE);

        currentPlayer = nullptr;
        tradeAsker = nullptr;
        tradeReceiver = nullptr;
        given = CardType::NONE;
        asked = CardType::NONE;
    }

    Catan::~Catan()
    {
        delete deck;
        delete board;
        delete biggest_army_card;
        delete longest_road_card;
    }

    void Catan::addPlayer(Player *player)
    {
        if (players.size() == NUM_OF_PLAYERS)
        {
            throw invalid_argument("There are already THREE players in the game");
        }

        players.push_back(player);
        trade_values[player] = map<CardType, size_t>();
        for (CardType type : {CardType::BRICK, CardType::WOOD, CardType::WHEAT, CardType::SHEEP, CardType::ORE})
        {
            trade_values[player][type] = FOUR;
        }

        player->game = this;
        player->id = players.size();
        points[player] = 0;

        if (players.size() == NUM_OF_PLAYERS)
        {
            startGame();
        }
    }

    void Catan::addCard(Player *player, CardType type, size_t amount)
    {
        if (amount == 0)
        {
            throw invalid_argument("Amount must be greater than 0");
        }

        for (size_t i = 0; i < amount; i++)
        {
            switch (type)
            {
            case CardType::WHEAT:
                player->cards.push_back(new ResourceCard(CardType::WHEAT));
                break;
            case CardType::WOOD:
                player->cards.push_back(new ResourceCard(CardType::WOOD));
                break;
            case CardType::BRICK:
                player->cards.push_back(new ResourceCard(CardType::BRICK));
                break;
            case CardType::SHEEP:
                player->cards.push_back(new ResourceCard(CardType::SHEEP));
                break;
            case CardType::ORE:
                player->cards.push_back(new ResourceCard(CardType::ORE));
                break;
            case CardType::KNIGHT:
                player->cards.push_back(new KnightCard());
                break;
            case CardType::VICTORY_POINT:
                player->cards.push_back(new VictoryPointCard());
                break;
            case CardType::ROAD_BUILDING:
                player->cards.push_back(new RoadBuildingCard());
                break;
            case CardType::MONOPOLY:
                player->cards.push_back(new MonopolyCard());
                break;
            case CardType::YEAR_OF_PLENTY:
                player->cards.push_back(new YearOfPlentyCard());
                break;
            default:
                throw invalid_argument("Invalid card type");
            }
        }
    }
    void Catan::removeCard(Player *player, CardType type, size_t amount)
    {
        if (amount == 0)
        {
            throw invalid_argument("Amount must be greater than 0");
        }

        if (player->getCardAmount(type) < amount)
        {
            throw invalid_argument("Player does not have enough cards");
        }

        for (size_t i = 0; i < amount; i++)
        {
            for (auto it = player->cards.begin(); it != player->cards.end(); it++)
            {
                if ((*it)->getType() == type)
                {
                    Card *card = *it;
                    player->cards.erase(it);
                    delete card;
                    break;
                }
            }
        }
    }

    void Catan::nextTurn()
    {
        currentPlayer = players[(size_t)(find(players.begin(), players.end(), currentPlayer) - players.begin() + ONE) % NUM_OF_PLAYERS];
        hasRolled = false;
        playedDevCard = false;
    }

    void Catan::rollDice(Player &player)
    {
        checkCardsAfterThrow();
        checkTurn(&player);

        if (hasRolled)
        {
            throw invalid_argument("You have already rolled the dice");
        }

        dice = (size_t)((((rand()) % SIX) + ONE) + (((rand() + THREE) % SIX) + ONE));

        cout << player.name << " rolled " << dice << endl;

        hasRolled = true;

        if (dice == SEVEN)
        {
            rolled_7 = true;

            for (auto *player : players)
            {
                if (player->cards.size() > SEVEN)
                {
                    cout << player->name << " has more than SEVEN cards, must discard " << player->cards.size() / TWO << " cards" << endl;
                }
            }

            // to be implemented
        }
        else
        {
            for (Hexagon *hex : board->getHexagons(dice))
            {
                for (Node *node : hex->getNodes())
                {

                    if (node->getSettlement() != nullptr)
                    {
                        Settlement *settlement = node->getSettlement();
                        CardType type = hex->getResource();
                        for (int i = 0; i <= (int)settlement->getType(); i++)
                        {
                            addCard(settlement->getPlayer(), type, ONE);
                        }
                    }
                }
            }
        }
    };

    void Catan::checkTurn(Player *player)
    {
        if (!playerExists(player))
        {
            throw invalid_argument("Player does not exist");
        }

        if (player != currentPlayer)
        {
            throw invalid_argument("It is not your turn");
        }
    }

    void Catan::ChooseStartingPlayer()
    {
        size_t index = 0;               // replace with rand() % THREE, to randomly choose a player to start the game
        currentPlayer = players[index]; // Randomly choose a player to start the game
        lastPlayer = players[(index + TWO) % NUM_OF_PLAYERS];
    }

    void Catan::chooseStartSettlement(Player *player, size_t node)
    {
        checkTurn(player);

        if (gameStarted)
        {
            throw invalid_argument("Game has already started");
        }

        Node *chosenNode = board->getNode(node);

        if (isOccupied(chosenNode))
        {
            throw invalid_argument("Node already has a settlement");
        }

        for (auto edge : board->getEdges(chosenNode))
        {
            if (isOccupied(edge.first))
            {
                throw invalid_argument("Settlement must be at least TWO edges away from another settlement");
            }
        }

        chosenNode->setSettlement(new Settlement(player));
        addPoints(player, ONE);

        if (lastChooseRound)
        {
            for (auto *hex : board->getNodeHexagons(node))
            {

                if (hex->getResource() != CardType::NONE)
                {
                    addCard(player, hex->getResource(), ONE);
                }
            }
        }
    }

    void Catan::chooseStartRoad(Player *player, size_t node1, size_t node2)
    {
        checkTurn(player);

        if (gameStarted)
        {
            throw invalid_argument("Game has already started");
        }

        board->PlaceRoad(player, node1, node2);

        if (player == lastPlayer)
        {
            if (!lastChooseRound)
            {
                lastChooseRound = true;
            }
            else
            {
                gameStarted = true;
            }
        }

        nextTurn();
    }

    void Catan::startGame()
    {
        ChooseStartingPlayer();
    }

    void Catan::endTurn(Player *player)
    {
        checkCardsAfterThrow();

        checkTurn(player);
        if (RoadBuildActivated > 0)
        {
            throw invalid_argument("You must play the road building card and place TWO roads before ending your turn");
        }
        if (!hasRolled && !playedDevCard)
        {
            throw invalid_argument("You must roll the dice or play a development card before ending your turn");
        }

        if (tradeOffered)
        {
            throw invalid_argument("Must respond to the trade before ending the turn");
        }
        nextTurn();
    }

    void Catan::buildRoad(Player *player, size_t node1, size_t node2)
    {
        checkCardsAfterThrow();

        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (!hasRolled)
        {
            throw invalid_argument("You must roll the dice before building a road");
        }
        Edge *edge = board->getEdge(node1, node2);

        if (edge->getRoad() != nullptr)
        {
            throw invalid_argument("Road already exists");
        }

        bool haveRoad1 = haveRoadToNode(player, node1);
        bool haveRoad2 = haveRoadToNode(player, node2);
        bool isBlocked1 = false;
        bool isBlocked2 = false;

        if (!haveRoad1 && !haveRoad2)
        {
            throw invalid_argument("You must have a road connected to the node");
        }

        if ((edge->getNode1()->getSettlement() != nullptr && edge->getNode1()->getSettlement()->getPlayer() != player) || !haveRoad1)
        {
            isBlocked1 = true;
        }

        if ((edge->getNode2()->getSettlement() != nullptr) && (edge->getNode2()->getSettlement()->getPlayer() != player || !haveRoad2))
        {
            isBlocked2 = true;
        }

        if (isBlocked1 && isBlocked2)
        {
            throw invalid_argument("Cannot continue road after another player's settlement");
        }
        // road costs

        if (RoadBuildActivated == 0)
        {
            if (player->getCardAmount(CardType::BRICK) < ONE || player->getCardAmount(CardType::WOOD) < ONE)
            {
                throw invalid_argument("You do not have enough resources to build a road");
            }

            removeCard(player, CardType::BRICK, ONE);
            removeCard(player, CardType::WOOD, ONE);
        }

        else
        {
            RoadBuildActivated--;
        }

        cout << "Player " << player->name << " built a road between nodes " << node1 << " and " << node2 << endl;
        edge->setRoad(new Road(player));

        checkLongestRoad(edge);
    }

    void Catan::buildSettlement(Player *player, size_t node, SettlementType settlementType)
    {
        checkCardsAfterThrow();
        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (!hasRolled)
        {
            throw invalid_argument("You must roll the dice before building a settlement");
        }
        Node *chosenNode = board->getNode(node);

        if (isOccupied(chosenNode))
        {
            if (chosenNode->getSettlement()->getPlayer() != player)
            {
                throw invalid_argument("Node already has a settlement of another player");
            }

            SettlementType type = chosenNode->getSettlement()->getType();

            if (type == SettlementType::City)
            {
                throw invalid_argument("Node already has a city");
            }

            if (settlementType == SettlementType::Settlement)
            {
                throw invalid_argument("Node already has a settlement");
            }

            // cost of a city are THREE ore and TWO wheat
            if (player->getCardAmount(CardType::ORE) < THREE || player->getCardAmount(CardType::WHEAT) < TWO)
            {
                throw invalid_argument("You do not have enough resources to build a city");
            }

            removeCard(player, CardType::ORE, THREE);
            removeCard(player, CardType::WHEAT, TWO);

            chosenNode->getSettlement()->upgrade();
            addPoints(player, ONE);

            if (Board::isPort(node))
            {
                updateTradeValues(player, Board::getPortType(node));
            }
            cout << "Player " << player->name << " built a city" << " on node " << node << endl;
            return;
        }

        if (!isBuildable(chosenNode))
        {
            throw invalid_argument("Node must be at least TWO edges away from another settlement");
        }

        if (!haveRoadToNode(player, node))
        {
            throw invalid_argument("You must have a road connected to the node");
        }

        // cost of a settlement are ONE brick, ONE wood, ONE wheat, ONE sheep
        if (player->getCardAmount(CardType::BRICK) < ONE || player->getCardAmount(CardType::WOOD) < ONE || player->getCardAmount(CardType::WHEAT) < ONE || player->getCardAmount(CardType::SHEEP) < ONE)
        {
            throw invalid_argument("You do not have enough resources to build a settlement");
        }

        removeCard(player, CardType::BRICK, ONE);
        removeCard(player, CardType::WOOD, ONE);
        removeCard(player, CardType::WHEAT, ONE);
        removeCard(player, CardType::SHEEP, ONE);

        chosenNode->setSettlement(new Settlement(player));
        addPoints(player, ONE);

        cout << "Player " << player->name << " built a settlement" << " on node " << node << endl;
    }

    void Catan::buyDevelopmentCard(Player *player)
    {
        checkCardsAfterThrow();
        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (player->getCardAmount(CardType::ORE) < ONE || player->getCardAmount(CardType::WHEAT) < ONE || player->getCardAmount(CardType::SHEEP) < ONE)
        {
            throw invalid_argument("You do not have enough resources to buy a development card");
        }

        removeCard(player, CardType::ORE, ONE);
        removeCard(player, CardType::WHEAT, ONE);
        removeCard(player, CardType::SHEEP, ONE);

        DevelopmentCard *card = deck->draw();
        player->cards.push_back(card);

        cout << "Player " << player->name << " bought a development card" << endl;
    }

    void Catan::playDevelopmentCard(Player *player, CardType type)
    {
        checkCardsAfterThrow();
        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (player->getCardAmount(type) == 0)
        {
            throw invalid_argument("You do not have this card");
        }

        playedDevCard = true;
        switch (type)
        {
        case CardType::KNIGHT:
            revealCard(player, CardType::KNIGHT);
            checkBiggestArmy();
            break;

        case CardType::VICTORY_POINT:
            revealCard(player, CardType::VICTORY_POINT);
            addPoints(player, ONE);

            cout << "Player " << player->name << " played a victory point card and now have " << points[player] << " points" << endl;

            break;
        case CardType::ROAD_BUILDING:
            RoadBuildActivated = TWO;
            deck->addCard(new RoadBuildingCard());
            break;

        default:
            throw invalid_argument("Invalid card type");
        }
    }

    void Catan::playYearofPlentyCard(Player *player, CardType type, CardType type2)
    {
        checkCardsAfterThrow();
        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (player->getCardAmount(CardType::YEAR_OF_PLENTY) == 0)
        {
            throw invalid_argument("You do not have this card");
        }

        removeCard(player, CardType::YEAR_OF_PLENTY, ONE);
        addCard(player, type, ONE);
        addCard(player, type2, ONE);

        cout << "Player " << player->name << " played a year of plenty card" << endl;
    }

    void Catan::playMonopolyCard(Player *player, CardType type)
    {
        checkCardsAfterThrow();
        checkTurn(player);

        if (!gameStarted)
        {
            throw invalid_argument("Game has not started yet");
        }

        if (player->getCardAmount(CardType::MONOPOLY) == 0)
        {
            throw invalid_argument("You do not have this card");
        }

        removeCard(player, CardType::MONOPOLY, ONE);

        for (Player *p : players)
        {
            if (p != player)
            {
                size_t amount = p->getCardAmount(type);
                if (amount > 0)
                {
                    removeCard(p, type, amount);
                    addCard(player, type, amount);
                }
            }
        }

        cout << "Player " << player->name << " played a monopoly card" << endl;
    }
    void Catan::trade(Player *player, Player *asked_player,const map<CardType, size_t> &given,const map<CardType, size_t> &asked)
    {
        checkCardsAfterThrow();

        if (!hasRolled)
        {
            throw invalid_argument("Player must roll the dice before trading");
        }
        if (player != currentPlayer && asked_player != currentPlayer)
        {
            throw invalid_argument("Can only trade with the current player");
        }

        if (player == asked_player)
        {
            throw invalid_argument("Cannot trade with yourself");
        }

        if (tradeOffered)
        {
            throw invalid_argument("Must complete the current trade before offering a new one");
        }

        for (auto card : given)
        {
            if (player->getCardAmount(card.first) < card.second)
            {
                throw invalid_argument("Player does not have enough to trade");
            }
        }

        for (auto card : asked)
        {
            if (asked_player->getCardAmount(card.first) < card.second)
            {
                throw invalid_argument("The other player does not have enough of this card");
            }
        }

        if (player == currentPlayer)
        {
            tradeAsker = player;
            tradeReceiver = asked_player;
        }
        else
        {
            tradeAsker = asked_player;
            tradeReceiver = player;
        }

        givenCards = given;
        askedCards = asked;

        tradeOffered = true;
        cout << "Player " << player->name << " has offered a trade to player " << asked_player->name << endl;
        cout << "Offered: ";
        for (auto card : given)
        {
            cout << card.second << " " << Card::cardTypeToString(card.first) << " ";
        }

        cout << "Asked: ";
        for (auto card : asked)
        {
            cout << card.second << " " << Card::cardTypeToString(card.first) << " ";
        }
        cout << endl;
    }

    void Catan::respondeToTrade(Player *player, bool response)
    {
        if (!tradeOffered)
        {
            throw invalid_argument("No trade has been offered");
        }

        if (player != tradeReceiver)
        {
            throw invalid_argument("Only the receiver of the trade can respond");
        }

        if (response)
        {
            for (auto card : givenCards)
            {
                removeCard(tradeAsker, card.first, card.second);
                addCard(tradeReceiver, card.first, ONE);
            }

            for (auto card : askedCards)
            {
                removeCard(tradeReceiver, card.first, card.second);
                addCard(tradeAsker, card.first, ONE);
            }
        }

        string responseStr;

        if (response)
        {
            responseStr = "accepted";
        }
        else
        {
            responseStr = "declined";
        }
        cout << player->name << " has " << responseStr << " the trade" << endl;
        tradeOffered = false;
    }
    // helper functions
    bool
    Catan::playerExists(Player *player)
    {
        return find(players.begin(), players.end(), player) != players.end();
    };

    bool Catan::isOccupied(Node *node)
    {
        return node->getSettlement() != nullptr;
    }

    bool Catan::haveRoadToNode(Player *player, size_t index1)
    {
        Node *node = board->getNode(index1);

        for (auto edge : board->getEdges(node))
        {
            if (edge.second->getRoad() != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    bool Catan::isBuildable(Node *node)
    {
        for (auto edge : board->getEdges(node))
        {
            if (edge.first->getSettlement() != nullptr)
            {
                return false;
            }
        }

        return true;
    }

    void Catan::throwCards(Player *player, map<CardType, size_t> &cards)
    {
        for (auto card : cards)
        {
            if (player->getCardAmount(card.first) < card.second)
            {
                throw invalid_argument("Player does not have enough of this card");
            }
        }

        for (auto card : cards)
        {
            removeCard(player, card.first, card.second);
        }

        cout << "Player " << player->name << " has thrown " << cards.size() << " cards" << endl;
        for (Player *p : players)
        {
            if (p->cards.size() > SEVEN)
            {
                cout << p->name << " has more than SEVEN cards, must discard " << p->cards.size() / TWO << " cards" << endl;
                return;
            }
        }

        rolled_7 = false;
    }

    void Catan::checkCardsAfterThrow()
    {
        if (!rolled_7)
        {
            return;
        }

        for (Player *player : players)
        {
            if (player->cards.size() > SEVEN)
            {
                cout << player->name << " has more than SEVEN cards, must discard " << player->cards.size() / TWO << " cards" << endl
                     << "Cards: ";
                for (auto *card : player->cards)
                {
                    cout << *card << ", ";
                }
                cout << endl;

                throw invalid_argument(player->name + " has more than SEVEN cards, must discard");
            }
        }
    }

    void Catan::util_showCards()
    {
        for (Player *player : players)
        {
            player->displayCards();
        }
    }

    void Catan::trade(Player *player, CardType given, CardType asked)
    {
        checkTurn(player);
        size_t ratio = trade_values[player][asked];

        if (player->getCardAmount(given) < ratio)
        {
            throw invalid_argument("Player does not have enough of this card");
        }

        for (size_t i = 0; i < ratio; i++)
        {
            removeCard(player, given, ONE);
        }

        addCard(player, asked, ONE);
        string givenCard = given == CardType::BRICK ? "brick" : given == CardType::WOOD ? "wood"
                                                            : given == CardType::WHEAT  ? "wheat"
                                                            : given == CardType::SHEEP  ? "sheep"
                                                                                        : "ore";
        string askedCard = asked == CardType::BRICK ? "brick" : asked == CardType::WOOD ? "wood"
                                                            : asked == CardType::WHEAT  ? "wheat"
                                                            : asked == CardType::SHEEP  ? "sheep"
                                                                                        : "ore";

        cout << "Player " << player->name << " traded with bank " << ratio << " " << givenCard << " for ONE " << askedCard << endl;
    }

    void Catan::updateTradeValues(Player *player, CardType type)
    {
        if (type == CardType::NONE)
        {
            // set all trading rate to THREE;
            for (CardType curr_type : {CardType::BRICK, CardType::WOOD, CardType::WHEAT, CardType::SHEEP, CardType::ORE})
            {
                trade_values[player][curr_type] > THREE ? trade_values[player][curr_type] = THREE : trade_values[player][curr_type];
            }
        }

        else
        {
            trade_values[player][type] = TWO;
        }
    }

    void Catan::checkBiggestArmy()
    {
        size_t max = 0;
        Player *maxPlayer = nullptr;
        for (Player *p : players)
        {
            size_t armySize = 0;
            for (Card *card : p->revealdeCards)
            {
                if (card->getType() == CardType::KNIGHT)
                {
                    armySize++;
                }
            }

            if (armySize > max)
            {
                max = armySize;
                maxPlayer = p;
            }
        }

        if (max >= THREE && maxPlayer != biggest_army_card->getPlayer())
        {
            if (biggest_army_card->getPlayer() != nullptr)
            {
                removePoints(biggest_army_card->getPlayer(), TWO);
            }

            biggest_army_card->setPlayer(maxPlayer);
            if (maxPlayer != nullptr)
            {
                addPoints(maxPlayer, TWO);
            }
        }
    }

    void Catan::checkLongestRoad(Edge *edge)
    {
        Player *player = edge->getRoad()->getPlayer();
        size_t length = board->getRoadLength(edge->getNode1()->getId(), edge->getNode2()->getId(), player);

        if (length > longest_road)
        {
            longest_road = length;

            if (longest_road_card->getPlayer() != nullptr)
            {
                removePoints(longest_road_card->getPlayer(), TWO);
            }

            longest_road_card->setPlayer(player);
            addPoints(player, TWO);
        }
    };

    void Catan::addPoints(Player *player, size_t points)
    {

        this->points[player] += points;

        if (this->points[player] >= TEN)
        {
            cout << "Player " << player->name << " has won the game!" << endl;
            exit(0);
        }
    }

    void Catan::removePoints(Player *player, size_t points)
    {
        if (points > this->points[player])
        {
            throw invalid_argument("Player does not have enough points");
        }

        this->points[player] -= points;
    }

    void Catan::revealCard(Player *player, CardType card)
    {
        for (auto it = player->cards.begin(); it != player->cards.end(); it++)
        {
            if ((*it)->getType() == card)
            {
                player->revealdeCards.push_back(*it);
                player->cards.erase(it);
                return;
            }
        }

        throw invalid_argument("Player does not have this card");
    }
};
// namespace ariel
