// Fichier : fenetre.cpp
// Description : Fichier source de la classe Fenetre
// Date : 2024-02-10
// Auteur : Nicolas Garant

// Inclusion des librairies
// =========================
#include <iostream>
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

void fenetre::afficher() const
{
    for (int column = 0; column < _largeur; ++column)
    {
        cout << _cr;
    }
    
    cout << "\n";

    for (int row = 0; row < _hauteur; ++row)
    {
        // print the left "wall"
        cout << _cr;
        // now print 78 spaces
        for (int column = 0; column < _largeur-2; ++column)
        {
            cout << " ";
        }
        // finally print the right "wall" and a carraige return
        cout << "\u25A0\n";
        // continue the for loop to print the next row
    }

    // Once the loop is done, we can print the bottom wall the same way we printed the top one.
    for (int column = 0; column < _largeur; ++column)
    {
        cout << _cr;
    }
    // now print a carraige return, so we can start printing on the next line
    cout << "\n";
}
