// Fichier : game.h
// Description : Fichier d'en-tête de la classe game
// Date : 2024-02-10
// Auteur : Bakayoko Kanvali

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "fenetre.h"
#include "personnage.h"
#include <conio.h>

using namespace std;

// Définition de la classe game
class game
{
private:
    int _clavier;
    fenetre _f;
    personnage _p;
    
public:
    // Constructeur et destructeur
    game();
    ~game();

    // Accesseurs
    int getclavier() const;
    void setclavier();

    // Méthodes
    void afficher() const;
    void deplacer(int dir);
    void collision() const;

    void loop();
};
#endif