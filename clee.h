/*Fichier: clee.h
Description : Fichier d'en-tête de la classe clée
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>

#ifndef CLEE_H
#define CLEE_H

using namespace std;

class clee
{
private:
    char clee_correspondante[4];
public:
    clee();
    ~clee();
};  
#endif