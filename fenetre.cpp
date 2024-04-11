/* Fichier : fenetre.cpp
Description : Fichier d'en-tête de la classe fenetre
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/


#include "fenetre.h"

using namespace std;

fenetre::fenetre(int largeur, int hauteur)
{
    _largeur = largeur;
    _hauteur = hauteur;

    for (int i = 0; i < _largeur; i++)
    {
        for (int j = 0; j<_hauteur; j++)
        {
            _ecran[i][j] = "  ";
        }
    }
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

void fenetre::resetEcran()
{
    for (int i = 0; i < _largeur; i++)
    {
        for (int j = 0; j<_hauteur; j++)
        {
            _ecran[i][j] = "  ";
        }
    }
}

void fenetre::setEcran(const char* c, int row, int column)
{
    if (row >= 0 && row < _largeur && column >= 0 && column < _hauteur)
    {
        _ecran[row][column] = c;
    }
}

const char* fenetre::getEcran(int row, int column) const 
{

    if (row >= 0 && row < _largeur && column >= 0 && column < _hauteur)
    {
        return _ecran[row][column];
    }
    else
    {
        return " ";
    }
}

void fenetre::print(ostream &output) const
{

    // Affiche la ligne supérieure de la fenêtre
    for (int column = 0; column < _largeur + 2; ++column)
    {
        cout << _cr << " ";
    }

    cout << endl; // Saute une ligne après avoir affiché la ligne supérieure

    // Affiche le contenu de la fenêtre
    for (int row = 0; row < _hauteur; ++row)
    {
        // Affiche le bord gauche de la fenêtre
        cout << _cr << " ";

        // Affiche le contenu de chaque case de la ligne de la fenêtre
        for (int column = 0; column < _largeur; ++column)
        {
            cout << _ecran[column][row]; // Affiche le contenu de la case
        }

        // Affiche le bord droit de la fenêtre et passe à la ligne suivante
        cout << _cr << " " << endl;
    }

    // Affiche la ligne inférieure de la fenêtre
    for (int column = 0; column < _largeur + 2; ++column)
    {
        cout << _cr << " ";
    }

    cout << "\n"; // Saute une ligne après avoir affiché la ligne inférieure
}
