/* Fichier : main.cpp
Description : Fichier d'en-tête du main
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/  

#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "game.h"

using namespace std;

void HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO _info; // Structure pour masquer le curseur
    _info.dwSize = 100; // Taille du curseur
    _info.bVisible = FALSE; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_info); // Masquer le curseur
}

int main(int argc, char const *argv[])
{
    system("cls"); // Effacer la console
    HideConsoleCursor(); // Appel de la fonction pour masquer le curseur
    SetConsoleOutputCP(CP_UTF8); // Permet d'afficher les caractères spéciaux
    
    game g;
    g.actualiserMap("map1.txt");
    while (!g.getGameOver())
    {
        g.loop();
    }

    cout << "=================== Game Over!===================" << endl;
    return 0;
}