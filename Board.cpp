#include "Board.hpp"
using namespace ariel;

vector<pair<string, size_t>> map_data = {
    {"Mountains", TEN},
    {"Pasture Land", TWO},
    {"Forest", NINE},
    {"Agricultural Land", TWELVE},
    {"Hills", SIX},
    {"Pasture Land", FOUR},
    {"Hills", TEN},
    {"Agricultural Land", NINE},
    {"Forest", ELEVEN},
    {"Desert", SEVEN},
    {"Forest", THREE},
    {"Mountains", EIGHT},
    {"Forest", EIGHT},
    {"Mountains", THREE},
    {"Agricultural Land", FOUR},
    {"Pasture Land", FIVE},
    {"Hills", FIVE},
    {"Agricultural Land", SIX},
    {"Pasture Land", ELEVEN}};

vector<vector<size_t>> hexagons_nodes = {
    {ONE, FOUR, FIVE, EIGHT, NINE, THIRTEEN},
    {TWO, FIVE, SIX, NINE, TEN, FOURTEEN},
    {THREE, SIX, SEVEN, TEN, ELEVEN, FIFTEEN},
    {EIGHT, TWELVE, THIRTEEN, SEVENTEEN, EIGHTEEN, TWENTYTHREE},
    {NINE, THIRTEEN, FOURTEEN, EIGHTEEN, NINETEEN, TWENTYFOUR},
    {TEN, FOURTEEN, FIFTEEN, NINETEEN, TWENTY, TWENTYFIVE},
    {ELEVEN, FIFTEEN, SIXTEEN, TWENTY, TWENTYONE, TWENTYSIX},
    {SEVENTEEN, TWENTYTWO, TWENTYTHREE, TWENTYEIGHT, TWENTYNINE, THIRTYFOUR},
    {EIGHTEEN, TWENTYTHREE, TWENTYFOUR, TWENTYNINE, THIRTY, THIRTYFIVE},
    {NINETEEN, TWENTYFOUR, TWENTYFIVE, THIRTY, THIRTYONE, THIRTYSIX},
    {TWENTY, TWENTYFIVE, TWENTYSIX, THIRTYONE, THIRTYTWO, THIRTYSEVEN},
    {TWENTYONE, TWENTYSIX, TWENTYSEVEN, THIRTYTWO, THIRTYTHREE, THIRTYEIGHT},
    {TWENTYNINE, THIRTYFOUR, THIRTYFIVE, THIRTYNINE, FORTY, FORTYFOUR},
    {THIRTY, THIRTYFIVE, THIRTYSIX, FORTY, FORTYONE, FORTYFIVE},
    {THIRTYONE, THIRTYSIX, THIRTYSEVEN, FORTYONE, FORTYTWO, FORTYSIX},
    {THIRTYTWO, THIRTYSEVEN, THIRTYEIGHT, FORTYTWO, FORTYTHREE, FORTYSEVEN},
    {FORTY, FORTYFOUR, FORTYFIVE, FORTYEIGHT, FORTYNINE, FIFTYTWO},
    {FORTYONE, FORTYFIVE, FORTYSIX, FORTYNINE, FIFTY, FIFTYTHREE},
    {FORTYTWO, FORTYSIX, FORTYSEVEN, FIFTY, FIFTYONE, FIFTYFOUR}};

