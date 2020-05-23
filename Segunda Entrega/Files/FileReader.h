#ifndef SEGUNDA_ENTREGA_FILEREADER_H
#define SEGUNDA_ENTREGA_FILEREADER_H

#include <string>
#include "../Graph/Graph.h"

Graph createGraph(unsigned int dif);
void readNodes(Graph &graph);
void readEdges(Graph &graph, unsigned int dif);
void readTags(Graph &graph);

#endif //SEGUNDA_ENTREGA_FILEREADER_H
