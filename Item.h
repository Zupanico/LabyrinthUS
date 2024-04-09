// Fichier : Item.h
// Description : Fichier d'en-t�te de la classe item
// Date : 2024-02-24
// Auteur : Evan Frappier

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string.h>
#include "Position.h"

using namespace std;

class item
{
protected:
    string _nom;
    Position _position;

public:
    // Constructeur et destructeur
    item(string nom);
    ~item();

    // Accesseurs
    string getNom();

    Position getPosition() const; //
    void setPosition(Position position);
    
};
#endif