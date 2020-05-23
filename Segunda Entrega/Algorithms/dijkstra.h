//
// Created by davidrocha on 22/05/20.
//

#ifndef SEGUNDA_ENTREGA_DIJKSTRA_H
#define SEGUNDA_ENTREGA_DIJKSTRA_H

#include <queue>
#include "../Graph/Graph.h"
#include "../Graph/MutablePriorityQueue.h"

vector<int> dijkstraShortestPath(Graph g, const int &origin, const int &dest, vector<int> alreadyVisited);


#endif //SEGUNDA_ENTREGA_DIJKSTRA_H
