/*Fichier: cle.cpp
Description : Fichier d'en-tête de la classe cle
Date : 2024-02-22
Auteur : Nicolas Garant*/

#include "cle.h"

cle::cle()
{
    _id = 0;
    _nom = "";
    _x = 0;
    _y = 0;
    _couleur = 0;
}

cle::cle(int id, string nom, int x, int y, int couleur)
{
    _id = id;
    _nom = nom;
    _x = x;
    _y = y;
    _couleur = couleur;
}

cle::~cle()
{
}

int cle::getId()
{
    return this->_id;
}

string cle::getNom()
{
    return _nom;
}

int cle::getX()
{
    return _x;
}

int cle::getY()
{
    return _y;
}

int cle::getCouleur()
{
    return _couleur;
}

void cle::print(ostream &output) const
{
    
}
