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
    void addCle(item* item); //index 0 = cle
    void addFlash(item* item); //index 1 = flashlight
    void addCoin(item* item); //index 2 = coin
    void removeItem(int index);
    int inventairePlein();

    void afficherInventaire() const;

    void operator ++();
};
#endif