static vector<pair<size_t, size_t>> edges_data{
    {ONE, FOUR},
    {ONE, FIVE},
    {TWO, FIVE},
    {TWO, SIX},
    {THREE, SIX},
    {THREE, SEVEN},
    {FOUR, EIGHT},
    {FIVE, NINE},
    {SIX, TEN},
    {SEVEN, ELEVEN},
    {EIGHT, TWELVE},
    {EIGHT, THIRTEEN},
    {NINE, THIRTEEN},
    {NINE, FOURTEEN},
    {TEN, FOURTEEN},
    {TEN, FIFTEEN},
    {ELEVEN, FIFTEEN},
    {ELEVEN, SIXTEEN},
    {TWELVE, SEVENTEEN},
    {THIRTEEN, EIGHTEEN},
    {FOURTEEN, NINETEEN},
    {FIFTEEN, TWENTY},
    {SIXTEEN, TWENTYONE},
    {SEVENTEEN, TWENTYTWO},
    {SEVENTEEN, TWENTYTHREE},
    {EIGHTEEN, TWENTYTHREE},
    {EIGHTEEN, TWENTYFOUR},
    {NINETEEN, TWENTYFOUR},
    {NINETEEN, TWENTYFIVE},
    {TWENTY, TWENTYFIVE},
    {TWENTY, TWENTYSIX},
    {TWENTYONE, TWENTYSIX},
    {TWENTYONE, TWENTYSEVEN},
    {TWENTYTWO, TWENTYEIGHT},
    {TWENTYTHREE, TWENTYNINE},
    {TWENTYFOUR, THIRTY},
    {TWENTYFIVE, THIRTYONE},
    {TWENTYSIX, THIRTYTWO},
    {TWENTYSEVEN, THIRTYTHREE},
    {TWENTYEIGHT, THIRTYFOUR},
    {TWENTYNINE, THIRTYFOUR},
    {TWENTYNINE, THIRTYFIVE},
    {THIRTY, THIRTYFIVE},
    {THIRTY, THIRTYSIX},
    {THIRTYONE, THIRTYSIX},
    {THIRTYONE, THIRTYSEVEN},
    {THIRTYTWO, THIRTYSEVEN},
    {THIRTYTWO, THIRTYEIGHT},
    {THIRTYTHREE, THIRTYEIGHT},
    {THIRTYFOUR, THIRTYNINE},
    {THIRTYFIVE, FORTY},
    {THIRTYSIX, FORTYONE},
    {THIRTYSEVEN, FORTYTWO},
    {THIRTYEIGHT, FORTYTHREE},
    {THIRTYNINE, FORTYFOUR},
    {FORTY, FORTYFOUR},
    {FORTY, FORTYFIVE},
    {FORTYONE, FORTYFIVE},
    {FORTYONE, FORTYSIX},
    {FORTYTWO, FORTYSIX},
    {FORTYTWO, FORTYSEVEN},
    {FORTYTHREE, FORTYSEVEN},
    {FORTYFOUR, FORTYEIGHT},
    {FORTYFIVE, FORTYNINE},
    {FORTYSIX, FIFTY},
    {FORTYSEVEN, FIFTYONE},
    {FORTYEIGHT, FIFTYTWO},
    {FORTYNINE, FIFTYTWO},
    {FORTYNINE, FIFTYTHREE},
    {FIFTY, FIFTYTHREE},
    {FIFTY, FIFTYFOUR},
    {FIFTYONE, FIFTYFOUR}};

namespace ariel
{
    map<size_t, CardType> ports = {
        {ONE, {CardType::NONE}}, {FOUR, {CardType::NONE}}, {TWO, {CardType::WHEAT}}, {SIX, {CardType::WHEAT}}, {ELEVEN, {CardType::ORE}}, {SIXTEEN, {CardType::ORE}}, {TWELVE, {CardType::WOOD}}, {SEVENTEEN, {CardType::WOOD}}, {TWENTYSEVEN, {CardType::NONE}}, {THIRTYTHREE, {CardType::NONE}}, {THIRTYFOUR, {CardType::BRICK}}, {THIRTYNINE, {CardType::BRICK}}, {FORTYTHREE, {CardType::SHEEP}}, {FORTYSEVEN, {CardType::SHEEP}}, {FORTYEIGHT, {CardType::NONE}}, {FIFTYTWO, {CardType::NONE}}, {FIFTYTHREE, {CardType::NONE}}, {FIFTY, {CardType::NONE}}};

    Board::Board()
    {
        hexagons = map<size_t, vector<Hexagon *>>();
        adj_matrix = vector<vector<int>>(NUM_OF_NODES, vector<int>(NUM_OF_NODES, -ONE));

        for (size_t i = 0; i < NUM_OF_NODES; i++)
        {
            nodes.push_back(new Node());
        }

        for (size_t i = 0; i < NINETEEN; i++)
        {
            vector<Node *> hexagon_nodes;
            for (size_t j = 0; j < SIX; j++)
            {
                hexagon_nodes.push_back(nodes[hexagons_nodes[i][j] - ONE]);
            }

            string place = map_data[i].first;
            CardType resource = (place == "Mountains" ? CardType::ORE : place == "Hills"           ? CardType::BRICK
                                                                    : place == "Pasture Land"      ? CardType::SHEEP
                                                                    : place == "Forest"            ? CardType::WOOD
                                                                    : place == "Agricultural Land" ? CardType::WHEAT
                                                                                                   : CardType::NONE);

            hexagonsVector.push_back(new Hexagon(hexagon_nodes, resource, map_data[i].second));
            hexagons[(size_t)map_data[i].second].push_back(hexagonsVector[i]);
        }

        for (auto edge : edges_data)
        {
            Node *node1 = nodes[edge.first - ONE];
            Node *node2 = nodes[edge.second - ONE];
            edges[node1][node2] = new Edge(node1, node2);
            edges[node2][node1] = edges[node1][node2];
            adj_matrix[node1->getId() - ONE][node2->getId() - ONE] = 0;
            adj_matrix[node2->getId() - ONE][node1->getId() - ONE] = 0;
        }
    };

