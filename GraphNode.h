//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_GRAPHNODE_H
#define CPP_N23_GRAPHNODE_H


#include "Territory.h"

class GraphNode {
private:
    Territory* vertex;
    vector<string>* edges;

public:
    GraphNode() = default;
    GraphNode(Territory* vertex, vector<string>* edges) : vertex(vertex), edges(edges) {};
    ~GraphNode() = default;

    // Getters
    Territory* getVertex() const { return vertex; }
    vector<string>* getEdges() const { return edges; }

    // Setters
    void setVertex(Territory* vertex) { this->vertex = vertex; }
    void setEdges(vector<string>* edges) { this->edges = edges; }

    // Methods
    void addEdge(string* edge):

};

};


#endif //CPP_N23_GRAPHNODE_H
