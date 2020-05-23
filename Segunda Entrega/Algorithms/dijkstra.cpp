#include <climits>
#include <algorithm>
#include <iostream>
#include "dijkstra.h"

using namespace std;

vector<int> dijkstraShortestPath(Graph g, const int &origin, const int &dest, vector<int> alreadyVisited) {
    queue<Vertex*> path;
    vector<int> res;
    if(origin == dest)
        return res;
    g.initializeGraph();
    Vertex * vertex = g.findVertex(origin);
    vertex->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(vertex);

    while(!q.empty()) {
        Vertex* temp = q.extractMin();
        for(Edge edge: temp->getAdj()) {
            if (find(alreadyVisited.begin(), alreadyVisited.end(), edge.getDestID()) == alreadyVisited.end()) {
                Vertex *v = g.findVertex(edge.getDestID());
                bool notFound = (v->getDist() == INT_MAX);
                if (v->getDist() > temp->getDist() + edge.getWeight()) {
                    v->setDist(temp->getDist() + edge.getWeight());
                    v->setPath(temp);
                    if (notFound)
                        q.insert(v);
                    else
                        q.decreaseKey(v);
                }
            }
        }
    }

    Vertex* final = g.findVertex(dest);

    path.push(final);
    Vertex* previous = final->getPath();
    path.push(previous);
    if (previous == NULL)
        return res;
    while(previous != vertex) {
        previous = previous->getPath();
        path.push(previous);
    }

    while(!path.empty()){
        res.push_back(path.front()->getId());
        path.pop();
    }
    reverse(res.begin(), res.end());

    return res;
}