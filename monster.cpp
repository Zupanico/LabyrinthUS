/*Fichier: monster.cpp
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "monster.h"

monster::monster()
{
    _actif = true;
    _direction = 0;
    _poursuite = false;
    _range = 6;
    _x = -1;
    _y = -1;
}

monster::~monster()
{
}

int monster::getRange() const
{
    return _range;
}

bool monster::getActif() const
{
    return _actif;
}

void monster::setActif(bool actif)
{
    _actif = actif;
}

void monster::poursuivreJoueur(int direction)
{
    
    int vitesse = 80;

    switch (direction)
    {
    case 1: // Gauche
        _vitesse_x = -vitesse;
        _vitesse_y = 0;
        break;

    case 2: // Bas
        _vitesse_x = 0;
        _vitesse_y = vitesse;
        break;

    case 3: // Haut
        _vitesse_x = 0;
        _vitesse_y = -vitesse;
        break;

    case 4: // Droite
        _vitesse_x = vitesse;
        _vitesse_y = 0;
        break;

    case 0: // Immobile
        _vitesse_x = 0;
        _vitesse_y = 0;
        break;
    }
}

void monster::setPoursuite(bool poursuite)
{
    _poursuite = poursuite;
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
    // choisi une direction aléatoire
    /*static QTimer delay;
    delay.start(2000);
    connect(&delay, &QTimer::timeout, [&]() {
        _direction = rand() % 4 + 1;
        });*/
    _direction = rand() % 4 + 1;
    
    switch (_direction)
	{
		case 1: // Gauche
			_vitesse_x = -50;
			_vitesse_y = 0;
            break;

		case 2: // Bas
			_vitesse_x = 0;
			_vitesse_y = 50;
            break;

        case 3: // Haut
			_vitesse_x = 0;
			_vitesse_y = -50;
            break;

        case 4: // Droite
            _vitesse_x = 50;
            _vitesse_y = 0;
            break;

        case 0: // Immobile
			_vitesse_x = 0;
			_vitesse_y = 0;
            break;
    }
}