    vector<Hexagon *> Board::getHexagons(size_t diceNumber)
    {
        vector<Hexagon *> hexagons;

        for (auto *hexagon : hexagonsVector)
        {
            if ((hexagon->getDiceNumber()) == diceNumber)
            {
                hexagons.push_back(hexagon);
            }
        }

        return hexagons;
    };

    vector<Hexagon *> Board::getNodeHexagons(size_t nodeIndex)
    {
        vector<Hexagon *> hexagons;
        Node *node = nodes[nodeIndex - ONE];

        for (size_t i = 0; i < hexagonsVector.size(); i++)
        {
            for (size_t j = 0; j < hexagonsVector[i]->getNodes().size(); j++)
            {

                if (hexagonsVector[i]->getNodes()[j] == node)
                {

                    hexagons.push_back(hexagonsVector[i]);
                }
            }
        }

        return hexagons;
    };
    // namespace ariel

    Node *Board::getNode(size_t index)
    {
        return nodes[index - ONE];
    };

    Edge *Board::getEdge(size_t index1, size_t index2)
    {
        return edges[nodes[index1 - ONE]][nodes[index2 - ONE]];
    };

    Hexagon *Board::getHexagon(size_t index)
    {
        return hexagonsVector[index - ONE];
    };

    void Board::PlaceSettlement(Player *player, size_t nodeIndex, SettlementType settlementType)
    {
        switch (settlementType)
        {
        case SettlementType::Settlement:
            nodes[nodeIndex - ONE]->setSettlement(new Settlement(player));
            break;
        case SettlementType::City:
            nodes[nodeIndex - ONE]->getSettlement()->upgrade();
            break;
        }
    };

    void Board::PlaceRoad(Player *player, size_t nodeIndex1, size_t nodeIndex2)
    {
        if (edges[nodes[nodeIndex1 - ONE]][nodes[nodeIndex2 - ONE]]->getRoad() != nullptr)
        {
            throw "Road already exists";
        }

        edges[nodes[nodeIndex1 - ONE]][nodes[nodeIndex2 - ONE]]->setRoad(new Road(player));
        adj_matrix[nodeIndex1 - ONE][nodeIndex2 - ONE] = player->getID();
        adj_matrix[nodeIndex2 - ONE][nodeIndex1 - ONE] = player->getID();
    };

    void Board::PlaceRobber(size_t hexagonIndex)
    {
        hexagonsVector[hexagonIndex - ONE]->setHasRobber(true);
    };

    map<Node *, Edge *> Board::getEdges(Node *node)
    {
        return edges[node];
    };

    map<Node *, map<Node *, Edge *>> Board::getEdges() const
    {
        return edges;
    };

    bool Board::isPort(size_t index)
    {
        return ports.find(index) != ports.end();
    };

    CardType Board::getPortType(size_t index)
    {
        return ports[index];
    };

    size_t Board::getRoadLength(size_t index1, size_t index2, Player *player)
    {
        Node *node1 = nodes[index1 - ONE];
        Node *node2 = nodes[index2 - ONE];

        size_t node1_len = bfs(node1, node2, player); // Calculate the length of the road from node1 without passing through node2
        size_t node2_len = bfs(node2, node1, player); // Calculate the length of the road from node2 without passing through node1

        return node1_len + node2_len + ONE;
    };

    size_t Board::bfs(Node *startNode, Node *forbiddenNode, Player *player)
    {
        queue<pair<Node *, size_t>> q;
        map<Node *, bool> visited;
        size_t maxLength = 0;

        q.push({startNode, 0});
        visited[startNode] = true;

        while (!q.empty())
        {
            auto node_dist = q.front();
            Node *currentNode = node_dist.first;
            size_t length = node_dist.second;
            q.pop();
            maxLength = max(maxLength, length);

            for (auto edge : edges[currentNode])
            {
                if (edge.first != forbiddenNode && !visited[edge.first] && edge.second->getRoad() != nullptr && edge.second->getRoad()->getPlayer() == player)
                {
                    visited[edge.first] = true;
                    q.push({edge.first, length + ONE});
                }
            }
        }

        return maxLength;
    };

    Board::~Board()
    {
        for (Node *node : nodes)
        {
            delete node;
        }

        for (Hexagon *hexagon : hexagonsVector)
        {
            delete hexagon;
        }

        for (auto edge : edges)
        {
            for (auto edge_pair : edge.second)
            {
                if (edge.first->getId() < edge_pair.first->getId())
                {
                    delete edge_pair.second;
                }
            }
        }
    };
};

// namespace ariel
