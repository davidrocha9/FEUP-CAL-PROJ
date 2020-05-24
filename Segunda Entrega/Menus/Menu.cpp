#include <iostream>
#include <vector>
#include "Menu.h"
#include "Utils.h"
#include "Worker.h"
#include "pathGenerator.h"
#include "../Files/FileReader.h"
#include "connectivity.h"

Graph fullgraph = createGraph(3, 1);
Graph mediumgraph = createGraph(2, 1);
Graph easygraph = createGraph(1, 1);

void mainMenu(){
    bool return_menu = true;
    unsigned int opt;
    vector<Worker*> workers;

    srand(time(NULL));

    do{
        logo();
        cout << " 1 - Iniciar Percurso" << endl;
        cout << " 2 - Conectividade" << endl;
        cout << " 2 - Sair" << endl;

        opt = answer(1,2);
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
                leave();
                return;
            default:
                break;
        }

        changeReturn(return_menu);
    } while (return_menu);

    leave();
}
