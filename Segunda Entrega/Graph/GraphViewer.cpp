//
// Created by josed on 13/05/2020.
//

#include "GraphViewer.h"
#include "../Menus/Utils.h"

void close();

graphDisplay::graphDisplay(Graph graph, int i, int i1) {
    this->graph = graph;
    this->width = i;
    this->height = i1;
    this->gv = new GraphViewer(width, height, false);
}

void graphDisplay::setGraph(Graph &graph) {
    this->graph = graph;
}

void graphDisplay::show(vector<vector<int>> paths) {
    gv->defineVertexColor("yellow");
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(4);
    gv->createWindow(width, height);

    vector<int> ida;
    for (auto x: paths.at(0)) {
        ida.push_back(x);
    }

    vector<int> volta;
    for (auto x: paths.at(1)) {
        volta.push_back(x);
    }

    double yPercent, xPercent;

    for (Vertex* vertex: graph.getVertexSet()){
        if (vertex->getType() == "restaurant\r"){
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexSize(vertex->getId(), 15);
        }
        if (vertex->getType() == "entrance\r"){
            gv->setVertexColor(vertex->getId(), "green");
            gv->setVertexSize(vertex->getId(), 15);
        }
        if (vertex->getId() == ida.at(0)){
            gv->setVertexColor(vertex->getId(), "blue");
            gv->setVertexSize(vertex->getId(), 15);
            gv->setVertexLabel(vertex->getId(), "Comeco");
        }
        if (vertex->getId() == volta.at(volta.size()-1)){
            gv->setVertexColor(vertex->getId(), "orange");
            gv->setVertexSize(vertex->getId(), 15);
            gv->setVertexLabel(vertex->getId(), "Fim");
        }
        if (vertex->getId() == ida.at(ida.size()-1)){
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexSize(vertex->getId(), 15);
            gv->setVertexLabel(vertex->getId(), "Restaurante");
        }
        yPercent = 1.0 - ((vertex->getY()- graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getX() - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getId(), (int) (xPercent * width), (int) (yPercent * height));
        //gv->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
    }

    int id = 0, count = 0;

    for (Vertex* vertex: graph.getVertexSet()){
        for (Edge edge: vertex->getAdj()){
            switch(edge.getDifficulty()){
                case 1:
                    gv->setEdgeColor(id, "green");
                    break;
                case 2:
                    gv->setEdgeColor(id, "yellow");
                    break;
                case 3:
                    gv->setEdgeColor(id, "red");
                    break;
                default:
                    break;
            }
            if (find(ida.begin(), ida.end(), vertex->getId()) != ida.end()) {
                if (find(ida.begin(), ida.end(), edge.getDestID()) != ida.end()) {
                    gv->setEdgeColor(id, "blue");
                    gv->setEdgeThickness(id, 5);
                }
            }

            if (find(volta.begin(), volta.end(), vertex->getId()) != volta.end()) {
                if (find(volta.begin(), volta.end(), edge.getDestID()) != volta.end()) {
                    gv->setEdgeColor(id, "blue");
                    gv->setEdgeThickness(id, 5);
                }
            }

            gv->addEdge(id,vertex->getId(),edge.getDestID(), 0);
            id++;
        }
    }
    this->close();
}

void graphDisplay::showConnectivity(vector<int> v) {
    gv->defineVertexColor("yellow");
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(4);
    gv->createWindow(width, height);

    double yPercent, xPercent;

    for (Vertex* vertex: graph.getVertexSet()){
        if (vertex->getType() == "restaurant\r"){
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexSize(vertex->getId(), 15);
        }
        if (vertex->getType() == "entrance\r"){
            gv->setVertexColor(vertex->getId(), "green");
            gv->setVertexSize(vertex->getId(), 15);
        }

        if (find(v.begin(), v.end(), vertex->getId()) != v.end()){
            gv->setVertexColor(vertex->getId(), "blue");
            gv->setVertexSize(vertex->getId(), 15);
        }

        yPercent = 1.0 - ((vertex->getY()- graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getX() - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getId(), (int) (xPercent * width), (int) (yPercent * height));
        //gv->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
    }

    int id = 0, count = 0;

    for (Vertex* vertex: graph.getVertexSet()){
        for (Edge edge: vertex->getAdj()){
            switch(edge.getDifficulty()){
                case 1:
                    gv->setEdgeColor(id, "green");
                    break;
                case 2:
                    gv->setEdgeColor(id, "yellow");
                    break;
                case 3:
                    gv->setEdgeColor(id, "red");
                    break;
                default:
                    break;
            }

            gv->addEdge(id,vertex->getId(),edge.getDestID(), 0);
            id++;
        }
    }
}
