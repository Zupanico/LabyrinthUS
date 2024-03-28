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
     _direction = rand() % 4 + 1;
    // choisi une direction aléatoire
    if (_firstInput == false)
    {
        // Generate a random number between 1 and 2 (gauche ou droite)
       
        
        _firstInput = true;
    }
    

    switch (_direction)
	{
		case 1: // Gauche
			_vitesse_x = -100;
			_vitesse_y = 0;
            break;
		
		case 2: // Bas
			_vitesse_x = 0;
			_vitesse_y = 100;
            break;

        case 3: // Haut
			_vitesse_x = 0;
			_vitesse_y = -100;
            break;

        case 4: // Droite
            _vitesse_x = 100;
            _vitesse_y = 0;
            break;

        case 0: // Immobile
			_vitesse_x = 0;
			_vitesse_y = 0;
            break;
    }
}

