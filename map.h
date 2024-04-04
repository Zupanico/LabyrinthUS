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

class maps {
    protected:
        
        vector<coord> _murs;    // vecteur des coordonnées du mur
        coord _cle;     // coordonnées de la clee
        coord _p;       // coordonnées du personnage
        coord _m1;       // coordonnées du monstre1
        vector<coord> _door;    // coordonnées de la porte
        vector<coord> _niveau;    // coordonnées de la zone du prochain niveau
        vector<coord> _locker;  // coordonnées du locker
        coord _coin;    // coordonnées du coin

    public:
    
        maps();
        ~maps();

        void ajouterMur(int x, int y);
        void ajouterPorte(int x, int y);
        void ajouterLocker(int x, int y);
        void ajouterNiveau(int x, int y);

        void afficherCle(int x, int y);
        void afficherM1(int x, int y);

        bool chercherMur(int x, int y);
        bool chercherDoor(int x, int y);
        bool chercherLocker(int x, int y);
        bool chercherNiveau(int x, int y);

        void actualiserMap(string fichier);

        int getSizeNiveau() const;
        coord getNiveau(int i) const;

        int getSizeMurs() const;
        coord getMur(int i) const;

        int getSizeDoor() const;
        coord getDoor(int i) const;

        int getSizeLocker() const;
        coord getLocker(int i) const;

        coord getCle() const;
        coord getM1() const;
};

#endif