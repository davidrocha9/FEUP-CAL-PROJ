//
// Created by davidrocha on 23/05/20.
//

#include <iostream>
#include "pathGenerator.h"
#include "../Algorithms/dijkstra.h"
#include "Utils.h"
#include "../Graph/GraphViewer.h"
#include "../Files/FileReader.h"
#include "Path.h"
#include "math.h"
#include "time.h"
#include "timer.h"

vector<int> restaurants;
vector<int> entrances;
Graph fullGraph;
Graph mediumGraph;
Graph easyGraph;

vector<Path> easyPaths;
vector<Path> normalPaths;
vector<Path> hardPaths;

vector<vector<vector<Path>>> combinations;

unsigned int startPoint, endPoint, restaurantID;

unsigned int maxTime;

// Inicia os pontos que sao restaurantes/entradas/saidas
void createSpots(){
    //Restaurantes
    for (auto x: fullGraph.getVertexSet()){
        if (x->getType() == "restaurant\r")
            restaurants.push_back(x->getId());
    }

    // Entradas/saidas
    for (auto x: fullGraph.getVertexSet()){
        if (x->getType() == "entrance\r")
            entrances.push_back(x->getId());
    }

}

// Calcula o caminho desde o restaurante ate uma saida
vector<vector<int>> getPathBack(int restaurant, vector<int> toRestaurant, Graph graph, int entrance) {
    vector<int> pathBack, visited;
    vector<vector<int>> paths;
    // inicia um vetor com pontos ja visitados, para que o algoritmo ignore estes pontos e tente maximizar o nr de pontos percorridos
    for (auto x: toRestaurant) {
        if (graph.findVertex(x)->getType() != "restaurant\r" && graph.findVertex(x)->getType() != "entrance\r")
            visited.push_back(x);
    }

    // calcula os trilhos possiveis desde o restaurante ate as saidas
    for (int & exit : entrances) {
        pathBack = dijkstraShortestPath(graph, restaurant, exit, visited);
        if (!pathBack.empty()) {
            paths.push_back(pathBack);
            break;
        }
    }

    return paths;
}

// Gera caminhos
void choosePaths(Graph graph, unsigned int maxTime, int dif) {
    vector<int> visited;
    vector<int> toRestaurant;
    vector<vector<int>> fromRestaurant;
    vector<vector<int>> temp;
    vector<vector<vector<int>>> res;
    vector<Path> candidates, final;

    //caso n de para voltar
    vector<vector<int>> ida;

    bool found;
    // calcula caminhos possiveis entre todas as entradas e restaurantes
    for (int &entrance : entrances) {
        found = false;
        for (int &restaurant : restaurants) {
            toRestaurant.clear();
            toRestaurant = dijkstraShortestPath(graph, entrance, restaurant, visited);
            // caso encontre um caminho valido de uma entrada ate ao restaurante, começa a calcular o caminho desse restaurante ate uma saida
            if (!toRestaurant.empty()) {
                fromRestaurant = getPathBack(restaurant, toRestaurant, graph, entrance);
                ida.push_back(toRestaurant);
                // caso os caminho calculado seja valido é adicionado a um vetor temporario de trilhos possiveis
                if (!fromRestaurant.empty()) {
                    temp.clear();
                    for (auto x: fromRestaurant) {
                        temp.push_back(toRestaurant);
                        temp.push_back(x);
                    }
                    res.push_back(temp);
                    found = true;
                    break;
                }
            }
        }
    }

    // caso n seja encontrado um caminho do restaurante para outra saida, o trabalhador volta para o ponto inicial
    if (!found) {
        temp.clear();
        temp.push_back(ida.at(0));
        temp.push_back(ida.at(0));
        res.push_back(temp);
    }

    Path path = Path();
    // calcula as duracoes dos trilhos
    double tempoIda = 0.0, tempoVolta = 0.0;
    for (int a = 0; a < res.size(); a++){
        for (int x = 0; x < res.at(a).size(); x++) {
            vector<int> trilhoManhaTarde = res.at(a).at(x);
            for (int y = 0; y < trilhoManhaTarde.size() - 1; y++) {
                vector<Edge> adj = graph.findVertex(trilhoManhaTarde.at(y))->getAdj();
                for (auto z :adj) {
                    if (z.getDestID() == graph.findVertex(trilhoManhaTarde.at(y + 1))->getId()) {
                        //cout << graph.findVertex(trilhoManhaTarde.at(y))->getId() << " " << graph.findVertex(trilhoManhaTarde.at(y+1))->getId() << endl;
                        switch(x){
                            case 0:
                                tempoIda += z.getDur();
                                break;
                            case 1:
                                tempoVolta += z.getDur();
                                break;
                        }
                        break;
                    }
                }
            }
        }

        path.setDurIda(tempoIda);
        path.setDurVolta(tempoVolta);
        path.setPath(res.at(a));
        candidates.push_back(path);

        tempoIda = 0.0;
        tempoVolta = 0.0;
    }

    double afterLunchTime = maxTime - 1.0 - 5.0;

    // filtra os caminhos possiveis de acordo com as restricoes de tempo
    for (auto x: candidates){
        if (x.getdurIda() < 5.0*60.0) {
            if (x.getdurVolta() < afterLunchTime*60.0){
                switch(dif){
                    case 1:
                        easyPaths.push_back(x);
                        break;
                    case 2:
                        easyPaths.push_back(x);
                        normalPaths.push_back(x);
                        break;
                    case 3:
                        easyPaths.push_back(x);
                        normalPaths.push_back(x);
                        hardPaths.push_back(x);
                        break;
                }
            }
        }
    }
}

