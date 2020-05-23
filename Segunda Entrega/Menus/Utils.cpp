#include <iostream>
#include "Utils.h"

using namespace std;

void logo() {
    cout << endl << "--------------------------------------------- " << endl;
    cout << "     ExploreIT: Caminhadas e Patuscadas " << endl;
    cout << "--------------------------------------------- " << endl;
    cout << endl;
}

void leave(){
    cout << "Thank you for using ExploreIT: Caminhadas e Patuscadas!" << endl;
}

int answer(int range, int range2){
    unsigned int opt = 0;
    cout << endl;
    do {
        cout << "Introduza uma opcao:"; cin >> opt;
        if (opt < range || opt > range2 || cin.fail()) {
            cin.clear();
            cout << "Opcao invalida! Introduza um numero entre " << range << " e " << range2 << "." << endl;
            cin.ignore(1000, '\n');
        }
    } while (opt < range || opt > range2 || cin.fail());

    return opt;
}

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