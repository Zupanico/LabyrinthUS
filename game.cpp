/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : _f(30, 30)
{
    _clavier = 0;
    _vies = 3;  

    _gameOver = false;


    _keyCollect = false;
    
    _m.addTriggerPoint(_map.getM1().x, _map.getM1().y);

}

game::~game()
{
}

int game::getclavier() const
{
    return _clavier;
}

// Méthode pour mettre à jour le nombre de vies du joueur
void game::mettreAJourVies(int changement)
{
    _vies += changement;
        
    if (_vies <= 0) 
    {
        // Game over
        _gameOver = true;
    }
}


void game::setclavier()
{
    static int k = 0; // Déclarer k en tant que variable statique pour qu'elle conserve sa valeur entre les appels
    if (_kbhit()){
        int touche = _getch();
        if (touche=='q' || touche=='Q')
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
                _p.setVitesseY(-100);
                _p.setVitesseX(0);
                break;
            case 80:    //fleche bas
                _p.setVitesseY(100);
                _p.setVitesseX(0);
                break;
            case 77:    // fleche droite
                _p.setVitesseX(100);
                _p.setVitesseY(0);
                break;
            case 75:    // fleche gauche
                _p.setVitesseX(-100);
                _p.setVitesseY(0);
                break;
            default:
                break;
            }
            k = 0; // Réinitialiser k après avoir traité la touche fléchée
        }
    }
}

void game::deplacerJoueur()
{
    _f.setEcran("  ", _p.getX(), _p.getY());
    


     // Vérifier que le mouvement vers le haut n'est pas une collision avec un mur
    if (!collision(_p.getX(), (_p.getY()-1)) && _p.getVitesseY() < 0)
        {
            _p.deplacementY();
        }


    // Vérifier que le mouvement vers le bas n'est pas une collision avec un mur
    if (!collision(_p.getX(), (_p.getY()+1)) && _p.getVitesseY() > 0)
        {
            _p.deplacementY();
        }



    // Vérifier que le mouvement vers la droite n'est pas une collision avec un mur
    if (!collision(_p.getX()+1, _p.getY()) && _p.getVitesseX() > 0)
        {
            _p.deplacementX();
        }


    // Vérifier que le mouvement vers la gauche n'est pas une collision avec un mur
    if (!collision(_p.getX()-1, _p.getY()) && _p.getVitesseX() < 0)
        {
            _p.deplacementX();
        }

    if ((_p.getX() == _map.getCle().x && _p.getY() == _map.getCle().y && _keyCollect == false))
        {
            _inv.addItem(new item(_cle));
            _keyCollect = true;
        }
    //Actualiser les portes
    for (int i = 0; i < _map.getSizeDoor(); i++)
    {
        _f.setEcran(_door, _map.getDoor(i).x, _map.getDoor(i).y);
    }
    // Afficher le personnage sur la fenêtre
    _f.setEcran(_player,  _p.getX(), _p.getY());
    
    if (_m.getActif())
    {
        deplacerMonster();
    }
    else
    {
        checkTriggerPoints();
    }

    // Afficher le jeu complet
    afficher();   
}

// Réinitialiser la position du joueur
void game::reinitialiserPositionJoueur()
{
    // Générer une nouvelle position aléatoire pour le joueur
    int newX, newY;
    int maxTentatives = 1000; // Limite le nombre de tentatives pour éviter une boucle infinie
    do {
        newX = rand() % _f.getLargeur();
        newY = rand() % _f.getHauteur();
        maxTentatives--;
    } while (collision(newX, newY) && maxTentatives > 0); // Vérifier que la position générée n'est pas en collision avec un mur

    // Mettre à jour la position du joueur
    _p.setX(newX);
    _p.setY(newY);
}