// funcao sort consoante a experiencia
bool sortExperience(Worker* w1, Worker* w2){
    return w1->getExp() < w2->getExp();
}

// mostra os paths dos trabalhadores
void showPaths(vector<Worker*> workers){
    char n;
    cout << endl << "Pretende visualizar algum trilho?" << endl;

    do {
        std::cout << "Introduza uma opcao (S/N):";
        cin.clear();
        cin >> n;
        if ((n != 'S' && n != 's' && n != 'N' && n != 'n') || cin.fail()){
            cin.clear();
            cin.ignore();
            std::cout << "Opcao invalida! Tente Novamente." << endl;
        }
    } while (n != 'S' && n != 's' && n != 'N' && n != 'n');

    if (n == 's'){
        unsigned int opt;
        cout << endl << "Selecione o trilho que pretende visualizar:" << endl << endl;

        for (int x = 0; x < workers.size(); x++){
            cout << "[" << x+1 << "] " << workers.at(x)->getName() << endl;
        }
        opt = answer(1, workers.size());

        graphDisplay gd(fullGraph, 1920, 1080);
        gd.show(workers.at(opt-1)->getPath());
        getchar();

        graphDisplay gd2(fullGraph, 1920, 1080);
        gd2.show(workers.at(0)->getPath());
        getchar();

        graphDisplay gd3(fullGraph, 1920, 1080);
        gd2.show(workers.at(1)->getPath());
        getchar();

    }
    else return;
}

// funcao sort para ver se o caminho e valido de acordo com as restricoes
bool checkPath(Path path){
    return path.getPath().at(0).back() == restaurantID && path.getPath().at(1).back() == endPoint;
}

// filtra os caminhos, excluindo os invalidos
void filterPaths(Path p){
    vector<vector<int>> path = p.getPath();

    vector<Path> v1, v2, v3;

    vector<Path> temp;
    for (auto x: easyPaths){
        if (checkPath(x))
            temp.push_back(x);
    }
    v1 = temp;

    temp.clear();
    for (auto x: normalPaths){
        if (checkPath(x))
            temp.push_back(x);
    }
    v2 = temp;

    temp.clear();
    for (auto x: hardPaths){
        if (checkPath(x))
            temp.push_back(x);
    }
    v3 = temp;

    vector<vector<Path>> v4;
    v4.clear();
    v4.push_back(v1);
    v4.push_back(v2);
    v4.push_back(v3);

    if (!v1.empty() && !v2.empty() && !v3.empty())
        combinations.push_back(v4);
}

// funcao sort
bool sortCombinations(vector<vector<Path>> c1, vector<vector<Path>> c2){
    return ((c1.at(0).size() * c1.at(1).size() * c1.at(2).size()) < (c2.at(0).size() * c2.at(1).size() * c2.at(2).size()));
}

