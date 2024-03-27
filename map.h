/*Fichier: map.cpp
Description : Fichier d'en-tête de la classe map
Date : 2024-03-26
Auteur : Nicolas Garant*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>


#ifndef MAP_H
#define MAP_H

using namespace std;

struct coord
{
    int x = 0;
    int y = 0;
};

class map {
    protected:
        vector<coord> _murs;    // vecteur des coordonnées du mur
        coord _cle;     // coordonnées de la clee
        coord _p;       // coordonnées du personnage
        coord _m;       // coordonnées du monstre
        coord _door;    // coordonnées de la porte
        coord _locker;  // coordonnées du locker
        coord _coin;    // coordonnées du coin

    public:

};

#endif