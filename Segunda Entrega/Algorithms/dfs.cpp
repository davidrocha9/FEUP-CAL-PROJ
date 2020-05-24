//
// Created by davidrocha on 24/05/20.
//

#include "dfs.h"

void dfsVisit(Graph graph, Vertex *v, vector<int> &res) {
    v->setVisited(true);
    res.push_back(v->getId());
    for (auto edge : v->getAdj()) {
        if (!graph.findVertex(edge.getDestID())->getVisited()) { dfsVisit(graph, graph.findVertex(edge.getDestID()), res); }
    }
}

vector<int> dfs(Graph graph, const int id_src)  {
    vector<int> result;
    for (auto vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    dfsVisit(graph, graph.findVertex(id_src), result);

    return result;
}