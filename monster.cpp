/*Fichier: monster.cpp
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "monster.h"

monster::monster()
{
    _actif = false;
    _direction = 0;
    _poursuite = false;
    _firstInput = false;
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

bool monster::getPoursuite() const
{
    return _poursuite;
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

void monster::patrol()
{
    if (_firstInput == false)
    {
        srand(static_cast<unsigned int>(std::time(nullptr)));
        // Generate a random number between 1 and 2 (gauche ou droite)
        _direction = rand() % 2 + 1;

        _firstInput = true;
    }

    switch (_direction)
	{
		case GAUCHE:
			_vitesse_x = -100;
			_vitesse_y = 0;
		
		case DROITE:
			_vitesse_x = 0;
			_vitesse_y = 100;

		case HAUT:
			_vitesse_x = 0;
			_vitesse_y = -100;

		case BAS:
			_vitesse_x = 0;
			_vitesse_y = 100;

		case 0:
			_vitesse_x = 0;
			_vitesse_y = 0;
	}

}

