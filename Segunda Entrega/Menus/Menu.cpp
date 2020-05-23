#include <iostream>
#include <vector>
#include "Menu.h"
#include "Utils.h"
#include "Worker.h"
#include "pathGenerator.h"

void mainMenu(){
    bool return_menu = true;
    unsigned int opt;
    vector<Worker*> workers;

    srand(time(NULL));
    createSpots();

    do{
        logo();
        cout << " 1 - Iniciar Trilho" << endl;
        cout << " 2 - Sair" << endl;

        opt = answer(1,2);
        cin.ignore(1000, '\n');

        switch(opt){
            case 1:
                start(workers);
                break;
            case 2:
                leave();
                return;
        }

        changeReturn(return_menu);
    } while (return_menu);

}
