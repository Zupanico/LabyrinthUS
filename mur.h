/*Fichier: mur.h
Description : Fichier d'en-tête de la classe mur
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef MUR_H
#define MUR_H

using namespace std;

struct coord
{
    int x;
    int y;
};

class mur
{
private:
    vector<coord> _murs;

public:

    mur();
    ~mur();

    void ajouterMur(int x, int y);
    bool chercherMur(int x, int y);
    void actualiserMur(string fichier);

    int getSize() const;
    coord getMur(int i) const;

};
#endif 