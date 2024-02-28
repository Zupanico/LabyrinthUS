/* Fichier : main.cpp
Description : Fichier d'en-tête du main
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/


#include "game.h"
#include <windows.h>

using namespace std;

// Définition de la fonction HideConsoleCursor
void HideConsoleCursor() 
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // Cache le curseur du terminal
}

int main(int argc, char const *argv[])
{
    HideConsoleCursor(); // Cache le curseur du terminal
    SetConsoleOutputCP(CP_UTF8); // Permet d'afficher les caractères spéciaux

    game g;
    g.actualiserMur();
    
    system("cls"); // Efface l'écran avant d'afficher la fenêtre de jeu
    while (true)
    {
        g.loop(); // Mettre à jour et afficher uniquement les parties de l'écran qui changent
    } 
    return 0;
}

