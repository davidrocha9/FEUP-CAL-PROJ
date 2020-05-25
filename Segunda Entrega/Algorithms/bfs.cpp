//
// Created by davidrocha on 22/05/20.
//

#include "bfs.h"

// Algoritmo bfs
vector<Vertex*> bfs(Graph g, const int &source, const int &dest) {
    vector<Vertex*> res;
    if(source == dest)
        return res;
    queue<Vertex*> q;

    Vertex* s = g.findVertex(source);
    q.push(s);
    s->setVisited(true);

    while (!q.empty()) {
        Vertex* temp = q.front();
        q.pop();
        res.push_back(temp);

        for(Edge edge: temp->getAdj()) {
            Vertex *d = g.findVertex(edge.getDestID());
            if(d == g.findVertex(dest)) {
                res.push_back(d);
                return res;
            }
            if (!d->getVisited()) {
                q.push(d);
                d->setVisited(true);
            }
        }
    }
    res.clear();
    return res;
}