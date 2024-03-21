/*Fichier: monstre1.cpp
Description : Fichier source de la classe monstre1
Date : 2024-03-14
Auteur : Evan Frappier*/

#include "monstre1.h"

monstre1::monstre1()
{
	_actif = true;
}

monstre1::~monstre1()
{
}

void monstre1::patrouiller()
{
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

void monstre1::poursuivre(coordonnees positionJoueur)
{

	while (getX() != positionJoueur.x && getY() != positionJoueur.y)
	{
		if (positionJoueur.x < getX())
		{
			_vitesse_x = -150;
		}
		else if (positionJoueur.x > getX())
		{
			_vitesse_x = 150;
		}

		if (positionJoueur.y < getY())
		{
			_vitesse_y = -150;
		}
		else if (positionJoueur.y > getY())
		{
			_vitesse_y = 150;
		}
	}
	
}

