#include <iostream>
#include <utility>
#include "Graph.h"

Edge::Edge(int destID, double weight, double slope, double dur, int dif) {
    this->destID = destID;
    this->weight = weight;
    this->slope = slope;
    this->dur = dur;
    this->difficulty = dif;
}

int Edge::getDestID() {
    return destID;
}

int Edge::getDifficulty() {
    return difficulty;
}

double Edge::getWeight() {
    return weight;
}

double Edge::getSlope() {
    return slope;
}

double Edge::getDur() {
    return dur;
}

// Constructor
Vertex::Vertex(int id, int x, int y) : id(id), x(x), y(y){
    this->visited = false;
}

// Get Methods
int Vertex::getId() {
    return id;
}

int Vertex::getX() {
    return x;
}

int Vertex::getY() {
    return y;
}

bool Vertex::getVisited() {
    return visited;
}

// Set Methods
void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setX(int x) {
    this->x = x;
}

void Vertex::setY(int y) {
    this->y = y;
}

void Vertex::setVisited() {
    this->visited = true;
}

vector<Edge> Vertex::getAdj() {
    return adj;
}

void Vertex::addEdge(const int &dest, const double &w, const double &s, const double &d, const int &dif) {
    Edge edge(dest, w, s, d, dif);
    adj.push_back(edge);
}

string Vertex::getType() {
    return type;
}

void Vertex::setType(string t) {
    this->type = std::move(t);
}


Graph::Graph() {

}

double Graph::getMinX() const {
    return minX;
}

double Graph::getMaxX() const {
    return maxX;
}

double Graph::getMinY() const {
    return minY;
}

double Graph::getMaxY() const {
    return maxY;
}

vector<Vertex *> Graph::getVertexSet() {
    return vertexSet;
}

Vertex *Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return nullptr;
}

bool Graph::addVertex(const int &id, const double &x, const double &y) {
    if (findVertex(id) != nullptr)
        return false;
    Vertex* toAdd = new Vertex(id, x, y);
    if (vertexSet.empty()) {
        this->minY = toAdd->getY();
        this->minX = toAdd->getX();
        this->maxX = toAdd->getX();
        this->maxY = toAdd->getY();
    }
    else {
        if(toAdd->getX() > maxX)
            maxX = toAdd->getX();
        else if(toAdd->getX() < minX)
            minX = toAdd->getX();
        if(toAdd->getY() > maxY)
            maxY = toAdd->getY();
        else if (toAdd->getY() < minY)
            minY = toAdd->getY();
    }
    vertexSet.push_back(toAdd);
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, const double &weight, const double &slope, const double &dur, const int &dif) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(dest,weight,slope,dur,dif);
    return true;
}