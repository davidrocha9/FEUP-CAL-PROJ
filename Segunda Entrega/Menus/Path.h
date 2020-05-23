//
// Created by davidrocha on 23/05/20.
//

#ifndef SEGUNDA_ENTREGA_PATH_H
#define SEGUNDA_ENTREGA_PATH_H
#include <vector>

using namespace std;

class Path {
    vector<vector<int>> path;
    double durIda, durVolta;
public:
    Path();
    vector<vector<int>> getPath();
    double getdurIda();
    double getdurVolta();

    void setPath(vector<vector<int>> v);
    void setDurIda(double dur);
    void setDurVolta(double dur);
};


#endif //SEGUNDA_ENTREGA_PATH_H