void game::deplacerMonster()
{
    _f.setEcran("  ", _m.getX(), _m.getY());

    if (_m.getX() < _p.getX() && !collision(_m.getX() + 1, _m.getY()))
        _m.setX(_m.getX() + 1);
    else if (_m.getX() > _p.getX() && !collision(_m.getX() - 1, _m.getY()))
        _m.setX(_m.getX() - 1);
    if (_m.getY() < _p.getY() && !collision(_m.getX(), _m.getY() + 1))
        _m.setY(_m.getY() + 1);
    else if (_m.getY() > _p.getY() && !collision(_m.getX(), _m.getY() - 1))
        _m.setY(_m.getY() - 1);

    // Afficher le personnage sur la fenêtre
    _f.setEcran(_monster,  _m.getX(), _m.getY());

    if ( _p.getX() == _m.getX() && _p.getY() == _m.getY())
    {
        // Diminuer la vie du joueur
        mettreAJourVies(-1);

        // Réinitialiser la position du joueur à une position aléatoire
        reinitialiserPositionJoueur();
    }
    else
    {
        _gameOver = false;
    }
}

bool game::checkTriggerPoints()
{
    if (_keyCollect == true)  
        {
            _m.setActif(true);
            _m.setX(_map.getM1().x);
            _m.setY(_map.getM1().y);

            return true;
        }
    return false;
}

void game::actualiserMap(string fichier)
{
    _map.actualiserMap(fichier);
    for (int i = 0; i < _map.getSizeMurs(); i++)
    {
        _f.setEcran(_cr, _map.getMur(i).x, _map.getMur(i).y);
    }
    for (int i = 0; i < _map.getSizeDoor(); i++)
    {
        _f.setEcran(_door, _map.getDoor(i).x, _map.getDoor(i).y);
    }
    for (int i = 0; i < _map.getSizeLocker(); i++)
    {
        _f.setEcran(_locker, _map.getLocker(i).x, _map.getLocker(i).y);
    }
    _f.setEcran(_cle, _map.getCle().x, _map.getCle().y);
}

bool game::collision(int x, int y)
{
    const int largeurFen = _f.getLargeur();   // Largeur de la fenetre
    const int hauteurFen = _f.getHauteur();   // Hauteur de la fenetre

    const int largeurPer = _p.getLargeur();   // Largeur du personnage
    const int hauteurPer = _p.getHauteur();   // Hauteur du personnage


    // Collision avec les bords de la fenêtre
    // Regarde si la position en y et en x du personnage est en dehors des limites de la fenetre
    if (x < 0 || x >= largeurFen - largeurPer || y < 0 || y >= hauteurFen - hauteurPer)
    {
        // Ramener le joueur à sa position précédente
        return true;
    } 
    
    else if (_map.chercherMur(x, y))
    {
        // Ramener le joueur à sa position précédente
        return true;
    }

    else if (_map.chercherDoor(x, y))
    {
        if (_keyCollect == false)
        {
            // Ramener le joueur à sa position précédente
            return true;
        }
        else
        {
            return false;
        }
    }

    else if (_map.chercherLocker(x, y))
    {
        return true;
    }

    else 
    {
        return false;
    }
}

bool game::getGameOver()
{
    return _gameOver;
}

// Afficher le jeu
void game::afficher() const
{
    // Effacer l'écran
    COORD _pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _pos); // Positionne le curseur en haut à gauche de la fenêtre
    // Afficher le jeu

    cout << "LABYRINTHUS" << endl;

    _f.print(cout);

    // Afficher les coordonnées du personnage
    cout << "Coordonnées du personnage : (" << _p.getX() << ", " << _p.getY() << ")" << endl;

    // Afficher les coordonnées du monstre
    cout << "Coordonnées du monstre : (" << _m.getX() << ", " << _m.getY() << ")" << endl;

    // Afficher la vie du joueur
    cout << "Vies du joueur : " << _vies << endl;

    // Afficher l'inventaire du joueur
    _inv.afficherInventaire();
}

void game::loop()
{
    // Capturer les entrées clavier
    setclavier();
    deplacerJoueur();

    // Pause pour limiter la vitesse d'affichage
    Sleep(10); // Utilisation de Sleep() pour introduire un délai de 10 millisecondes
}