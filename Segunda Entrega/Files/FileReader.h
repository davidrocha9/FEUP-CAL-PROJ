#ifndef SEGUNDA_ENTREGA_FILEREADER_H
#define SEGUNDA_ENTREGA_FILEREADER_H

#include <string>
#include "../Graph/Graph.h"

void createGraph(const string& cityName);
void readNodes(Graph &graph, string cityName);
void readEdges(Graph &graph, string cityName);
void readTags(Graph &graph, string cityName);

#endif //SEGUNDA_ENTREGA_FILEREADER_H
