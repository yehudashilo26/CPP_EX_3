#pragma once
#include "Road.hpp"
#include "Node.hpp"

namespace ariel{
    class Node; // Forward declaration
    class Road; // Forward declaration
    class Edge{
        private:
            Road* road;
            Node* node1;
            Node* node2;
        public:
            Edge(Node* node1, Node* node2) : road(nullptr), node1(node1), node2(node2) {};
            ~Edge();
            Road* getRoad();
            Node* getNode1();
            Node* getNode2();
            void setRoad(Road* road);
    };
}