// funcao para criar caminhos
void start(vector<Worker*> &workers, unsigned int randOrNot) {//, vector<vector<vector<int>>> &workersPaths) {
    //system("cls");
    logo();
    unsigned opt, exp;
    string name;

    Timer timer;
    timer.start();

    fullGraph = createGraph(3, randOrNot);
    mediumGraph = createGraph(2, randOrNot);
    easyGraph = createGraph(1, randOrNot);

    createSpots();

    cout << "Duracao Maxima do Percurso (Min. 5h, Max 12h)";
    maxTime = answer(5, 12);
    cout << endl << "Insira o numero total de pessoas no grupo (Max. 25 pessoas)";
    opt = answer(1, 25);
    cout << endl;

    for (size_t x = 0; x < opt; x++) {
        cout << "Pessoa #" << x + 1 << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nome:";
        getline(cin, name);
        cout << "Experiencia (1 a 3)";
        exp = answer(1, 3);
        cout << endl;

        workers.push_back(new Worker(name, exp));
    }

    cout << endl << "A calcular trilhos... por favor aguarde..." << endl;

    sort(workers.begin(), workers.end(), sortExperience);

    vector<vector<int>> temp;

    choosePaths(easyGraph, maxTime, 1);

    if (easyPaths.empty()) {
        for (auto x: workers) {
            if (x->getExp() == 1) {
                cout << "Impossivel gerar trilho!" << endl;
                return;
            }
        }
    }
    choosePaths(mediumGraph, maxTime, 2);
    if (normalPaths.empty()) {
        for (auto x: workers) {
            if (x->getExp() == 2) {
                cout << "Impossivel gerar trilho!" << endl;
                return;
            }
        }
    }
    choosePaths(fullGraph, maxTime, 3);
    if (hardPaths.empty()) {
        for (auto x: workers) {
            if (x->getExp() == 3) {
                cout << "Impossivel gerar trilho!" << endl;
                return;
            }
        }
    }

    vector<Path> vTemp = easyPaths;
    // calcular restaurantes e pontos possiveis
    vector<vector<int>> pares;
    for (auto x: vTemp) {
        vector<int> par;
        par.clear();
        par.push_back(x.getPath().front().back());
        par.push_back(x.getPath().back().back());
        pares.push_back(par);
    }

    // filtra os caminhos de acordo com o restaurante e a saida escolhidos
    bool impossible = true;
    while (impossible) {
        int chosenOne = rand() % (pares.size() - 1);
        restaurantID = pares.at(chosenOne - 1).front();
        endPoint = pares.at(chosenOne - 1).back();

        for (auto x: vTemp) {
            filterPaths(x);
        }

        if (!combinations.empty())
            impossible = false;
    }

    int w1 = 0, w2 = 0, w3 = 0;
    for (auto x: workers){
        switch(x->getExp()){
            case 1:
                w1++;
                break;
            case 2:
                w2++;
                break;
            case 3:
                w3++;
                break;
        }
    }

    // depois de filtrados os caminhos, escolhe os resultados com maior volume de trilhos diferentes
    sort(combinations.begin(), combinations.end(), sortCombinations);
    vector<vector<vector<Path>>> combinations2;
    for (auto x: combinations){
        if (x.at(0).size() >= w1)
            if (x.at(1).size() >= w2)
                if (x.at(2).size() >= w3)
                    combinations2.push_back(x);
    }

    combinations = combinations2;

    easyPaths = combinations.at(0).at(0);
    normalPaths = combinations.at(0).at(1);
    hardPaths = combinations.at(0).at(2);

    // atribui a todos os trabalhadores os trilhos calculados
    int index;
    for (size_t x = 0; x < workers.size(); x++){
        switch (workers.at(x)->getExp()) {
            case 1:
                index = rand() % (easyPaths.size() - 1);
                temp = easyPaths.at(index).getPath();
                break;
            case 2:
                index = rand() % (normalPaths.size() - 1);
                temp = normalPaths.at(index).getPath();
                break;
            case 3:
                index = rand() % (hardPaths.size() - 1);
                temp = hardPaths.at(index).getPath();
                break;
        }
        workers.at(x)->setPath(temp);
    }


    timer.stop();

    cout << "Tempo Gasto:" << timer.elapsedSeconds() << endl;

    showPaths(workers);
}