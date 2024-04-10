#include "map.h"

maps::maps()
{
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

bool maps::chercherMachine(int x, int y)
{
    if (getMachine().x == x && getMachine().y == y)
    {
        return true;
    }
    return false;
}

bool maps::chercherMachine(int x, int y)
{
    if (getMachine().x == x && getMachine().y == y)
    {
        return true;
    }
    return false;
}

bool maps::chercherNiveau(int x, int y)
{
    for (int i = 0; i < _niveau.size(); i++)
    {
        if (_niveau[i].x == x && _niveau[i].y == y){
            return true;
        }
    }
    return false;
}

void maps::actualiserMap(string fichier)
{
    _murs.clear();
    _door.clear();
    _locker.clear();
    _niveau.clear();
    _cle.x = 0;
    _cle.y = 0;
    _m1.x = 0;
    _m1.y = 0;

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
            switch (c)
                {
                case '#':
                    ajouterMur(x, y);
                    x++;
                    break;
                case 'P' :
                    ajouterPorte(x, y);
                    x++;
                    break;
                case 'L':
                    ajouterLocker(x, y);
                    x++;
                    break;
                case 'K':
                    afficherCle(x, y);
                    x++;
                    break;
                case '1':
                    afficherM1(x, y);
                    x++;
                    break;
                case 'N':
                    ajouterNiveau(x, y);
                    x++;
                    break;
                case 'F':
                    afficherFlash(x, y);
                    x++;
                    break;
                case '\n':
                    y++;
                    x = 0;
                    break;

                default:
                    x++;
                    break;
                }
        }
        fichierMur.close();
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier" << endl;
    }
}

int maps::getSizeNiveau() const
{
    return _niveau.size();
}

coord maps::getNiveau(int i) const
{
    return _niveau[i];
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

void maps::ajouterNiveau(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    _niveau.push_back(c);
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

void maps::afficherCoin(int x, int y)
{
    _coin.x = x;
    _coin.y = y;
}

void maps::afficherMachine(int x, int y)
{
    _machine.x = x;
    _machine.y = y;
}

void maps::afficherFlash(int x, int y)
{
    _flash.x = x;
    _flash.y = y;
}

void maps::afficherFood(int x, int y)
{
    _food.x = x;
    _food.y = y;
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

coord maps::getCoin() const
{
    return _coin;
}

coord maps::getMachine() const
{
    return _machine;
}

coord maps::getFlash() const
{
    return _flash;
}

coord maps::getFood() const
{
    return _food;
}