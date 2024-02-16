// Fichier: personnage.h
// Description: Fichier d'en-tête de la classe Personnage
// Date: 2024-02-12
// Auteur: Nicolas Garant

// Inclusion des librairies
// =========================
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

    int getX();
    int getY();

    void setX(int x);
    void setY(int y);

    void print(ostream &output) const;
};

