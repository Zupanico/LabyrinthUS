
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string.h>

using namespace std;

class item
{
protected:
    string _nom;

public:
    // Constructeur et destructeur
    item(string nom);
    ~item();

    // Accesseurs
    string getNom();

};
#endif
