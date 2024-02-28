// Fichier : Item.cpp
// Description : Fichier source de la classe item
// Date : 2024-02-24
// Auteur : Evan Frappier

#include "Item.h"

item::item(string nom)
{
	_nom = nom;
}

item::~item()
{
}

string item::getNom()
{
	return _nom;
}
