// Fichier : Inventaire.h
// Description : Fichier d'en-t�te de la classe inventaire
// Date : 2024-02-24
// Auteur : Evan Frappier


#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#define MAX_ITEMS 4

#include <iostream>
#include <string.h>
#include "Item.h"

using namespace std;

class inventaire
{
private:
    item* _inventaire[MAX_ITEMS];
    int _selectedSlot;
    int _taille;
public:
    // Constructeur et destructeur
    inventaire();
    ~inventaire();

    //Accesseurs
    int getCapacite();

    // Methodes
    void addItem(item* item);
    void selectSlot(int index);
    int inventairePlein();

    void afficherInventaire() const;

    void operator ++();
};
#endif
