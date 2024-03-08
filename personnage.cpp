/*Fichier: personnage.cpp
Description : Fichier d'en-tête de la classe personnage
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "personnage.h"

personnage::personnage()
{
    _x = 0;
    _y = 0;
    _vitesse_x = 0;
    _vitesse_y = 0;
    _time_x = 0;
    _time_y = 0;
}

personnage::~personnage()
{
}

int personnage::getX() const
{
    return this->_x;
}

int personnage::getY() const
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
    cout << "\033[31m" << _cr << "\033[0m";
}

void personnage::deplacementX()
{
    if (_vitesse_x > 0)
    {
        if ((((double) clock()) / CLOCKS_PER_SEC) - _time_x >= _k/_vitesse_x)
        {
            _x += 1;
            _time_x = ((double) clock()) / CLOCKS_PER_SEC;
        }
    } else if (_vitesse_x < 0)
    {
        if ((((double) clock()) / CLOCKS_PER_SEC) - _time_x >= _k/(-_vitesse_x))
        {
            _x -= 1;
            _time_x = ((double) clock()) / CLOCKS_PER_SEC;
        }
    }
}

void personnage::deplacementY()
{
    if (_vitesse_y > 0)
    {
        if ((((double) clock()) / CLOCKS_PER_SEC) - _time_y >= _k/_vitesse_y)
        {
            _y += 1;
            _time_y = ((double) clock()) / CLOCKS_PER_SEC;
        }
    }else if (_vitesse_y < 0)
    {
        if ((((double) clock()) / CLOCKS_PER_SEC) - _time_y >= _k/(-_vitesse_y))
        {
            _y -= 1;
            _time_y = ((double) clock()) / CLOCKS_PER_SEC;
        }
    }
}


void personnage::setVitesseX(int vitesse)
{
    _vitesse_x = vitesse;
}

void personnage::setVitesseY(int vitesse)
{
    _vitesse_y = vitesse;
}

int personnage::getVitesseX() const
{
    return _vitesse_x;
}

int personnage::getVitesseY() const
{
    return _vitesse_y;
}
