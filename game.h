 /*Fichier : game.h
 Description : Fichier d'en-tête de la classe game
 Date : 2024-02-22
 Auteur : Bakayoko Kanvali*/

#ifndef GAME_H
#define GAME_H

// Déclaration avancée des classes
class personnage;
class monster;

#include <iostream>
#include <windows.h>
#include "fenetre.h"
#include "mur.h"
#include <vector>
#include <cstdlib>
#include "monster.h"
#include <conio.h>

using namespace std;

// Définition de la classe game
class game
{
private:
    int _clavier;
    fenetre _f;
    personnage _p;
    monster _m;
    
    const char* _cr = "\u25A0 ";
    const char* _player = "\U0001F468";
    const char* _monster = "\U0001F47E";

    

    vector<mur*> _murs;

public:
    // Constructeur et destructeur
    game();
    ~game();

    // Accesseurs
    int getclavier() const;
    void setclavier();

    // Méthodes
    void afficher() const;
    void deplacerJoueur(int dir);

    void deplacerMonster();
    bool checkTriggerPoints();

    void actualiserMur();

    bool collision(int x, int y);
    void loop();
};
#endif
