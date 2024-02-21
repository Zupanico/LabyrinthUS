// Fichier : main.cpp
// Description : Fichier principal du jeu LabyrinthUS
// Date : 2024-02-10
// Auteur : Nicolas Garant


// Inclusion des librairies
// =========================
#include "fenetre.h"
#include "personnage.h"
#include <string>
#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    fenetre f(80,40);
    f.setEcran('*', 20 ,20);
    f.print(cout);
    game g;
    while (1)
    {
        g.setclavier();
    }
    

    
    return 0;
}
