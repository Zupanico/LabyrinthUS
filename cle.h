/*Fichier: cle.h
Description : Fichier d'en-tête de la classe clée
Date : 2024-02-22
Auteur : Nicolas Garant*/

#include <windows.h>
#include <iostream>

#ifndef CLE_H
#define CLE_H

using namespace std;

class cle
{
private:
    int _id;
    string _nom;
    int _x;
    int _y;
    int _couleur;

public:
// Constructeur et destructeur
    cle();
    cle(int id, string nom, int x, int y, int couleur);
    ~cle();

// Accesseurs
    int getId();
    string getNom();
    int getX();
    int getY();
    int getCouleur();

// Méthodes
    void print(ostream &output) const;

};  
#endif