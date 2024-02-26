/*Fichier: mur.h
Description : Fichier d'en-tête de la classe mur
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>

#ifndef MUR_H
#define MUR_H

using namespace std;

class mur
{
private:
    int _largeur;
    int _hauteur;
    int _positionX;
    int _positionY;

public:
    mur(int lar = 1, int ho = 1, int x = 0, int y = 0);
    ~mur();

    void set_positionX(int lar);
    void set_positionY(int ho);

    int get_positionX() const;
    int get_positionY() const;

    void set_largeur(int lar);
    void set_hauteur(int ho);

    int get_largeur() const;
    int get_hauteur() const;


};
#endif 