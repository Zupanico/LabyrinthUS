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
{   // fonction pour imprimer le cadre de la fenetre

    // ligne du haut
    for (int column = 0; column < _largeur; ++column)
    {
        cout << _cr;
    }
    
    cout << "\n";

    for (int row = 0; row < _hauteur; ++row)
    {
        // mur de gauche
        cout << _cr;
        // _largeur-2 espaces
        for (int column = 0; column < _largeur-2; ++column)
        {
            cout << " ";
        }
        // mur de droite + retour de ligne
        cout << "\u25A0\n";
    }

    // ligne du bas
    for (int column = 0; column < _largeur; ++column)
    {
        cout << _cr;
    }
    // fin de ligne
    cout << "\n";
}
