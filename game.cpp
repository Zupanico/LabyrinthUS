/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : _f(30, 30)
{
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

    // Murs ajoutes par Evan
    _murs.push_back(new mur(1, 1, 26, 4));
    _murs.push_back(new mur(1, 1, 29, 4));

    _f.setEcran("_", 27, 4);
    _f.setEcran("_", 28, 4);
    _f.setEcran(_cle, 5, 9);

    _keyCollect = false;
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
    if (_kbhit()){
        int touche = _getch();
        if (touche=='q'){
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
    // Afficher le jeu
    _f.print(cout);
    _inv.afficherInventaire();
}

void game::deplacer(int dir)
{
    
    _f.setEcran(" ", _p.getX(), _p.getY());
    _f.setEcran("_", 27, 4);
    _f.setEcran("_", 28, 4);

    switch(dir)
    {
    case 72: 
         // Vérifier que le mouvement vers le haut n'est pas une collision avec un mur
         if (!collision(_p.getX(), (_p.getY()-1)))
            {
                _p.setY(_p.getY()-1);
            }
        break;
    case 80: 
        // Vérifier que le mouvement vers le bas n'est pas une collision avec un mur
        if (!collision(_p.getX(), (_p.getY()+1)))
        {
            _p.setY(_p.getY()+1);
        }
        break;
    case 77: 
        // Vérifier que le mouvement vers la droite n'est pas une collision avec un mur
        if (!collision(_p.getX()+1, _p.getY()))
        {
            _p.setX(_p.getX()+1);
        }
        break;
    case 75: 
        // Vérifier que le mouvement vers la gauche n'est pas une collision avec un mur
        if (!collision(_p.getX()-1, _p.getY()))
        {
            _p.setX(_p.getX()-1);
        }
        break;
    }
    
    //Actualiser l'inventaire
    ajoutCle();

    // Afficher le personnage sur la fenêtre
    _f.setEcran("X",  _p.getX(), _p.getY());

    // Afficher le jeu complet
    afficher();   

    cout << "Coordonnées du personnage : (" << _p.getX() << ", " << _p.getY() << ")" << endl;
    cout << "Dimensions de la fenêtre : " << _f.getLargeur() << "x" << _f.getHauteur() << endl;


}

void game::actualiserMur()
{
    for (int k=0; k<_murs.size(); k++)
    {
        for (int i = 0; i < _murs.at(k)->get_largeur(); i++)
        {
            for (int j = 0; j < _murs.at(k)->get_hauteur(); j++)
            {
                _f.setEcran(_cr, _murs.at(k)->get_positionX() + i, _murs.at(k)->get_positionY() + j);
            }
        }
    }
}

bool game::collision(int x, int y)
{

    // Collision avec les bords de la fenêtre
    if (x < 0 || x >= _f.getLargeur() || y < 0 || y >= _f.getHauteur()) 
    {
        cout << "Collision avec les bords de la fenêtre !" << endl;
        // Ramener le joueur à sa position précédente
        return true;
    } else if (_f.getEcran(x, y) == _cr)
    {
        cout << "Collision avec un mur !" << endl;
        // Ramener le joueur à sa position précédente
        return true;
    } else if (_f.getEcran(x, y) == "_")
    {
        if (_keyCollect == false)
        {
            cout << "Collision avec la porte !" << endl;
            // Ramener le joueur à sa position précédente
            return true;
        }
        else
        {
            return false;
        }
    }
    else 
    {
        return false;
    }
}

void game::loop()
{
    // Capturer les entrées clavier
    setclavier();

    // Pause pour limiter la vitesse d'affichage
    Sleep(10); // Utilisation de Sleep() pour introduire un délai de 100 millisecondes
}

void game::ajoutCle()
{
    if (_p.getX() == 5 && _p.getY() == 9 && _keyCollect == false)
    {
        _inv.addItem(new item(_cle));
        _keyCollect = true;
    }
}
