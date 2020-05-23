//
// Created by davidrocha on 23/05/20.
//

#ifndef SEGUNDA_ENTREGA_PATHGENERATOR_H
#define SEGUNDA_ENTREGA_PATHGENERATOR_H

#include "../Graph/Graph.h"
#include "Worker.h"

void createSpots();
vector<int> getPathBack(int restaurant, vector<int> toRestaurant, Graph graph, int entrance);
void choosePaths(Graph graph, unsigned int maxTime, int dif);
bool sortExperience(Worker* w1, Worker* w2);
void showPaths(vector<Worker*> workers);
void start(vector<Worker*> &workers);


#endif //SEGUNDA_ENTREGA_PATHGENERATOR_H
