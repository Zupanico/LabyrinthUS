/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

game::game() : _f(85, 30)
{
    _clavier = 0;

    _vies = 3;

    _gameOver = false;

    // Inserez ici le code pour initialiser les murs
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
    _murs.push_back(new mur(1,3,20,26)); //21
    _murs.push_back(new mur(4,1,3,14)); //22
    _murs.push_back(new mur(1,2,3,15)); //23
    _murs.push_back(new mur(1,1,14,11)); //24
    _murs.push_back(new mur(6,1,17,6)); //25
    _murs.push_back(new mur(1,7,22,7)); //26
    _murs.push_back(new mur(3,1,9,3)); //27
    _murs.push_back(new mur(2,2,27,6)); //28
    _murs.push_back(new mur(2,2,27,11)); //29
    _murs.push_back(new mur(2,2,27,16)); //30
    _murs.push_back(new mur(2,2,27,21)); //31
    _murs.push_back(new mur(2,2,9,16)); //32
    _murs.push_back(new mur(2,2,9,9)); //33
    _murs.push_back(new mur(4,4,1,25)); //34
    _murs.push_back(new mur(1,2,6,27)); //35
    _murs.push_back(new mur(1,1,5,28)); //36
    _murs.push_back(new mur(2,3,17,8)); //37
    _murs.push_back(new mur(2,5,17,17)); //38
    _murs.push_back(new mur(2,1,20,13)); //39
    _murs.push_back(new mur(2,2,9,0)); //40
    _murs.push_back(new mur(2,2,14,0)); //41
    _murs.push_back(new mur(1,1,10,28)); //42
    _murs.push_back(new mur(1,3,25,0)); //43

    _f.setEcran(_cle, 5, 9);

    _keyCollect = false;

    //_m.addTriggerPoint(1, 10);
    _m.addTriggerPoint(5, 1);

}

game::~game() 
{
    // Libérer la mémoire allouée pour les objets mur
    for (auto mur : _murs)
    {
        delete mur;
    }

    // Libérer la mémoire allouée pour l'objet game
    delete this;
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

void game::setJoystick()
{
    // Lire les valeurs du joystick
    tuple<double, double> joystickValues = _a.lireJoystick();

    double joystickX, joystickY;
    tie(joystickX, joystickY) = joystickValues;

    // Déterminez la direction de déplacement en fonction des valeurs du joystick
    _p.setVitesseX(joystickX);
    _p.setVitesseY(joystickY);
}


void game::libererDuMonstre() 
{

    cout << "                    !!!!!!! LE MONSTRE VOUS A ATTRAPÉ !!!!!!!" << endl;
    Sleep(3000); // Attendre 1 seconde

    cout << "Tournez rapidement la manette du HAUT vers le BAS de la DROITE vers la GAUCHE pour vous libérer !" << endl;
    Sleep(3000); // Attendre 1 seconde

    cout << "                    Vous avez 10 secondes pour vous libérer !" << endl;
    Sleep(5000); // Attendre 2 secondes
    
    cout << "\n" << endl;

    // Initialisations
    const double standardValueX = 0.5, standardValueY = -0.2, standardValueZ = 0.8;
    const double marge = 0.50;

    auto start = chrono::steady_clock::now();

    while (true) 
    {
        auto valeursAccelerometre = _a.lireAccelerometre();
        double valeurAccelerometreX = std::get<0>(valeursAccelerometre);
        double valeurAccelerometreY = std::get<1>(valeursAccelerometre);
        double valeurAccelerometreZ = std::get<2>(valeursAccelerometre);

        string message = "Valeurs de l'accéléromètre : " ;
        cout << message << valeurAccelerometreX << ", " << valeurAccelerometreY << ", " << valeurAccelerometreZ << endl;

        // Imprimez suffisamment d'espaces pour couvrir le message précédent
        for (size_t i = 0; i < message.length(); ++i) 
        {
            cout << "\b \b"; 
        }

        // Conditions de libération ou d'échec
        if (abs(valeurAccelerometreX - standardValueX) < marge && 
            abs(valeurAccelerometreY - standardValueY) < marge && 
            abs(valeurAccelerometreZ - standardValueZ) < marge) 
        {
            mettreAJourVies(-1);
            reinitialiserPositionJoueur();

            string message = "Vous vous êtes libéré du monstre mais vous avez perdu une vie !";

            cout << message << endl;

            // Imprimez suffisamment d'espaces pour couvrir le message précédent
            for (size_t i = 0; i < message.length(); ++i) 
            {
                cout << "\b \b"; 
            }
            
            Sleep(2000); // Attendre 3 secondes

            system("cls");

            break;
        }

        auto end = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(end - start).count() >= 10) 
        {
            _vies = 0;
            _gameOver = true;

            string message = "Vous n'avez pas réussi à vous libérer à temps. Vous avez perdu toutes vos vies !";

            cout << message << endl;

            // Imprimez suffisamment d'espaces pour couvrir le message précédent
            for (size_t i = 0; i < message.length(); ++i) 
            {
                cout << "\b \b"; 
            }

            Sleep(2000); // Attendre 3 secondes

            system("cls");

            break;
        }  
         
        Sleep(500); // Pause
    }
}

