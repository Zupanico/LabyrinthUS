/*Fichier: monstre1.h
Description : Fichier d'en-t�te de la classe monstre1
Date : 2024-03-14
Auteur : Evan Frappier*/

#ifndef MONSTRE1_H
#define MONSTRE1_H

#define GAUCHE 1
#define DROITE 2
#define HAUT 3
#define BAS 4

#include "monster.h"

using namespace std;

class monstre1 : public monster
{
private:

	const double _k = 25;

public:

	monstre1();
	~monstre1();

	void patrouiller();
	void poursuivre(coordonnees positionJoueur);
	void observer();

};

#endif