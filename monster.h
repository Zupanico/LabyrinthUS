/*Fichier: monster.h
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#ifndef MONSTER_H
#define MONSTER_H

// Déclaration avancée des classes
class game;
class personnage;

#include <windows.h>
#include <iostream>

#include "personnage.h"
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

#define GAUCHE 1
#define DROITE 2
#define HAUT 3
#define BAS 4

using namespace std;

struct coordonnees
{
    int x;
    int y;
};

class monster : public personnage
{
private:
    bool _actif;
    coordonnees _triggerPoints;
    
    int _direction;
    int _poursuite;
    bool _firstInput; // condition pour que le monstre va dans une direction random au debut de son patrouillage

public:
    monster();
    ~monster();

    bool getActif() const;
    void setActif(bool actif);
    bool getPoursuite() const;

    void addTriggerPoint(int x, int y);
    coordonnees getTriggerPoint() const;

    void patrol();
};
#endif
