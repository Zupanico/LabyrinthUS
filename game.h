 /*Fichier : game.h
 Description : Fichier d'en-tête de la classe game
 Date : 2024-02-22
 Auteur : Bakayoko Kanvali*/

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "fenetre.h"
#include "mur.h"
#include <vector>
#include "personnage.h"
#include <conio.h>

using namespace std;

// Définition de la classe game
class game
{
private:
    int _clavier;
    
    int prevPlayerX;
    int prevPlayerY;

    const wchar_t _cr = L'\u25A0';

    fenetre f;
    vector<mur*> murs;
    personnage p;

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
    void collision();


    void loop();
};
#endif