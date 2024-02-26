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
            _ecran[i][j] = ' ';
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

void fenetre::setEcran(wchar_t c, int row, int column, string couleur )
{
    if (row >= 0 && row < _hauteur && column >= 0 && column < _largeur) 
    {
        if (c == 'X') // Vérifie si le caractère est celui du joueur
        {
            if (!couleur.empty()) 
            {
                cout << couleur; // Applique la couleur spécifiée pour le joueur
            }
        }
        else
        {
            // Réinitialise la couleur pour tous les autres caractères
            cout << RESET; // Utilise la couleur par défaut du terminal
        }
        _ecran[row][column] = c;
    } 
    else 
    {
        cerr << "Erreur : Coordonnées hors limites !" << endl;
    }
}


wchar_t fenetre::getEcran(int row, int column) const 
{

    if (row >= 0 && row < _hauteur && column >= 0 && column < _largeur) 
    {
        return _ecran[row][column];
    } 
    else 
    {
        cerr << "Erreur : Coordonnées hors limites !" << endl;
        return L' ';
    }
}

void fenetre::print(ostream &output) const
{
    system("cls"); // Efface l'écran avant d'afficher la fenêtre

    // Affiche la ligne supérieure de la fenêtre
    for (int column = 0; column < _largeur; ++column)
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
        for (int column = 0; column < _largeur-2; ++column)
        {
            cout << _ecran[column][row] << " "; // Affiche le contenu de la case
        }

        // Affiche le bord droit de la fenêtre et passe à la ligne suivante
        cout << _cr << " " << endl;
    }

    // Affiche la ligne inférieure de la fenêtre
    for (int column = 0; column < _largeur; ++column)
    {
        cout << _cr << " ";
    }

    cout << "\n"; // Saute une ligne après avoir affiché la ligne inférieure
}
