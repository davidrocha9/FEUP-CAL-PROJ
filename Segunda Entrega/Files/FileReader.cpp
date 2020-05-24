#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "math.h"
#include "../Graph/Graph.h"
#include "../Graph/GraphViewer.h"
#include "../Algorithms/dijkstra.h"
#include "time.h"

using namespace std;

Graph createGraph(unsigned int dif, unsigned int randOrNot) {
    Graph graph;
    readNodes(graph);
    readEdges(graph, dif);

    if (randOrNot == 2) {
        srand(time(NULL));
        for (int x = 0; x < 20; x++) {
            int a = rand() % 3900;
            if (graph.getVertexSet().at(a)->getType() == "") {
                graph.getVertexSet().at(a)->setType("restaurant\r");
            }
        }

        for (int x = 0; x < 20; x++) {
            int a = rand() % 3900;
            if (graph.getVertexSet().at(a)->getType() == "") {
                graph.getVertexSet().at(a)->setType("entrance\r");
            }
        }
    } else readTags(graph);

    return graph;
}

int getDifficulty(double s){
    if (abs(s) < 14)
        return 1;
    else if (s < 19)
        return 2;
    return 3;
}

double getDur(double w, double s){
    if (s > 0)
        return w/1.25;
    else
        return w/1.75;
}

double getDistance(int src, int dest, Graph graph, double s){
    Vertex* v1 = graph.findVertex(src);
    Vertex* v2 = graph.findVertex(dest);

    double res = sqrt(pow(v1->getX() - v2->getX(), 2) + pow(v1->getY() - v2->getY(), 2));

    return res / cos(abs(s) * (3.14/180.0));
}

double getSlope(){
    double slopeNum = rand() % 30000 + 1;
    double slopeDen = 1000 + rand() % 5000 + 1;

    return slopeNum/slopeDen;
}

void readNodes(Graph &graph) {
    ifstream file;
    string fileName = "../Maps/PortugalMaps/Penafiel/penafiel_strong_nodes_xy.txt";
    file.open(fileName);
    string temp = "";
    int id, var = 0;
    double x, y;

    if(file.is_open()){
        getline(file, temp);
        graph.setnumNodes(stoi(temp));
        while(getline(file, temp)){
            while(temp.find(',') != string::npos){
                int index = temp.find(',');
                if (var == 0) {
                    id = stoi(temp.substr(1, index));
                    var++;
                } else {
                    x = stoi(temp.substr(0, index));
                }
                temp = temp.erase(0, index + 1);
            }
            y = stoi(temp);
            var = 0;
            graph.addVertex(id, x ,y);
        }
    }
    file.close();
}

void readEdges(Graph &graph, unsigned int dif) {
    ifstream file;
    string fileName = "../Maps/PortugalMaps/Penafiel/penafiel_strong_edges.txt";
    file.open(fileName);
    string temp = "";
    int src, dest, difficulty;
    double weight, slope;

    if(file.is_open()){
        getline(file, temp);
        while(getline(file, temp)){
            while(temp.find(',') != string::npos){
                int index = temp.find(',');
                src = stoi(temp.substr(1, index));
                temp = temp.erase(0, index + 1);
                dest = stoi(temp);
            }
            slope = getSlope();
            weight = getDistance(src, dest, graph, slope);
            difficulty = getDifficulty(slope);
            if (difficulty <= dif) {
                graph.addEdge(src, dest, weight, slope, getDur(weight, slope)/60.0, difficulty);
                graph.addEdge(dest, src, weight, -slope, getDur(weight, slope)/60.0, difficulty);
            }
        }
    }
    file.close();
}

void readTags(Graph &graph) {
    ifstream file;
    //string fileName = "../Maps/TagExamples/" + cityName + "/t03_tags_" + lowerName + ".txt";
    string fileName = "../Maps/TagExamples/Penafiel/t10_tags_penafiel.txt";
    file.open(fileName);
    string temp = "", tagName = "";

    if(file.is_open()){
        getline(file, temp);
        while(getline(file, temp)){
            if (temp.find("amenity") != string::npos) {
                tagName = temp.erase(0, 8);
                getline(file, temp);
            } else
                graph.findVertex(stoi(temp))->setType(tagName);
        }
    }

    //graph.findVertex(18)->setType("restaurant\r");
    //graph.findVertex(1)->setType("entrance\r");

    file.close();
}