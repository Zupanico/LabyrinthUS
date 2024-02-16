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

