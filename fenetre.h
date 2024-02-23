/* Fichier : fenetre.h
Description : Fichier d'en-tête de la classe fenetre
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>

#define MAX_HAUTEUR  100
#define MAX_LARGEUR  100

using namespace std;
class fenetre
{
private:

    int _largeur;
    int _hauteur;

    char ecran[MAX_HAUTEUR][MAX_LARGEUR]; 
    const char * _cr = "\u25A0";

public:
    // Constructeur et destructeur
    fenetre(int largeur, int hauteur);
    ~fenetre();

    // Accesseurs
    int getLargeur() const;
    int getHauteur() const;

    void setEcran(wchar_t c, int row, int column);
    wchar_t getEcran(int row, int column) const;

    // Méthodes
    void print(ostream &output) const;
};
