/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-10
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : _f(80, 40)
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
    int touche;
    if (_kbhit()){
        touche = _getch();
        if (touche=='q'){
            cout << "Quitter" << endl;
            exit(0);
        }

        if (touche == 224) // Vérifier si la touche est une fleche
        {
            k = 1; // Passage à l'étape suivante
        }
        else if (k == 1) // Vérifier si nous sommes dans la deuxieme étape
        {
            switch (touche)
            {
            case 72:    // fleche haut
                deplacer(72);
                cout << "Haut" << endl;
                break;
            case 80:    //fleche bas
                deplacer(80);
                cout << "Bas" << endl;
                break;
            case 77:    // fleche droite
                deplacer(77);
                cout << "Droite" << endl;
                break;
            case 75:    // fleche gauche
                deplacer(75);
                cout << "Gauche" << endl;
                break;
            default:
                break;
            }
            k = 0; // Réinitialiser k après avoir traité la touche fléchée
        }
    }
}


void game::afficher() const
{
    // Afficher le jeu
    _f.print(cout);
}

void game::deplacer(int dir)
{
    _f.setEcran(' ', _p.getX(), _p.getY());
    switch(dir)
    {
    case 72: _p.setY(_p.getY()-2);
    case 80: _p.setY(_p.getY()+1);
    case 77: _p.setX(_p.getX()+2);
    case 75: _p.setX(_p.getX()-1);
    }
    _f.setEcran('*', _p.getX(), _p.getY());
    // Déplacer le joueur
    afficher();
}

void game::collision() const
{
    // Gérer les collisions
}

void game::loop()
{
    setclavier();
}