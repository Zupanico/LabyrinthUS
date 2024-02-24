/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : f(32, 30)
{
    prevPlayerX = 0;
    prevPlayerY = 0;   

    prevMonsterX = 29;
    prevMonsterY = 29; 
    _clavier = 0;

    murs.push_back(new mur(1,4,4,1)); //1
    murs.push_back(new mur(4,1,5,3)); //1'
    murs.push_back(new mur(5,1,0,5)); //2

    murs.push_back(new mur(7,1,0,7)); //3
    murs.push_back(new mur(1,1,3,8)); //3'
    murs.push_back(new mur(1,2,3,10)); //3''
    murs.push_back(new mur(2,1,4,11)); //3'''
    murs.push_back(new mur(3,1,0,11)); //3'''''
    murs.push_back(new mur(1,11,7,7)); //4
    murs.push_back(new mur(5,1,3,18)); //5
    murs.push_back(new mur(1,5,3,18)); //6
    murs.push_back(new mur(2,1,4,22)); //6'
    murs.push_back(new mur(1,5,6,22)); //6''
    
    murs.push_back(new mur(4,1,12,3)); //7
    murs.push_back(new mur(1,4,16,3)); //8
    murs.push_back(new mur(1,20,12,3)); //9
    murs.push_back(new mur(3,1,16,11)); //9'
    murs.push_back(new mur(4,1,12,23)); //10
    murs.push_back(new mur(1,13,15,11)); //11

    murs.push_back(new mur(5,1,20,4)); //12
    murs.push_back(new mur(3,1,20,15)); //12'
    murs.push_back(new mur(1,21,25,4)); //13
    murs.push_back(new mur(1,5,20,0)); //13'
    murs.push_back(new mur(1,10,20,15)); //14
    murs.push_back(new mur(6,1,20,25)); //15

    murs.push_back(new mur(6,1,10,26)); //16
    murs.push_back(new mur(1,2,10,26)); //17
    murs.push_back(new mur(1,3,15,26)); //18
    murs.push_back(new mur(10,1,16,28)); //19
    murs.push_back(new mur(1,2,25,27)); //20

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
    int touche;
    if (_kbhit())
    {
        touche = _getch();
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
    prevPlayerX = p.getX();
    prevPlayerY = p.getY();
    
    // Afficher le mur

    for (int k=0; k<murs.size(); k++)
    {
        for (int i = 0; i < murs.at(k)->get_largeur(); i++)
        {
            for (int j = 0; j < murs.at(k)->get_hauteur(); j++)
            {
                f.setEcran(c_mur, murs.at(k)->get_positionX() + i, murs.at(k)->get_positionY() + j);
            }
        }
    }

    f.setEcran(' ', prevPlayerX, prevPlayerY, RESET);
    f.setEcran(' ', prevMonsterX, prevMonsterY, RESET);

    switch(dir)
    {
    case 72: 
         // Vérifier que le mouvement vers le haut n'est pas une collision avec un mur
         if (prevPlayerY > 0 && f.getEcran(prevPlayerX,prevPlayerY-1) != _cr && f.getEcran(prevPlayerX, prevPlayerY-1) != c_mur)
            {
                p.setY(prevPlayerY-1);
            }
        break;
    case 80: 
        // Vérifier que le mouvement vers le bas n'est pas une collision avec un mur
        if (prevPlayerY < f.getHauteur()-1 && f.getEcran(prevPlayerX, prevPlayerY+1) != _cr && f.getEcran(prevPlayerX, prevPlayerY+1) != c_mur)
        {
            p.setY(prevPlayerY+1);
        }
        break;
    case 77: 
        // Vérifier que le mouvement vers la droite n'est pas une collision avec un mur
        if (prevPlayerX < f.getHauteur()-1 && f.getEcran(prevPlayerX+1, prevPlayerY) != _cr && f.getEcran(prevPlayerX+1, prevPlayerY) != c_mur)
        {
            if ((prevPlayerX < f.getLargeur()-2 && f.getEcran(prevPlayerX+1, prevPlayerY)) != _cr)
            {
                p.setX(prevPlayerX+1);
            }
        }
        break;
    case 75: 
        // Vérifier que le mouvement vers la gauche n'est pas une collision avec un mur
        if (prevPlayerX > 0 && f.getEcran(prevPlayerX-1, prevPlayerY) != _cr &&f.getEcran(prevPlayerX-1, prevPlayerY) != c_mur) 
            p.setX(prevPlayerX-1);
        break;
    }
    
    prevPlayerX = p.getX();
    prevPlayerY = p.getY();
    // Afficher le personnage sur la fenêtre
    f.setEcran('X',  prevPlayerX, prevPlayerY, RESET);


    if (prevMonsterX < f.getLargeur() - 1 && prevMonsterX < prevPlayerX && f.getEcran(prevMonsterX + 1, prevMonsterY) != c_mur)
        m.setX(prevMonsterX + 1);
    else if (prevMonsterX > 0 && prevMonsterX > prevPlayerX && f.getEcran(prevMonsterX - 1, prevMonsterY) != c_mur)
        m.setX(prevMonsterX - 1);
    if (prevMonsterY < f.getHauteur() - 1  && prevMonsterY < prevPlayerY && f.getEcran(prevMonsterX, prevMonsterY + 1) != c_mur)
        m.setY(prevMonsterY + 1);
    else if (prevMonsterY > 0 && prevMonsterY > prevPlayerY && f.getEcran(prevMonsterX, prevMonsterY - 1) != c_mur)
        m.setY(prevMonsterY - 1);

    // Sauvegarde de la position précédente du monstre
    prevMonsterX = m.getX();
    prevMonsterY = m.getY();

    // Afficher le monstre sur la fenêtre
    f.setEcran('M', prevMonsterX, prevMonsterY, RESET);

    // Mettre à jour le déplacement du monstre
    m.Demarrage_Deplacement_continu(p);

    // Vérifier les collisions
    collision();

    // Afficher le jeu complet
    afficher();   

    cout << "Coordonnées du personnage : (" << prevPlayerX << ", " << prevPlayerY << ")" << endl;
    cout << "Dimensions de la fenêtre : " << f.getLargeur() << "x" << f.getHauteur() << endl;
}

void game::collision()
{
    // Collision avec les bords de la fenêtre
    int x = p.getX();
    int y = p.getY();

    // Collision avec les bords de la fenêtre
    if (x < 0 || x >= f.getLargeur() || y < 0 || y >= f.getHauteur()) 
    {
        cout << "Collision avec les bords de la fenêtre !" << endl;
        // Ramener le joueur à sa position précédente
        p.setX(prevPlayerX);
        p.setY(prevPlayerY);
    }

    // Collision avec un mur
    if (f.getEcran(x, y) == _cr)
    {
        cout << "Collision avec un mur !" << endl;
        // Ramener le joueur à sa position précédente
        p.setX(prevPlayerX);
        p.setY(prevPlayerY);
    }
}

void game::loop()
{
    // Capturer les entrées clavier
    setclavier();

    // Pause pour limiter la vitesse d'affichage
    Sleep(10); // Utilisation de Sleep() pour introduire un délai de 100 millisecondes
}