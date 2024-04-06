/* Fichier : fenetre.h
Description : Fichier d'en-tête de la classe fenetre
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#ifndef FENETRE_H
#define FENETRE_H

#include <windows.h>
#include <iostream>
#include <string>

#define MAX_HAUTEUR  100
#define MAX_LARGEUR  100

using namespace std;
class fenetre
{
private:

    int _largeur;
    int _hauteur;

    const char* _ecran[MAX_HAUTEUR][MAX_LARGEUR];
    const char * _cr = "\u25A0";

public:
    // Constructeur et destructeur
    fenetre(int largeur, int hauteur);
    ~fenetre();

    // Accesseurs
    int getLargeur() const;
    int getHauteur() const;

    void setEcran(const char* c, int row, int column);
    const char* getEcran(int row, int column) const;

    // Méthodes
    void print(ostream &output) const;
};

#endif // !FENETRE_H