void game::deplacerJoueur()
{
    _f.setEcran("  ", _p.getX(), _p.getY());
    _f.setEcran(_door, 25, 3);
    _f.setEcran(_door, 24, 3);


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
        
    //Actualiser l'inventaire
    ajoutCle();

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

void game::reinitialiserPositionJoueur()
{
    int distanceMax = 10; // Définir la distance maximale de réinitialisation
    int newX, newY;
    int maxTentatives = 100; // Limite le nombre de tentatives pour éviter une boucle infinie
    bool positionValide;

    do {
        // Générer une nouvelle position aléatoire à proximité du joueur
        int decalageX = (rand() % (distanceMax * 2 + 1)) - distanceMax;
        int decalageY = (rand() % (distanceMax * 2 + 1)) - distanceMax;
        newX = _p.getX() + decalageX;
        newY = _p.getY() + decalageY;

        // Vérifier si la nouvelle position est valide (pas en collision et dans les limites du jeu)
        positionValide = !collision(newX, newY) && newX >= 0 && newY >= 0 && newX < _f.getLargeur() && newY < _f.getHauteur();
        maxTentatives--;
    } while (!positionValide && maxTentatives > 0);

    if (positionValide) 
    {
        // Si une position valide est trouvée, mettre à jour la position du joueur
        _p.setX(newX);
        _p.setY(newY);
    } 
    else 
    {
        // Si aucune position valide n'est trouvée, réinitialiser le joueur à sa position initiale
        _p.setX(0);
        _p.setY(0);
    }
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
        // Le monstre a attrapé le joueur
        libererDuMonstre();
    }
    else
    {
        _gameOver = false;
    }
}

bool game::checkTriggerPoints()
{
    if (abs(_p.getX() - _m.getTriggerPoint().x) < 4 && abs(_p.getY() - _m.getTriggerPoint().y) < 3 || _keyCollect)  
        {
            _m.setActif(true);
            _m.setX(_m.getTriggerPoint().x);
            _m.setY(_m.getTriggerPoint().y);

            return true;
        }
    return false;
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
        // Ramener le joueur à sa position précédente
        return true;
    } 
    
    else if (_f.getEcran(x, y) == _cr)
    {
        // Ramener le joueur à sa position précédente
        return true;
    }

    else if (_f.getEcran(x, y) == _door)
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

    else 
    {
        return false;
    }
}

void game::ajoutCle()
{
    if (_p.getX() == 5 && _p.getY() == 9 && _keyCollect == false)
    {
        _inv.addItem(new item(_cle));
        _keyCollect = true;
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

    // Afficher le titre du jeu
    cout << "                           LABYRINTHUS" << endl;

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
    setJoystick();
    deplacerJoueur();

    // Pause pour limiter la vitesse d'affichage
    Sleep(100); // Utilisation de Sleep() pour introduire un délai de 5 millisecondes
}