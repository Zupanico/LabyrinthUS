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
#include <conio.h>

#include <cmath>
#include <algorithm>
#include <random>

#include "fenetre.h"
#include "mur.h"
#include "monster.h"
#include "portail.h"
#include <vector>
#include <cstdlib>

using namespace std;

// Définition de la classe game
class game
{
private:
    int _clavier;

    int prevPlayerX;
    int prevPlayerY;

    vector<int> prevMonsterX;
    vector<int> prevMonsterY;

    vector<monster*> monstres;
    vector<portail*>_portails;
    vector<mur*> _murs;

    fenetre _f;
    personnage _p;
    monster _m;
    portail _po;
    
    const char* _cr = "\u25A0";

public:
    // Constructeur et destructeur
    game();
    ~game();

    // Accesseurs
    int getclavier() const;
    void setclavier();

    // Méthodes
    void Ajouter_Mur();
    void Inserer_Murs();

    void Ajouter_Portail();
    void Inserer_Portail();

    void Ajouter_Monstre(int x = 10, int y = 10);
    void Inserer_Monstre();

    bool collision(int x, int y);
    
    void deplacer_monstre(int index = 0);
    void deplacer_joueur(int dir);
    
    bool Mur_Entre_Les_Deux(int x0 , int y0, int x1, int y1, const fenetre& f);
    void actualiserMur();

    void afficher() const;
    void loop();
};
#endif
