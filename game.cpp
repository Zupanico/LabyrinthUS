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

    _longerMur = false;

    _murDroite = false;
    _murGauche = false;
    _murHaut = false;
    _murBas = false;

    _positionPrecedante = 0;

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
    if (!_a.isConnected())
    {
        mettreAJourVies(-1);
        reinitialiserPositionJoueur();
        return;
    }
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
    _f.setEcran(_player, _p.getX(), _p.getY());
    
    // Deplacer monstre
    if (_m.getActif()){
        if (_m.getPoursuite()){
            //...
        }
        else {
            patrouillageMonster();
        }
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

    // Vérifier que le mouvement vers le haut n'est pas une collision avec un mur
    if (!collision(_m.getX(), (_m.getY() - 1)) && _m.getVitesseY() < 0)
    {
        _m.deplacementY();
    }

    // Vérifier que le mouvement vers le bas n'est pas une collision avec un mur
    if (!collision(_m.getX(), (_m.getY() + 1)) && _m.getVitesseY() > 0)
    {
        _m.deplacementY();
    }

    // Vérifier que le mouvement vers la droite n'est pas une collision avec un mur
    if (!collision(_m.getX() + 1, _m.getY()) && _m.getVitesseX() > 0)
    {
        _m.deplacementX();
    }

    // Vérifier que le mouvement vers la gauche n'est pas une collision avec un mur
    if (!collision(_m.getX() - 1, _m.getY()) && _m.getVitesseX() < 0)
    {
        _m.deplacementX();
    }

    // Afficher le monstre sur la fenêtre
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

void game::patrouillageMonster()
{
    if (_map.chercherMur(_m.getX()+1, _m.getY()))
    {
        _murDroite = true;
        _positionPrecedante = 1; //droite
    }
    else if (_map.chercherMur(_m.getX()-1, _m.getY()))
    {
        _murGauche = true;
        _positionPrecedante = 2; //gauche
    }
    else if (_map.chercherMur(_m.getX(), _m.getY()+1))
    {
        _murBas = true;
        _positionPrecedante = 3; //bas
    }
    else if (_map.chercherMur(_m.getX(), _m.getY()-1))
    {
        _murHaut = true;
        _positionPrecedante = 4; //haut
    }

    if (_longerMur == false)
    {
        while (_murDroite==false && _murGauche==false && _murBas==false && _murHaut==false)
        {
            _m.patrol();
        }
        _longerMur = true;
    }
    else if (_longerMur == true)
    {
        if (_murGauche == true)
        {
            _m.setY(_m.getY()+1);
        }
        else if (_murDroite == true)
        {
            _m.setY(_m.getY()-1);
        }
        else if (_murHaut == true)
        {
            _m.setX(_m.getX()-1);
        }
        else if (_murBas == true)
        {
            _m.setX(_m.getX()+1);
        }
        else
        {
            switch (_positionPrecedante)
            {
                case 1: //droite
                    _m.setX(_m.getX()+1);

                case 2: //gauche
                    _m.setX(_m.getX()-1);

                case 3: //bas
                    _m.setY(_m.getY()+1);

                case 4: //haut
                    _m.setY(_m.getY()-1);
            }
        }
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
    if (_a.isConnected())
    {
        setJoystick();
        
    }
    deplacerJoueur();

    // Pause pour limiter la vitesse d'affichage
    Sleep(200); // Utilisation de Sleep() pour introduire un délai de 5 millisecondes
}
