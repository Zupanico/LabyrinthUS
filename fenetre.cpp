// Fichier : fenetre.cpp
// Description : Fichier source de la classe Fenetre
// Date : 2024-02-10
// Auteur : Nicolas Garant

// Inclusion des librairies
// =========================
#include "fenetre.h"

using namespace std;

fenetre::fenetre(int largeur, int hauteur)
{
    _largeur = largeur;
    _hauteur = hauteur;
}

fenetre::~fenetre()
{
}

int fenetre::getLargeur() const
{
    return _largeur;
}

int fenetre::getHauteur() const
{
    return _hauteur;
}

void fenetre::print(ostream &output) const
{ // fonction pour imprimer le cadre de la fenetre

    initscr();
    cbreak();
    noecho();

    move(0, 0);
    for (int i = 0; i < _largeur; i++)
    {
        printw("%s", _cr);
    }

    // milieu
    for (int i = 0; i < _hauteur-2; i++){
        mvprintw(i + 1, 0, "%s", _cr);

        mvprintw(i + 1, _largeur, "%s", _cr);
    }

    move(_hauteur - 1, 0);
    // ligne du bas
    for (int i = 0; i < _largeur; i++)
    {
        printw("%s", _cr);
    }

    // Refresh the screen
    refresh();

    // Wait for user input to exit
    getch();

    endwin();

    // End ncurses
}
