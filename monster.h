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
    

public:
    monster();
    ~monster();

    bool getActif() const;
    void setActif(bool actif);

    void addTriggerPoint(int x, int y);
    coordonnees getTriggerPoint() const;
};
#endif