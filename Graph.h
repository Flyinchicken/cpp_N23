//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_GRAPH_H
#define CPP_N23_GRAPH_H


#include "Territory.h"
#include "GraphNode.h"

class Graph {
private:
    vector<GraphNode>* graphNodes;
    int* size;

public:
    Graph() { size = new int(0); }
    ~Graph() { delete size; }

    // Getters
    int* getSize() const { return size; }

    // Methods
    void addGraphNode(GraphNode* graphNode);

    bool isAdjacent(Territory* territory1, Territory* territory2);

    void display();

    bool isValid();

    bool isSubGraph(Graph* graph);

    Territory* getTerritory(string* territoryName);

};


#endif //CPP_N23_GRAPH_H
