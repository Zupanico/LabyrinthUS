/*Fichier: personnage.cpp
Description : Fichier d'en-tête de la classe personnage
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "personnage.h"

// Couleur du personnage
#define RESET "\033[0m"
#define VERT "\033[32m"

personnage::personnage()
{
    _x = 0;
    _y = 0;
}

personnage::~personnage()
{
}

int personnage::getX()
{
    return this->_x;
}

int personnage::getY()
{
    return this->_y;
}

void personnage::setX(int x)
{
    this->_x = x;
}

void personnage::setY(int y)
{
    this->_y = y;
}

void personnage::print(ostream &output) const
{
    cout << VERT << _cr << RESET;
}
