#include <iostream>
#include <vector>
#include "Menu.h"
#include "Utils.h"
#include "../Files/FileReader.h"

struct user{
    int maxTime, experience;
} user;

bool changeReturn(bool& return_menu) {
    string n;
    //cin.ignore(1000, '\n');
    std::cout << endl << endl << "Deseja realizar mais alguma operacao? (S/N)" << endl;
    do {
        std::cout << "Introduza uma opcao:";
        cin.clear();
        cin >> n;
        if ((n != "S" && n != "s" && n != "N" && n != "n") || cin.fail()){
            cin.clear();
            cin.ignore();
            std::cout << "Opcao invalida! Tente Novamente." << endl;
        }
    } while (n != "S" && n != "s" && n != "N" && n != "n");

    if (n == "N" || n == "n")
        return_menu = false;
    return return_menu;
}

int answer(int range){
    unsigned int opt = 0;
    cout << endl;
    do {
        cout << "Introduza uma opcao:"; cin >> opt;
        if (opt < 1 || opt > range || cin.fail()) {
            cin.clear();
            cout << "Opcao invalida! Introduza um numero entre 1 e " << range << "." << endl;
            cin.ignore(1000, '\n');
        }
    } while (opt < 1 || opt > range || cin.fail());

    return opt;
}

void start(){
    //system("cls");
    logo();
    unsigned opt;

    cout << "Escolha uma cidade:" << endl << endl;
    cout << " 1 - Aveiro" << endl;
    cout << " 2 - Ermesinde" << endl;
    cout << " 3 - Fafe" << endl;
    cout << " 4 - Gondomar" << endl;
    cout << " 5 - Maia" << endl;
    cout << " 6 - Porto" << endl;
    cout << " 7 - Viseu" << endl;

    opt = answer(7);

    switch(opt){
        case 1:
            createGraph("Aveiro");
            break;
        case 2:
            createGraph("Ermesinde");
            break;
        case 3:
            createGraph("Fafe");
            break;
        case 4:
            createGraph("Gondomar");
            break;
        case 5:
            createGraph("Maia");
            break;
        case 6:
            createGraph("Porto");
            break;
        case 7:
            createGraph("Viseu");
            break;
    }
}

void mainMenu(){
    bool return_menu = true;
    unsigned int opt;
    do{
        logo();
        cout << " 1 - Escolher Trilho" << endl;
        cout << " 2 - Sair" << endl;

        opt = answer(2);
        cin.ignore(1000, '\n');

        switch(opt){
            case 1:
                start();
                break;
            case 2:
                leave();
                return;
        }

        changeReturn(return_menu);
    } while (return_menu);
}
