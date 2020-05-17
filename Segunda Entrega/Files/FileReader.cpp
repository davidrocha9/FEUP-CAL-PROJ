#include "FileReader.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "../Graph/Graph.h"
#include "../Graph/GraphViewer.h"

using namespace std;

string makeLower(string s){
    for (char & x : s){
        x = tolower(x);
    }
    return s;
}

void createGraph(const string& cityName){
    Graph graph;
    readNodes(graph, cityName);
    readEdges(graph, cityName);
    readTags(graph, cityName);

    graphDisplay gd(graph, 1920, 1080);
    gd.show();

    getchar();

}

int getDifficulty(double s){
    if (s < 4)
        return 1;
    else if (s < 8)
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

void readNodes(Graph &graph, string cityName) {
    ifstream file;
    string lowerName = makeLower(cityName);
    string fileName = "../Maps/PortugalMaps/" + cityName + "/nodes_x_y_" + lowerName + ".txt";
    file.open(fileName);
    string temp = "";
    int id, var = 0;
    double x, y;

    if(file.is_open()){
        getline(file, temp);
        while(getline(file, temp)){
            while(temp.find(',') != string::npos){
                int index = temp.find(',');
                if (var == 0) {
                    id = stoi(temp.substr(1, index));
                    var++;
                } else {
                    x = stoi(temp.substr(1, index));
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

void readEdges(Graph &graph, string cityName) {
    ifstream file;
    string lowerName = makeLower(cityName);
    string fileName = "../Maps/PortugalMaps/" + cityName + "/edges_" + lowerName + ".txt";
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
            graph.addEdge(src, dest, weight, slope, getDur(weight, slope), difficulty);
            graph.addEdge(dest, src, weight, -slope, getDur(weight, slope), difficulty);
        }
    }
    file.close();
}

void readTags(Graph &graph, string cityName) {
    ifstream file;
    string lowerName = makeLower(cityName);
    string fileName = "../Maps/TagExamples/" + cityName + "/t03_tags_" + lowerName + ".txt";
    file.open(fileName);
    string temp = "", tagName = "";

    if(file.is_open()){
        getline(file, temp);
        while(getline(file, temp)){
            if (temp.find("tourism") != string::npos) {
                tagName = temp.erase(0, 8);
                getline(file, temp);
            } else
                graph.findVertex(stoi(temp))->setType(tagName);
        }
    }

    file.close();

    fileName = "../Maps/TagExamples/" + cityName + "/t10_tags_" + lowerName + ".txt";
    file.open(fileName);
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
    file.close();
}