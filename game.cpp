/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : f(32, 30)
{
    _prevPlayerX = 0;
    _prevPlayerY = 0;   

    _prevMonsterX = 29;
    _prevMonsterY = 29; 
    _clavier = 0;

    _murs.push_back(new mur(1,4,4,1)); //1
    _murs.push_back(new mur(4,1,5,3)); //1'
    _murs.push_back(new mur(5,1,0,5)); //2

    _murs.push_back(new mur(7,1,0,7)); //3
    _murs.push_back(new mur(1,1,3,8)); //3'
    _murs.push_back(new mur(1,2,3,10)); //3''
    _murs.push_back(new mur(2,1,4,11)); //3'''
    _murs.push_back(new mur(3,1,0,11)); //3'''''
    _murs.push_back(new mur(1,11,7,7)); //4
    _murs.push_back(new mur(5,1,3,18)); //5
    _murs.push_back(new mur(1,5,3,18)); //6
    _murs.push_back(new mur(2,1,4,22)); //6'
    _murs.push_back(new mur(1,5,6,22)); //6''
    
    _murs.push_back(new mur(4,1,12,3)); //7
    _murs.push_back(new mur(1,4,16,3)); //8
    _murs.push_back(new mur(1,20,12,3)); //9
    _murs.push_back(new mur(3,1,16,11)); //9'
    _murs.push_back(new mur(4,1,12,23)); //10
    _murs.push_back(new mur(1,13,15,11)); //11

    _murs.push_back(new mur(5,1,20,4)); //12
    _murs.push_back(new mur(3,1,20,15)); //12'
    _murs.push_back(new mur(1,21,25,4)); //13
    _murs.push_back(new mur(1,5,20,0)); //13'
    _murs.push_back(new mur(1,10,20,15)); //14
    _murs.push_back(new mur(6,1,20,25)); //15

    _murs.push_back(new mur(6,1,10,26)); //16
    _murs.push_back(new mur(1,2,10,26)); //17
    _murs.push_back(new mur(1,3,15,26)); //18
    _murs.push_back(new mur(10,1,16,28)); //19
    _murs.push_back(new mur(1,2,25,27)); //20

}

game::~game() 
{
    // Destructeur
}

int game::getclavier() const
{
    return _clavier;
}

void game::setclavier()
{
    static int k = 0; // Déclarer k en tant que variable statique pour qu'elle conserve sa valeur entre les appels
    if (_kbhit())
    {
        int touche = _getch();
        if (touche=='q')
        {
            cout << "Quitter" << endl;
            exit(0);
        }

        if (touche == 224) // Vérifier si la touche est une fleche
        {
            k = 1; // Passage à l'étape suivante
        }
        else if (k == 1) // Vérifier si nous sommes dans la deuxieme étape
        {
            switch (touche)
            {
            case 72:    // fleche haut
                deplacer(72);
                cout << "Haut" << endl;
                break;
            case 80:    //fleche bas
                deplacer(80);
                cout << "Bas" << endl;
                break;
            case 77:    // fleche droite
                deplacer(77);
                cout << "Droite" << endl;
                break;
            case 75:    // fleche gauche
                deplacer(75);
                cout << "Gauche" << endl;
                break;
            default:
                break;
            }
            k = 0; // Réinitialiser k après avoir traité la touche fléchée
        }
    }
}

// Afficher le jeu
void game::afficher() const
{
    f.print(cout);
}

