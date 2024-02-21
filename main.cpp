// Fichier : main.cpp
// Description : Fichier principal du jeu LabyrinthUS
// Date : 2024-02-10
// Auteur : Nicolas Garant


// Inclusion des librairies
// =========================
#include <string>
#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    game g;
    while (1)
    {
        g.loop();
    }
    

    
    return 0;
}
