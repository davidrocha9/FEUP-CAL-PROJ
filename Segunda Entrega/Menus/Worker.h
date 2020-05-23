//
// Created by davidrocha on 22/05/20.
//

#ifndef SEGUNDA_ENTREGA_WORKER_H
#define SEGUNDA_ENTREGA_WORKER_H

#include <string>
#include <vector>

using namespace std;

class Worker {
    string name;
    unsigned int exp;
    vector<vector<int>> path;
public:
    Worker(string name, unsigned int exp);

    string getName();
    unsigned int getExp();
    vector<vector<int>> getPath();

    void setPath(vector<vector<int>> path);
};


#endif //SEGUNDA_ENTREGA_WORKER_H
