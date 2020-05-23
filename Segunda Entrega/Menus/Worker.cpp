//
// Created by davidrocha on 22/05/20.
//

#include "Worker.h"

Worker::Worker(string name, unsigned int exp) {
    this->name = name;
    this->exp = exp;
    vector<vector<int>> v;
    this->path = v;
}

string Worker::getName() {
    return name;
}

unsigned int Worker::getExp() {
    return exp;
}

vector<vector<int>> Worker::getPath() {
    return path;
}

void Worker::setPath(vector<vector<int>> path) {
    this->path = path;
}
