/*Fichier: portail.h
Description : Fichier d'en-tête de la classe pour le portail
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>

#ifndef PORTAIL_H
#define PORTAIL_H

using namespace std;

class portail
{
private:

    int posX;
    int posY;

    const char *_P = "P";
    
public:
    portail(int x, int y);
    ~portail();

    void setPosX(int x);
    void setPosY(int y);

    int getPosX() const;
    int getPosY() const;
};
#endif