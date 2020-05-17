#ifndef SEGUNDA_ENTREGA_GRAPH_H
#define SEGUNDA_ENTREGA_GRAPH_H

#include <vector>
#include <string>

using namespace std;

class Edge{
    int destID, difficulty;
    double weight, slope, dur;
public:
    //Constructor
    Edge(int destID, double weight, double slope, double dur, int dif);

    //Get Methods
    int getDestID();
    int getDifficulty();
    double getWeight();
    double getSlope();
    double getDur();

    friend class Graph;
    friend class Vertex;
};

class Vertex{
    int id;
    double x, y;
    bool visited;
    string type;
    vector<Edge> adj;

public:
    //Constructor
    Vertex(int id, int x, int y);

    // Get Methods
    int getId();
    int getX();
    int getY();
    bool getVisited();
    string getType();
    vector<Edge> getAdj();

    // Set Methods
    void setId(int id);
    void setX(int x);
    void setY(int y);
    void setType(string t);
    void setVisited();
    void addEdge(const int &dest, const double &w, const double &s, const double &d, const int &dif);

    friend class Graph;
};

class Graph{
    double minX, maxX, minY, maxY;
    vector<Vertex*> vertexSet;
public:
    //Constructor
    Graph();

    //Get Methods
    double getMinX() const;
    double getMaxX() const;
    double getMinY()const;
    double getMaxY() const;
    vector<Vertex*> getVertexSet();

    Vertex *findVertex(const int &id) const;
    bool addVertex(const int &id, const double &x, const double &y);
    bool addEdge(const int &sourc, const int &dest, const double &weight, const double &slope, const double &dur, const int &dif);
};

#endif //SEGUNDA_ENTREGA_GRAPH_H
