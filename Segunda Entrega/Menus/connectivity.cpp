//
// Created by davidrocha on 24/05/20.
//

#include "connectivity.h"
#include "../Algorithms/dfs.h"
#include "../Graph/GraphViewer.h"

using namespace std;

// Menu de Conectividade, constroi um grafo com base no algoritmo dfs
void checkConnectivity(Graph graph) {
    cout << "Insira o ID do ponto de inicio" << endl;
    unsigned int opt = 0;
    bool done = true;
    do {
        cout << "Introduza uma opcao:"; cin >> opt;
        if (cin.fail()) {
            cin.clear();
            cout << "Opcao invalida! Nao existe nenhum ponto com este ID!" << endl;
            cin.ignore(1000, '\n');
        }
        else if (graph.findVertex(opt) == NULL){
            cin.clear();
            cout << "Opcao invalida! Nao existe nenhum ponto com este ID!" << endl;
            cin.ignore(1000, '\n');
        }
        else done = false;
    } while (done);

    vector<int> res = dfs(graph, opt);

    graphDisplay gd(graph, 1920, 1080);
    gd.showConnectivity(res);
    getchar();
}
