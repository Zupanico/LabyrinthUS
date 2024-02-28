/*Fichier: portail.h
Description : Fichier d'en-tête de la classe pour le portail
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/


#include "portail.h"

portail::portail(int x, int y)
{
    posX = x;
    posY = y;
}   

portail::~portail() {}

void portail::setPosX(int x)
{
    this->posX = x;
}

void portail::setPosY(int y)
{
    this->posY = y;
}

int portail::getPosX() const
{
    return this->posX;
}

int portail::getPosY() const
{
    return this->posY;
}