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
    
    int prevPlayerX;
    int prevPlayerY;

    int prevMonsterX;
    int prevMonsterY;

    const wchar_t _cr = L'\u25A0';
    const wchar_t c_mur = L'o';

    vector<mur*> murs;
    
    fenetre f;
    personnage p;
    monster m;

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