//
// Created by josed on 13/05/2020.
//

/*#ifndef SEGUNDA_ENTREGA_GRAPHVIEWER_H
#define SEGUNDA_ENTREGA_GRAPHVIEWER_H

#include <vector>
#include <cstdio>
#include "../lib/graphviewer.h"
#include "Graph.h"

GraphViewer * createWindow(Graph g);

#endif //SEGUNDA_ENTREGA_GRAPHVIEWER_H*/

#pragma once
#include "../Graph/Graph.h"
#include "../lib/graphviewer.h"
#include <algorithm>

class graphDisplay {
private:
    Graph graph;
    GraphViewer * gv;
    int height = 600;
    int width = 600;
public:
    graphDisplay();
    void setGraph(Graph &graph);
    void show(vector<vector<int>> paths);
    void showConnectivity(vector<int> v);

    graphDisplay(Graph graph, int i, int i1);
};