void game::deplacer(int dir)
{
    // Sauvegarde de la position précédente du joueur
    _prevPlayerX = _p.getX();
    _prevPlayerY = _p.getY();
    
    // Afficher le mur

    for (int k=0; k < _murs.size(); k++)
    {
        for (int i = 0; i < _murs.at(k)->get_largeur(); i++)
        {
            for (int j = 0; j < _murs.at(k)->get_hauteur(); j++)
            {
                f.setEcran(c_mur, _murs.at(k)->get_positionX() + i, _murs.at(k)->get_positionY() + j);
            }
        }
    }

    f.setEcran(' ', _prevPlayerX, _prevPlayerY, RESET);
    f.setEcran(' ', _prevMonsterX, _prevMonsterY, RESET);

    switch(dir)
    {
    case 72: 
         // Vérifier que le mouvement vers le haut n'est pas une collision avec un mur
         if (_prevPlayerY > 0 && f.getEcran(_prevPlayerX,_prevPlayerY-1) != _cr && f.getEcran(_prevPlayerX, _prevPlayerY-1) != c_mur)
            {
                _p.setY(_prevPlayerY-1);
            }
        break;
    case 80: 
        // Vérifier que le mouvement vers le bas n'est pas une collision avec un mur
        if (_prevPlayerY < f.getHauteur()-1 && f.getEcran(_prevPlayerX, _prevPlayerY+1) != _cr && f.getEcran(_prevPlayerX, _prevPlayerY+1) != c_mur)
        {
            _p.setY(_prevPlayerY+1);
        }
        break;
    case 77: 
        // Vérifier que le mouvement vers la droite n'est pas une collision avec un mur
        if (_prevPlayerX < f.getHauteur()-1 && f.getEcran(_prevPlayerX+1, _prevPlayerY) != _cr && f.getEcran(_prevPlayerX+1, _prevPlayerY) != c_mur)
        {
            if ((_prevPlayerX < f.getLargeur()-2 && f.getEcran(_prevPlayerX+1, _prevPlayerY)) != _cr)
            {
                _p.setX(_prevPlayerX+1);
            }
        }
        break;
    case 75: 
        // Vérifier que le mouvement vers la gauche n'est pas une collision avec un mur
        if (_prevPlayerX > 0 && f.getEcran(_prevPlayerX-1, _prevPlayerY) != _cr &&f.getEcran(_prevPlayerX-1, _prevPlayerY) != c_mur) 
            _p.setX(_prevPlayerX-1);
        break;
    }
    
    _prevPlayerX = _p.getX();
    _prevPlayerY = _p.getY();
    // Afficher le personnage sur la fenêtre
    f.setEcran('X',  _prevPlayerX, _prevPlayerY, RESET);


    if (_prevMonsterX < f.getLargeur() - 1 && _prevMonsterX < _prevPlayerX && f.getEcran(_prevMonsterX + 1, _prevMonsterY) != c_mur)
        _m.setX(_prevMonsterX + 1);
    else if (_prevMonsterX > 0 && _prevMonsterX > _prevPlayerX && f.getEcran(_prevMonsterX - 1, _prevMonsterY) != c_mur)
        _m.setX(_prevMonsterX - 1);
    if (_prevMonsterY < f.getHauteur() - 1  && _prevMonsterY < _prevPlayerY && f.getEcran(_prevMonsterX, _prevMonsterY + 1) != c_mur)
        _m.setY(_prevMonsterY + 1);
    else if (_prevMonsterY > 0 && _prevMonsterY > _prevPlayerY && f.getEcran(_prevMonsterX, _prevMonsterY - 1) != c_mur)
        _m.setY(_prevMonsterY - 1);

    // Sauvegarde de la position précédente du monstre
    _prevMonsterX = _m.getX();
    _prevMonsterY = _m.getY();

    // Afficher le monstre sur la fenêtre
    f.setEcran('M', _prevMonsterX, _prevMonsterY, RESET);

    // Mettre à jour le déplacement du monstre
    _m.Demarrage_Deplacement_continu(_p);

    // Vérifier les collisions
    collision();

    // Afficher le jeu complet
    afficher();   

    cout << "Coordonnées du personnage : (" << _prevPlayerX << ", " << _prevPlayerY << ")" << endl;
    cout << "Dimensions de la fenêtre : " << f.getLargeur() << "x" << f.getHauteur() << endl;
}

void game::collision()
{
    // Collision avec les bords de la fenêtre
    int x = _p.getX();
    int y = _p.getY();

    // Collision avec les bords de la fenêtre
    if (x < 0 || x >= f.getLargeur() || y < 0 || y >= f.getHauteur()) 
    {
        cout << "Collision avec les bords de la fenêtre !" << endl;
        // Ramener le joueur à sa position précédente
        _p.setX(_prevPlayerX);
        _p.setY(_prevPlayerY);
    }

    // Collision avec un mur
    if (f.getEcran(x, y) == _cr)
    {
        cout << "Collision avec un mur !" << endl;
        // Ramener le joueur à sa position précédente
        _p.setX(_prevPlayerX);
        _p.setY(_prevPlayerY);
    }
}

void game::loop()
{
    // Capturer les entrées clavier
    setclavier();

    // Pause pour limiter la vitesse d'affichage
    Sleep(10); // Utilisation de Sleep() pour introduire un délai de 100 millisecondes
}