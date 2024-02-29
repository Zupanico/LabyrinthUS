/*Fichier: mur.cpp
Description : Fichier d'en-tête de la classe mur
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "mur.h"

mur::mur(int lar, int ho, int x, int y)
{
    _largeur = lar;
    _hauteur = ho;
    _positionX = x;
    _positionY = y;
}

mur::~mur()
{
}

void mur::set_positionX(int lar)
{
    _positionX = lar;
}

void mur::set_positionY(int ho)
{
    _positionY = ho;
}

int mur::get_positionX() const
{
    return _positionX;
}

int mur::get_positionY() const
{
    return _positionY;
}

void mur::set_largeur(int lar)
{
    _largeur = lar;
}

void mur::set_hauteur(int ho)
{
    _hauteur = ho;
}

int mur::get_largeur() const
{
    return _largeur;
}

int mur::get_hauteur() const
{
    return _hauteur;
}
