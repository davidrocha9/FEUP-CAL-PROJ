//
// Created by josed on 13/05/2020.
//

/*#include "GraphViewer.h"

GraphViewer * createWindow(Graph g){
    double height = g.getMaxY() - g.getMinY();
    double width = g.getMaxX() - g.getMinX();
    int graphSize = 2000;

    auto *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    for(Vertex* vertex: g.getVertexSet()) {
        double y = (vertex->getY() - g.getMinY())/height;
        double x = (vertex->getX() - g.getMinX())/width;

        gv->addNode(vertex->getId(), (int)(x*graphSize), (int)(y*1341));
        gv->setVertexSize(vertex->getId(), 5);
    }
    int id = 0;

    for(Vertex* vertex: g.getVertexSet()) {
        for(Edge edge: vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge.getDestID(), EdgeType::UNDIRECTED);
            id++;
        }
    }

    gv->rearrange();
    return gv;
}*/

#include "GraphViewer.h"

graphDisplay::graphDisplay(Graph graph, int i, int i1) {
    this->graph = graph;
    this->width = i;
    this->height = i1;
    this->gv = new GraphViewer(width, height, false);
}

void graphDisplay::setGraph(Graph &graph) {
    this->graph = graph;
}

void graphDisplay::show() {
    gv->createWindow(width, height);

    double yPercent, xPercent;

    for (Vertex* vertex: graph.getVertexSet()){
        if (vertex->getType() == "information\r")
            gv->setVertexColor(vertex->getId(), "blue");
        else if (vertex->getType() == "attraction\r")
            gv->setVertexColor(vertex->getId(), "red");
        else if (vertex->getType() == "viewpoint\r")
            gv->setVertexColor(vertex->getId(), "black");
        else if (vertex->getType() == "picnic_site\r")
            gv->setVertexColor(vertex->getId(), "yellow");
        else if (vertex->getType() == "camp_site\r")
            gv->setVertexColor(vertex->getId(), "orange");
        else if (vertex->getType() == "museum\r")
            gv->setVertexColor(vertex->getId(), "green");
        else if (vertex->getType() == "restaurant\r")
            gv->setVertexColor(vertex->getId(), "pink");
        else if (vertex->getType() == "cafe\r")
            gv->setVertexColor(vertex->getId(), "white");
        else if (vertex->getType() == "fast_food\r")
            gv->setVertexColor(vertex->getId(), "brown");
        else if (vertex->getType() == "bar\r")
            gv->setVertexColor(vertex->getId(), "purple");



        yPercent = 1.0 - ((vertex->getY()- graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getX() - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getId(), (int) (xPercent * width), (int) (yPercent * height));
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
            gv->addEdge(id,vertex->getId(),edge.getDestID(),0);
            id++;
        }
    }
}
