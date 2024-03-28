/*Fichier: personnage.h
Description : Fichier d'en-tête de la classe personnage
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

// Déclaration avancée des classes
class game;
class monster;

#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;


class personnage
{
protected:
// Déplacement
    int _x;
    int _y;
    int _vitesse_x;
    int _vitesse_y;
    double _time_x;
    double _time_y;
    const double _k = 20;

// Hitbox
    int _largeur = 0;
    int _hauteur = 0;

public:
    
    personnage();
    ~personnage();

    int getX() const;
    int getY() const;
    int getLargeur() const;
    int getHauteur() const;

    void setX(int x);
    void setY(int y);
    void setLargeur(int largeur);
    void setHauteur(int hauteur);

    void setVitesseX(int vitesse);
    void setVitesseY(int vitesse);
    int getVitesseX() const;
    int getVitesseY() const;

    void deplacementX();
    void deplacementY();
};

