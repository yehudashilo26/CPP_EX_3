#pragma once
#include "Node.hpp"
#include "Edge.hpp"
#include "Hexagon.hpp"
#include "Numbers.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define NUM_OF_NODES FIFTYFOUR
#define NUM_OF_HEXAGONS NINETTEN
#define NUM_OF_EDGES 72

namespace ariel
{
    // Forward declarations
    class Node;
    class Edge;
    class Hexagon;
    enum class SettlementType;

    class Board
    {
    private:
        vector<Node *> nodes;
        map<Node *, map<Node *, Edge *>> edges;
        map<size_t, vector<Hexagon *>> hexagons; // key is the dice number
        vector<Hexagon *> hexagonsVector;
        vector<vector<int>> adj_matrix;

        size_t bfs(Node *startNode, Node *forbiddenNode, Player *player);

    public:
        Board();
        ~Board();
        void PlaceSettlement(Player *player, size_t nodeIndex, SettlementType settlementType);
        void PlaceRoad(Player *player, size_t nodeIndex1, size_t nodeIndex2);
        void PlaceRobber(size_t hexagonIndex);
        Node *getNode(size_t index);
        Edge *getEdge(size_t index1, size_t index2);
        map<Node *, Edge *> getEdges(Node *node);
        map<Node *, map<Node *, Edge *>> getEdges() const;
        Hexagon *getHexagon(size_t index);
        vector<Hexagon *> getHexagons(size_t diceNumber);
        vector<Hexagon *> getNodeHexagons(size_t nodeIndex);
        static bool isPort(size_t nodeIndex);
        static CardType getPortType(size_t nodeIndex);
        size_t getRoadLength(size_t nodeIndex1, size_t nodeIndex2 , Player *player);
        };
};