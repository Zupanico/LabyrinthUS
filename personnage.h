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
private:
    int _x;
    int _y;
    int _vitesse_x;
    int _vitesse_y;
    double _time_x;
    double _time_y;
    const double _k = 0.2;

    const char *_cr = "\u25A0";
public:
    
    personnage();
    ~personnage();

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    void setVitesseX(int vitesse);
    void setVitesseY(int vitesse);
    int getVitesseX() const;
    int getVitesseY() const;



    void deplacementX();
    void deplacementY();

    void print(ostream &output) const;
};

