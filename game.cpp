/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : _f(30, 30), _po(3, 9)
{
    _clavier = 0;

    Inserer_Murs();
    Inserer_Portail();
    Inserer_Monstre();

    _m.setX(28);
    _m.setY(28);

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
                deplacer_joueur(72);
                cout << "Haut" << endl;
                break;
            case 80:    //fleche bas
                deplacer_joueur(80);
                cout << "Bas" << endl;
                break;
            case 77:    // fleche droite
                deplacer_joueur(77);
                cout << "Droite" << endl;
                break;
            case 75:    // fleche gauche
                deplacer_joueur(75);
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
}

/// Ajouter un mur
void game::Ajouter_Mur()
{
      for (int k=0; k < _murs.size(); k++)
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

// Insérer les murs
void game::Inserer_Murs()
{
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

void game::Ajouter_Portail()
{
    // Insérez ici le code pour ajouter un portail
    for (int k = 0; k < _portails.size(); k++)
    {
        _f.setEcran("P", _portails.at(k)->getPosX(), _portails.at(k)->getPosY());
    }
}  

void game::Inserer_Portail()
{
    // Insérez ici le code pour initialiser les portails
    _portails.push_back(new portail(3, 9));
    //_portails.push_back(new portail(1, 1));
    //portails.push_back(new portail(2, 2));
    //portails.push_back(new portail(3, 3));
}

void game::Ajouter_Monstre(int x, int y)
{

    monster *new_monstre = new monster();
    new_monstre->setX(x);
    new_monstre->setY(y);
    monstres.push_back(new_monstre); // Ajout du monstre au vecteur monstres
}

void game::Inserer_Monstre()
{
    /*// Insérez ici le code pour initialiser les monstres
    Ajouter_Monstre(25, 27);
    //ajouter_monstre(24, 20);
    //ajouter_monstre(2, 26);
    //ajouter_monstre(28, 28);*/
}

void game::deplacer_monstre(int index) 
{
    // Vérification si l'index est valide
    if (index < 0 || index >= monstres.size()) 
    {
        cout << "Index de monstre invalide !" << endl;
        return;
    }

    // Sauvegarde de la position précédente du monstre
    prevMonsterX[index] = monstres[index]->getX();
    prevMonsterY[index] = monstres[index]->getY();
    
    prevPlayerX = _p.getX();
    prevPlayerY = _p.getY();

   // Vérifier s'il y a un mur entre le monstre et le joueur
    bool joueurADistance = (abs(prevPlayerX - prevMonsterX[index]) + abs(prevPlayerY - prevMonsterY[index])) < 5; // à adapter selon la portée du monstre
    bool cheminLibre = true;
    
    if (joueurADistance) 
    {
        // Vérifier s'il y a un mur entre le monstre et le joueur
        // Si le joueur est à portée, vérifiez s'il y a un mur sur la ligne de vue
        // Utilisez un algorithme de traçage de ligne (par exemple, Bresenham) 
        //pour vérifier s'il y a un mur entre les positions actuelles du monstre et du joueur
        // Vérifier s'il y a un mur entre le monstre et le joueur
        cheminLibre = !Mur_Entre_Les_Deux(prevMonsterX[index], prevMonsterY[index], prevPlayerX, prevPlayerY, _f);
        // Ici, je vais utiliser une vérification simple en regardant 
        //si le joueur est sur la même colonne ou la même ligne que le monstre
        if (prevPlayerX == prevMonsterX[index]) 
        {
            int minY = min(prevPlayerY, prevMonsterY[index]);
            int maxY = max(prevPlayerY, prevMonsterY[index]);
            for (int y = minY + 1; y < maxY; ++y) 
            {
                if (_f.getEcran(prevPlayerX, y) == _cr) 
                {
                    cheminLibre = false;
                    break;
                }
            }
        } 
        else if (prevPlayerY == prevMonsterY[index]) 
        {
            int minX = min(prevPlayerX, prevMonsterX[index]);
            int maxX = max(prevPlayerX, prevMonsterX[index]);
            for (int x = minX + 1; x < maxX; ++x) {
                if (_f.getEcran(x, prevPlayerY) == _cr) 
                {
                    cheminLibre = false;
                    break;
                }
            }
        } 
        else 
        {
            // Si le joueur n'est pas sur la même colonne ou la même ligne que le monstre,
            // nous supposons qu'il n'y a pas de ligne de vue claire pour le moment
            cheminLibre = false;
        }
    }

    // Si le joueur est à portée et la ligne de vue est claire, le monstre poursuit le joueur
    if (joueurADistance && cheminLibre) 
    {
        // Insersion de la methode pour faire poursuivre le joueur par le monstre
        monstres[index]->Poursuivre_Joueur(prevPlayerX, prevPlayerY);
    } 
    else 
    {
        // Si le joueur n'est pas à portée ou s'il y a un mur entre le monstre et le joueur, 
        //le monstre cherche une direction sans mur et s'y déplace

        // Liste des directions possibles
        vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // {Haut, Bas, Gauche, Droite}

        // Choisir une direction aléatoire qui ne contient pas de mur
        random_device rd; // Obtenir une graine aléatoire à partir du périphérique matériel
        mt19937 gen(rd()); // Initialiser un générateur de nombres aléatoires Mersenne Twister avec la graine aléatoire
        shuffle(directions.begin(), directions.end(), gen); // Mélanger les directions avec le générateur de nombres aléatoires

        if (!collision(_m.getX(), (_m.getY()-1)) && !collision(_m.getX(), (_m.getY()+1)) && !collision(_m.getX()-1, _m.getY()) && !collision(_m.getX()+1, _m.getY()))
        { 
            for (const auto& direction : directions) 
            {
                int newX = prevMonsterX[index] + direction.first;
                int newY = prevMonsterY[index] + direction.second;

                // Vérifier si la nouvelle position est valide et ne contient pas de mur
                if (newX >= 0 && newX < _f.getLargeur() && newY >= 0 && newY < _f.getHauteur() && _f.getEcran(newX, newY) != _cr) 
                {
                    monstres[index]->setX(newX);
                    monstres[index]->setY(newY);
                    break; // Sortir de la boucle une fois que nous avons trouvé une direction valide
                }
            }
        }
    }
    
  }

void game::deplacer_joueur(int dir)
{
    _f.setEcran(" ", _p.getX(), _p.getY());

    for (int i = 0; i < monstres.size(); i++)
    {
        _f.setEcran(" ", monstres[i]->getX(), monstres[i]->getY());
    }

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

     // Afficher le personnage sur la fenêtre
    _f.setEcran("X",  _p.getX(), _p.getY());   

    /*if (_m.getX() < _p.getX() && !collision(_m.getX() + 1, _m.getY()))
        _m.setX(_m.getX() + 1);
    else if (_m.getX() > _p.getX() && !collision(_m.getX() - 1, _m.getY()))
        _m.setX(_m.getX() - 1);
    if (_m.getY() < _p.getY() && !collision(_m.getX(), _m.getY() + 1))
        _m.setY(_m.getY() + 1);
    else if (_m.getY() > _p.getY() && !collision(_m.getX(), _m.getY() - 1))
        _m.setY(_m.getY() - 1);*/

    for (int i = 0; i < monstres.size(); i++)
    {
        deplacer_monstre(i);
    }


    for (int i = 0; i < monstres.size(); i++)
    {
        _f.setEcran("M",  monstres[i]->getX(), monstres[i]->getY());
    }

    // Mettre à jour le déplacement du monstre
    for (int i = 0; i < monstres.size(); i++)
    {
        monstres[i]->Demarrage_Deplacement_continu(_p);
    }
    
    // Afficher le jeu complet
    afficher();   

    cout << "Coordonnées du personnage : (" << _p.getX() << ", " << _p.getY() << ")" << endl;

    for (int i = 0; i < monstres.size(); i++)
    {
        cout << "Coordonnées du monstre " << i << " : (" << monstres[i]->getX() << ", " << monstres[i]->getY() << ")" << endl;
    }
    
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
    } 
    else if (_f.getEcran(x, y) == _cr)
    {
        cout << "Collision avec un mur !" << endl;
        // Ramener le joueur à sa position précédente
        return true;
    } else 
    {
        return false;
    }
}

bool game::Mur_Entre_Les_Deux(int x0 , int y0, int x1, int y1, const fenetre& f)
{
        
    x0 = max(0, min(x0, f.getLargeur() - 1));
    y0 = max(0, min(y0, f.getHauteur() - 1));
    x1 = max(0, min(x1, f.getLargeur() - 1));
    y1 = max(0, min(y1, f.getHauteur() - 1));

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int x = x0;
    int y = y0;

    int n = 1 + dx + dy;

    int x_inc = (x1 > x0) ? 1 : -1;
    int y_inc = (y1 > y0) ? 1 : -1;

    int error = dx - dy;
    dx *= 2;
    dy *= 2;

    for (; n > 0; --n)
    {
        if (f.getEcran(x, y) == _cr)
        {
            return true;
        }
        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }
    return false;
}

void game::loop()
{
    // Capturer les entrées clavier
    setclavier();

    // Pause pour limiter la vitesse d'affichage
    Sleep(10); // Utilisation de Sleep() pour introduire un délai de 100 millisecondes
}
