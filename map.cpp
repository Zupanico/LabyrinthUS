



#include "map.h"

map::map()
{
}

map::~map()
{
}

void map::ajouterMur(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _murs.push_back(c);
}

void map::ajouterPorte(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _door.push_back(c);
}

void map::afficherCle(int x, int y)
{
    _cle.x = x;
    _cle.y = y;
}

bool map::chercherMur(int x, int y)
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

void map::actualiserMap(string fichier)
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
                else if (c == 'P')
                {
                    ajouterPorte(x, y);
                }
                else if (c == 'K')
                {
                    afficherCle(x, y);
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

int map::getSizeMurs() const
{
    return _murs.size();
}

coord map::getMur(int i) const
{
    return _murs[i];
}

int map::getSizeDoor() const
{
    return _door.size();
}

coord map::getDoor(int i) const
{
    return _door[i];
}

coord map::getCle() const
{
    return _cle;
}