//
// Created by davidrocha on 23/05/20.
//

#include "Path.h"

Path::Path() {

}

double Path::getdurIda() {
    return durIda;
}

double Path::getdurVolta() {
    return durVolta;
}


vector<vector<int>> Path::getPath() {
    return path;
}

void Path::setPath(vector<vector<int>> v) {
    this->path = v;
}

void Path::setDurIda(double dur) {
    this->durIda = dur;
}

void Path::setDurVolta(double dur) {
    this->durVolta = dur;
}
