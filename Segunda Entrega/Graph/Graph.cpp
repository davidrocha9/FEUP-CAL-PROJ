#include <iostream>
#include <utility>
#include <list>
#include <climits>
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

void Vertex::setVisited(bool v) {
    this->visited = v;
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

void Vertex::setDist(int dist) {
    this->dist = dist;
}

int Vertex::getDist() {
    return dist;
}

void Vertex::setPath(Vertex *path) {
    this->path = path;
}

Vertex *Vertex::getPath() {
    return path;
}

bool Vertex::operator<(Vertex &vertex) const {
    return (this->dist - this->distSourcToDest + this->distFromDest) < (vertex.dist - this->distSourcToDest + vertex.distFromDest);
}


Graph::Graph() {

}

void Graph::initializeGraph() {
    for(auto v: vertexSet) {
        v->dist = INT_MAX;
        v->path = nullptr;
        v->distFromDest = 0;
        v->distSourcToDest = 0;
    }
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

void Graph::setnumNodes(int numNodes){
    this->numNodes = numNodes;
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

void Graph::setVertexSet(vector<Vertex *> v) {
    this->vertexSet = v;
}

//Algorithms