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

using namespace std;


class personnage
{
private:
    int _x = 0;
    int _y = 0;
    const char *_cr = "\u25A0";
public:
    
    personnage();
    ~personnage();

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    void print(ostream &output) const;
};

