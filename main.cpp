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
#include <ncurses.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // Initialize ncurses
    fenetre f(80,24);
    
    initscr();

    // Clear the screen
    clear();
    f.print(cout);

    personnage p;
    p.setY(10);
    p.setX(10);
    p.print(cout);

    endwin();
    return 0;
}
