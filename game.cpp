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
        _a.setMessagesVies(0);
        _gameOver = true;
    }
    else
    {
        _a.setMessagesVies(_vies);
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
        if (touche == ' ')
        {
            checkLocker();
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

void game::getBouton()
{
    
    if (_a.lireboutonDroite())
    {}
    if (_a.lireboutonGauche())
    {}
    if (_a.lireboutonHaut())
    {
        checkLocker();
    }
    if (_a.lireboutonBas())
    {}
    if (_a.lireboutonjoystick())
    {}
}

void game::checkLocker()
{
    if (_p.getX() == -2 && _p.getY() == -2)
    {
        _p.setX(_lastpx);
        _p.setY(_lastpy);
    }
    else{
        if (_map.chercherLocker(_p.getX()+1, _p.getY()) || _map.chercherLocker(_p.getX()-1, _p.getY())
            || _map.chercherLocker(_p.getX(), _p.getY()+1) || _map.chercherLocker(_p.getX(), _p.getY()-1))
        {
            _f.setEcran("  ", _p.getX(), _p.getY());
            _lastpx = _p.getX();
            _lastpy = _p.getY();
            _p.setX(-2);
            _p.setY(-2);
        }
    }
}


void game::vibreur()
{
    if (_a.isConnected())
    {                    
        float distance = sqrt(pow(_p.getX() - _m.getX(), 2) + pow(_p.getY() - _m.getY(), 2));
        // Activer ou désactiver la vibration basée sur la distance
        _a.setMessagesDistance(distance <= _seuilDistance ? distance : 0.0);
    }
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
    Sleep(2000); // Attendre 2 secondes

    cout << "       Tournez rapidement la manette dans tous les sens pour vous libérer !" << endl;
    Sleep(2000); // Attendre 2 secondes

    cout << "                    Vous avez 10 secondes pour vous libérer !" << endl;
    Sleep(4000); // Attendre 4 secondes

    auto start = chrono::steady_clock::now();

    while (true) 
    {   
        vibreur();
        
        auto valeursAccelerometre = _a.lireAccelerometre();
        double normeAccel = sqrt(pow(std::get<0>(valeursAccelerometre), 2) + pow(std::get<1>(valeursAccelerometre), 2) + pow(std::get<2>(valeursAccelerometre), 2)); 

        if (normeAccel > _seuilAccel) 
        {
            mettreAJourVies(-1);
            reinitialiserPositionJoueur();
            cout << "Vous vous êtes libéré du monstre mais vous avez perdu une vie !" << endl;
            Sleep(2000); // Attendre 2 secondes
            system("cls");
            break;
        }

        auto end = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(end - start).count() >= 10) // Si le temps dépasse 10 secondes
        {
            _vies = 0;
            _gameOver = true;
            cout << "Vous n'avez pas réussi à vous libérer à temps. Vous avez perdu toutes vos vies !" << endl;
            Sleep(2000); // Attendre 2 secondes
            system("cls");
            break;
        }

        Sleep(500); // Pause pour la prochaine lecture
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
            _m.setPoursuite(true);
            checkTriggerPoints();
        }
    //Actualiser les portes
    for (int i = 0; i < _map.getSizeDoor(); i++)
    {
        _f.setEcran(_door, _map.getDoor(i).x, _map.getDoor(i).y);
    }
    // Afficher le personnage sur la fenêtre
    _f.setEcran(_player, _p.getX(), _p.getY());
 
    // Afficher le jeu complet
    afficher();   
}

void game::reinitialiserPositionJoueur()
{
    int distanceMax = 15; // Définir la distance maximale de réinitialisation
    int newX, newY;
    int maxTentatives = 100; // Limite le nombre de tentatives pour éviter une boucle infinie
    bool positionValide = false;

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
    int mX = _m.getX();     // X du monstre
    int mY = _m.getY();     // Y du monstre

    int pX = _p.getX();     // X du joueur
    int pY = _p.getY();     // Y du joueur

    int range = _m.getRange();  // Portée du monstre


    int distanceX = abs(mX - pX);
    int distanceY = abs(mY - pY);

    // Si le monstre est à portée du joueur en X
    if( distanceX < range && mY == pY){
        for (int i = 0; i < distanceX; i++)
        {
            if (mX < pX && !collision(mX + i, mY))
            {
                _m.setPoursuite(true);
            }

            if (mX > pX && !collision(mX - i, mY))
            {
                _m.setPoursuite(true);
            }
            
        }
    }

    // Si le monstre est à portée du joueur en Y
    if( distanceY < range && mX == pX){
        for (int i = 0; i < distanceY; i++)
        {
            if (mY < pY && !collision(mX, mY + i))
            {
                _m.setPoursuite(true);
            }

            if (mY > pY && !collision(mX, mY - i)){
                _m.setPoursuite(true);
            }
        }
    }
    else if (distanceY > range || distanceX > range)
    {
        _m.setPoursuite(false);
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

void game::poursuiteJoueur()
{
    int mX = _m.getX(); // X du monstre
    int mY = _m.getY(); // Y du monstre

    int pX = _p.getX(); // X du joueur
    int pY = _p.getY(); // Y du joueur

    int range = _m.getRange(); // Portée du monstre

    int distanceX = abs(mX - pX);
    int distanceY = abs(mY - pY);

    // Joueur en bas
    if (mY < pY && mX == pX){
        _m.poursuivreJoueur(2);
    }
    // Joueur en haut
    if (mY > pY && mX == pX){
        _m.poursuivreJoueur(3);
    }
    // Joueur à gauche
    if (mX > pX && mY == pY){
        _m.poursuivreJoueur(1);
    }
    // Joueur à droite
    if (mX < pX && mY == pY){
        _m.poursuivreJoueur(4);
    }

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

    // Afficher le titre du jeu
    cout << "                     LABYRINTHUS" << endl;

    _f.print(cout);

    cout << "Coordonnées du personnage :  (" << _p.getX() << ", " << _p.getY() << ")" << endl;
    cout << "Coordonnées du monstre : (" << _m.getX() << ", " << _m.getY() << ")" << endl;

    cout << "Vies du joueur : " << _vies << endl;
    // Afficher les coordonnées du personnage

    // Afficher l'inventaire du joueur
    _inv.afficherInventaire();
}

void game::loop()
{
    setclavier();

    if (_a.isConnected())
    {
        _a.setMessagesVies(_vies);
        _a.setMessages();
        setJoystick();
        getBouton();
        vibreur();
    }

    deplacerJoueur();

    if (_m.getActif())
    {
        patrouillageMonster();

        if (_m.getPoursuite())
        {
            poursuiteJoueur();
        }
        else
        {
            _m.patrol();
        }

        deplacerMonster();   
    }
    
    Sleep(10);
}
