/*Fichier: monster.cpp
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "monster.h"

monster::monster()
{
}

monster::~monster()
{
    
}

bool monster::getActif() const
{
    return _actif;
}

void monster::setActif(bool actif)
{
    _actif = actif;
}

void monster::addTriggerPoint(int x, int y)
{
    _triggerPoints.x = x;
    _triggerPoints.y = y;
}

coordonnees monster::getTriggerPoint() const
{
    return _triggerPoints;
}


//Pathfinding

void monster::setCase(int debut_x, int debut_y, int fin_x, int fin_y)
{
    _debutCase = {debut_x, debut_y};
    _currentCase = _debutCase;
    _finCase = {fin_x, fin_y};
}

