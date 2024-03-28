#include "map.h"

maps::maps()
{
    _cle.x = 0;
    _cle.y = 0;
    _m1.x = -1;
    _m1.y = -1;
    _coin.x = 0;
    _coin.y = 0;
}

maps::~maps()
{
}

bool maps::chercherMur(int x, int y)
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

bool maps::chercherDoor(int x, int y)
{
    for (int i = 0; i < _door.size(); i++)
    {
        if (_door[i].x == x && _door[i].y == y)
        {
            return true;
        }
    }
    return false;
}

bool maps::chercherLocker(int x, int y)
{
    for (int i = 0; i < _locker.size(); i++)
    {
        if (_locker[i].x == x && _locker[i].y == y)
        {
            return true;
        }
    }
    return false;
}


void maps::actualiserMap(string fichier)
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
            c = toupper(c);
            
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
                else if (c == '1')
                {
                    afficherM1(x, y);
                }
                else if (c == 'L')
                {
                    ajouterLocker(x, y);
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

void maps::ajouterMur(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _murs.push_back(c);
}

void maps::ajouterPorte(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _door.push_back(c);
}

void maps::ajouterLocker(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _locker.push_back(c);
}


void maps::afficherCle(int x, int y)
{
    _cle.x = x;
    _cle.y = y;
}

void maps::afficherM1(int x, int y)
{
    _m1.x = x;
    _m1.y = y;
}

int maps::getSizeMurs() const
{
    return _murs.size();
}

coord maps::getMur(int i) const
{
    return _murs[i];
}

int maps::getSizeDoor() const
{
    return _door.size();
}

coord maps::getDoor(int i) const
{
    return _door[i];
}

int maps::getSizeLocker() const
{
    return _locker.size();
}

coord maps::getLocker(int i) const
{
    return _locker[i];
}

coord maps::getCle() const
{
    return _cle;
}

coord maps::getM1() const
{
    return _m1;
}