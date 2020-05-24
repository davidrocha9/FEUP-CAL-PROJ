#include <iostream>
#include <vector>
#include "Menu.h"
#include "Utils.h"
#include "Worker.h"
#include "pathGenerator.h"
#include "../Files/FileReader.h"
#include "connectivity.h"
#include "timer.h"
#include "../Graph/GraphViewer.h"

Graph fullgraph = createGraph(3, 1);
Graph mediumgraph = createGraph(2, 1);
Graph easygraph = createGraph(1, 1);

void mainMenu(){
    bool return_menu = true;
    unsigned int opt;
    vector<Worker*> workers;

    vector<int> v;
    graphDisplay gd(fullgraph, 1920, 1080);

    srand(time(NULL));
    do{
        logo();
        cout << " 1 - Iniciar Percurso" << endl;
        cout << " 2 - Conectividade" << endl;
        cout << " 3 - Visualizar Mapa" << endl << endl;
        cout << " 4 - Sair" << endl;

        opt = answer(1,4);
        cin.ignore(1000, '\n');

        unsigned int randOrNot, difficulty;

        switch(opt){
            case 1:
                logo();
                cout << "Escolha a região rural pretendida:" << endl << endl;
                cout << "[1] Predefinida" << endl;
                cout << "[2] Aleatória" << endl;
                randOrNot = answer(1,2);
                start(workers, randOrNot);
                break;
            case 2:
                logo();
                cout << "Dificuldade Maxima:"; difficulty = answer(1,3);
                cout << endl;
                switch(difficulty){
                    case 1:
                        checkConnectivity(easygraph);
                        break;
                    case 2:
                        checkConnectivity(mediumgraph);
                        break;
                    case 3:
                        checkConnectivity(fullgraph);
                        break;
                }
                break;
            case 3:
                gd.showConnectivity(v);
                getchar();
                break;
            case 4:
                leave();
                return;
            default:
                break;
        }

        changeReturn(return_menu);
    } while (return_menu);

    leave();
}
