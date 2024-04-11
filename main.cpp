/* Fichier : main.cpp
Description : Fichier d'en-tête du main
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/  

#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "game.h"
#include <QApplication>
#include <QTimer>

using namespace std;

void HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO _info; // Structure pour masquer le curseur
    _info.dwSize = 100; // Taille du curseur
    _info.bVisible = FALSE; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_info); // Masquer le curseur
}

int main(int argc, char **argv)
{
    system("cls");
    HideConsoleCursor(); // Appel de la fonction pour masquer le curseur
    SetConsoleOutputCP(CP_UTF8);

    game g(argc, argv);


    g.loop();


    cout << "=================== Game Over!===================" << endl;
    exit(0);
    return g.exec();
}
