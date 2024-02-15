/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-10
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() 
{
    _clavier = 0;
}

game::~game() 
{
    // Destructeur
}

int game::getclavier() const
{
    return _clavier;
}

void game::setclavier()
{
    static int k = 0; // Déclarer k en tant que variable statique pour qu'elle conserve sa valeur entre les appels

    int ch = _getch();
    if (ch == 224) // Vérifier si la touche est une fleche
    {
        k = 1; // Passage à l'étape suivante
    }
    else if (k == 1) // Vérifier si nous sommes dans la deuxieme étape
    {
        if (ch == 72) // Touche Haut
        {
            cout << "Haut" << endl;
        }
        else if (ch == 80) // Touche Bas
        {
            cout << "Bas" << endl;
        }
        else if (ch == 77) // Touche Droite
        {
            cout << "Droite" << endl;
        }
        else if (ch == 75) // Touche Gauche
        {
            cout << "Gauche" << endl;
        }

        k = 0; // Réinitialiser k après avoir traité la touche fléchée
    }
}


void game::afficher() const
{
    // Afficher le jeu
}

void game::deplacer() const
{
    // Déplacer le joueur
}

void game::collision() const
{
    // Gérer les collisions
}