/*Fichier: mur.cpp
Description : Fichier d'en-tête de la classe mur
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "mur.h"


mur::mur()
{

}

mur::~mur()
{
}

void mur::ajouterMur(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _murs.push_back(c);
}

bool mur::chercherMur(int x, int y)
{
    for (int i = 0; i < _murs.size(); i++)
    {
        if (_murs[i].x == x && _murs[i].y == y)
        {
            return true;
        }
    }
    return false;
}

void mur::actualiserMur(string fichier)
{
    for (int i = 0; i < _murs.size(); i++)
    {
        _murs.pop_back();
    }

    ifstream fichierMur;
    int x = 0;
    int y = 0;
    fichierMur.open(fichier);
    if (fichierMur.is_open())
    {
        while (!fichierMur.eof())
        {
            char c;
            fichierMur.get(c);
            if (c == '\n')
            {
                y++;
                x = 0;
            }
            else
            {
                if (c == '#')
                {
                    ajouterMur(x, y);
                }
                x++;
            }
        }
        fichierMur.close();
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier" << endl;
    }
}

int mur::getSize() const
{
    return _murs.size();
}

coord mur::getMur(int i) const
{
    return _murs[i];
}