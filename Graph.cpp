//
// Created by xu zhang on 2022-09-24.
//

#include "Graph.h"

Graph::Graph() {
    *graphNodes = new vector<GraphNode>();
    *size = 0;
}

void Graph::addGraphNode(GraphNode *graphNode) {
    graphNodes->push_back(*graphNode);
    *size = *size + 1;

}

bool Graph::isAdjacent(Territory *territory1, Territory *territory2) {
    return false;
}

void Graph::display() {

}

bool Graph::isValid() {
    return false;
}

bool Graph::isSubGraph(Graph *graph) {
    return false;
}

Territory *Graph::getTerritory(string *territoryName) {
    return nullptr;
}
