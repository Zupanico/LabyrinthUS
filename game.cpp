/*Fichier : game.cpp
Description : Fichier d'en-tête de la classe game
Date : 2024-02-22
Auteur : Olympus*/

#include "game.h"

game::game(int &argc, char **argv) : QApplication(argc, argv), _f(30, 30), _son(new son(this))
{
    _clavier = 0;
    _vies = 3;
    _gameOver = false;
    _keyCollect = false;
    _coinCollect = false;
    _flashCollect = false;
    _foodCollect = false;
    _sprint = false;

    _w.resetVies();
    _w.show();
    actualiserMap(_mapNiveau[getNiveau()]);

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
        if (_a.isConnected())
        {
            _a.setMessagesVies(0);
        }
        _gameOver = true;
    }
    else
    {
        if (_a.isConnected())
        {
            _a.setMessagesVies(_vies);
        }
    }
}


void game::setclavier()
{
    static int k = 0; // Déclarer k en tant que variable statique pour qu'elle conserve sa valeur entre les appels
    if (_kbhit())
    {
        int touche = _getch();
        if (touche == 'q' || touche == 'Q')
        {
            cout << "Quitter" << endl;
            exit(0);
        }
        if (touche == ' ')
        {
            checkLocker();
        }
        if (touche == 'c' || touche == 'C')
        {
            checkMachine();
        }
        if (touche == 'v' || touche == 'V')
        {
            sprint();
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
    if (_sprint == false)
    {
        _p.setVitesseX(joystickX);
        _p.setVitesseY(joystickY);
    }
    else if (_sprint == true)
    {
        _p.setVitesseX(joystickX*1.8);
        _p.setVitesseY(joystickY*1.8);
    }
}

void game::getBouton()
{

    if (_a.lireboutonDroite())
    {
        sprint();
    }
    if (_a.lireboutonGauche())
    {
        checkLocker();
    }
    if (_a.lireboutonHaut())
    {
        checkMachine();
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
        _son.playLockerOpen1();
        _p.setX(_lastpx);
        _p.setY(_lastpy);
    }
    else{
        if (_map.chercherLocker(_p.getX()+1, _p.getY()) || _map.chercherLocker(_p.getX()-1, _p.getY())
            || _map.chercherLocker(_p.getX(), _p.getY()+1) || _map.chercherLocker(_p.getX(), _p.getY()-1))
        {
            _son.playLockerClose1();
            _f.setEcran("  ", _p.getX(), _p.getY());
            _lastpx = _p.getX();
            _lastpy = _p.getY();
            _p.setX(-2);
            _p.setY(-2);
        }
    }
}

void game::checkMachine()
{   
    if (_map.chercherMachine(_p.getX()+1, _p.getY()) || _map.chercherMachine(_p.getX()-1, _p.getY())
        || _map.chercherMachine(_p.getX(), _p.getY()+1) || _map.chercherMachine(_p.getX(), _p.getY()-1)
        && _coinCollect == true) 
    {
        _son.playVendingMachine1();
        _foodCollect = true;
        _coinCollect = false;
    }
}

void game::sprint()
{
    if (_foodCollect == true)
    {
        _son.playEating1();
        _foodCollect = false;
        _sprint = true;
        _w.setSpeed(true);

        static QTimer powerUp;
        static QTimer emitTimer;
        powerUp.start(10000); // Start timer for 10 second cooldown period
        emitTimer.start(100);

        connect(&emitTimer, &QTimer::timeout, [&]() {
        _w.changerSizeBar();
        });

        connect(&powerUp, &QTimer::timeout, [&](){
            _sprint = false;
            _w.setSpeed(false);
            powerUp.stop();
            emitTimer.stop();
            });

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
    //_w.setShake(true);

    if (!_a.isConnected())
    {
        mettreAJourVies(-1);
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

    _w.setShake(false);
    _w.changerVies(-1);
    _son.playHeartbeat1();
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

    // Vérifier collection item
    if ((_p.getX() == _map.getCle().x && _p.getY() == _map.getCle().y && _keyCollect == false))
    {
        _son.playCollect1();
        _inv.addCle(new item(_cle));
        _keyCollect = true;
        _w.addMap(' ', _map.getCle().x, _map.getCle().y);
        _m.setX(_p.getX());
        _m.setY(_p.getY()-5);
        _m.setPoursuite(true);
    }

    if (_p.getX() == _map.getCoin().x && _p.getY() == _map.getCoin().y && _coinCollect == false)
    {
        _son.playCollect1();
        _inv.addCoin(new item(_coin));
        _coinCollect = true;
        _w.addMap(' ', _map.getCoin().x, _map.getCoin().y);
        _map.afficherCoin(-1, -1);
    }

    if (_p.getX() == _map.getFlash().x && _p.getY() == _map.getFlash().y && _flashCollect == false)
    {
        _son.playCollect1();
        _inv.addFlash(new item(_flash));
        _flashCollect = true;
        _w.addMap(' ', _map.getFlash().x, _map.getFlash().y);
    }

    //Actualiser les portes
    for (int i = 0; i < _map.getSizeDoor(); i++)
    {
        _f.setEcran(_door, _map.getDoor(i).x, _map.getDoor(i).y);
    }

    //Prochain Niveau
    if (_map.chercherNiveau(_p.getX(), _p.getY()))
    {
        prochainNiveau();
    }

    // Afficher le personnage sur la fenêtre
    _f.setEcran(_player, _p.getX(), _p.getY());
    _w.setPlayerPosition(_p.getX(), _p.getY());

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
        _p.setX(0);
        _p.setY(0);
        _w.setPlayerPosition(_p.getX(), _p.getY());
        mettreAJourVies(-1);
        _w.changerVies(-1);
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
    if (distanceX < range && mY == pY){
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
    if (distanceY < range && mX == pX){
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

int game::getNiveau() const
{
    return _niveau;
}

void game::prochainNiveau()
{
        cout << "PROCHAIN NIVEAU" << endl;
        _p.setX(0);
        _p.setY(0);
        _niveau++;
        _f.resetEcran();
        _w.emptyMap();
        _f.setEcran(_player, _p.getX(), _p.getY());
        _w.setPlayerPosition(_p.getX(), _p.getY());
        _w.resetVies();

        _keyCollect = false;
        _coinCollect = false;
        _flashCollect = false;
        _foodCollect = false;
        _sprint = false;
        _vies = 3;

        _w.setSpeed(false);

        for (int i = 0; i < 4; i++)
        {
            _inv.removeItem(i);
        }

        actualiserMap(_mapNiveau[getNiveau()]);
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

bool game::checkNiveau(int x, int y)
{
    return _map.chercherNiveau(x, y);
}

void game::actualiserMap(string fichier)
{
    // Charger la carte à partir du fichier
    _map.actualiserMap(fichier);

    for (int i = 0; i < _map.getSizeNiveau(); i++)
    {
        _w.addMap('n', _map.getNiveau(i).x, _map.getNiveau(i).y);
    }

    for (int i = 0; i < _map.getSizeMurs(); i++)
    {
        _f.setEcran(_cr, _map.getMur(i).x, _map.getMur(i).y);
        _w.addMap('w', _map.getMur(i).x, _map.getMur(i).y);
    }

    for (int i = 0; i < _map.getSizeDoor(); i++)
    {
        _f.setEcran(_door, _map.getDoor(i).x, _map.getDoor(i).y);
        _w.addMap('d', _map.getDoor(i).x, _map.getDoor(i).y);
    }

    for (int i = 0; i < _map.getSizeLocker(); i++)
    {
        _f.setEcran(_locker, _map.getLocker(i).x, _map.getLocker(i).y);
        _w.addMap('l', _map.getLocker(i).x, _map.getLocker(i).y);
    }

    _f.setEcran(_monster, _map.getM1().x, _map.getM1().y);
    _f.setEcran(_cle, _map.getCle().x, _map.getCle().y);
    _f.setEcran(_coin, _map.getCoin().x, _map.getCoin().y);
    _f.setEcran(_machine, _map.getMachine().x, _map.getMachine().y);
    _f.setEcran(_flash, _map.getFlash().x, _map.getFlash().y);
    _w.addMap('k', _map.getCle().x, _map.getCle().y);
    _w.addMap('c', _map.getCoin().x, _map.getCoin().y);
    _w.addMap('m', _map.getMachine().x, _map.getMachine().y);
    _w.addMap('f', _map.getFlash().x, _map.getFlash().y);
    _m.setX(_map.getM1().x);
    _m.setY(_map.getM1().y);
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

    // Collision avec la porte
    else if (_map.chercherDoor(x, y))
    {
        if (_keyCollect == false)
        {
            // Ramener le joueur à sa position précédente
            return true;
        }
        else
        {
            // Désactive le monstre
            _m.setActif(false);
            return false;
        }
    }

    else if (_map.chercherLocker(x, y))
    {
        return true;
    }

    else if (_map.chercherMachine(x, y))
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
void game::afficher()
{
    _w.afficherMap();
    // Effacer l'écran
    COORD _pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _pos); // Positionne le curseur en haut à gauche de la fenêtre

    // Afficher le titre du jeu
    cout << "                     LABYRINTHUS" << endl;

    _f.print(cout);

    cout << "Coordonnées du personnage :  (" << _p.getX() << ", " << _p.getY() << ")" << endl;
    cout << "Coordonnées du monstre : (" << _m.getX() << ", " << _m.getY() << ")" << endl;

    cout << "Vies du joueur : " << _vies << endl;
    
    // Afficher l'inventaire du joueur
    _inv.afficherInventaire();
}

void game::loop()
{

    QTimer timer; // Create a QTimer object for periodic updates
    QObject::connect(&timer, &QTimer::timeout, this, &game::updateGame); // Connect the QTimer's timeout signal to the updateGame slot
    timer.start(1000 / 30); // Start the timer to update the game approximately 60 times per second

    // Start the event loop
    exec(); // Assuming game inherits from QApplication or QCoreApplication
    
}

void game::updateGame()
{
    // Update game state and perform game logic here
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
        if (_m.getPoursuite()==true)
        {
            poursuiteJoueur();
        } 
        else 
        {
            _m.patrol();
        }
        deplacerMonster();
    }

    if (_flashCollect == true)
    {
        _w.setFlash(true);
    }
    else if (_flashCollect == false)
    {
        _w.setFlash(false);
    }

    if (_keyCollect == true)
    {
        _w.setKey(true);
    }
    else if (_keyCollect == false)
    {
        _w.setKey(false);
    }

    if (_coinCollect == true)
    {
        _w.setCoin(true);
    }
    else if (_coinCollect == false)
    {
        _w.setCoin(false);
    }

    if (_foodCollect == true)
    {
        _w.setFood(true);
    }
    else if (_foodCollect == false)
    {
        _w.setFood(false);
    }

    if (_map.chercherMachine(_p.getX()+1, _p.getY()) || _map.chercherMachine(_p.getX()-1, _p.getY())
        || _map.chercherMachine(_p.getX(), _p.getY()+1) || _map.chercherMachine(_p.getX(), _p.getY()-1)
        && _coinCollect == true) 
    {
        _w.setMachine(true);
    }
    else
    {
        _w.setMachine(false);
    }

    if (_map.chercherLocker(_p.getX()+1, _p.getY()) || _map.chercherLocker(_p.getX()-1, _p.getY())
        || _map.chercherLocker(_p.getX(), _p.getY()+1) || _map.chercherLocker(_p.getX(), _p.getY()-1))
    {
        _w.setLocker(true);
    }
    else
    {
        _w.setLocker(false);
    }

    _w.setMonsterPosition(_m.getX(), _m.getY());

    // Check for game over condition and stop the game loop if true
    if (_gameOver == true) {

        _clavier = 0;
        _vies = 3;
        _gameOver = false;
        _keyCollect = false;
        _coinCollect = false;
        _flashCollect = false;
        _foodCollect = false;
        _sprint = false;

        _w.resetVies();
        _w.show();
        actualiserMap(_mapNiveau[getNiveau()]);

        /*
        // Stop the game loop
        QTimer* timer = qobject_cast<QTimer*>(sender()); // Get the sender object (the timer)
        if (timer)
        {
            timer->stop(); // Stop the timer
            QObject::disconnect(timer, &QTimer::timeout, this, &game::updateGame); // Disconnect the timeout signal
        }*/
    }
    // Update GUI
    afficher();
}

bool game::eventFilter(QObject *obj, QEvent *event)
{
    static bool lockerChecked = false; // Track if checkLocker() has been called
    static QTimer delay; // Timer for cooldown period

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
            case Qt::Key_Q:
                qDebug() << "Quitter";
                exit(0);
                break;
            case Qt::Key_Space:
                if (!lockerChecked) {
                    checkLocker();
                    lockerChecked = true; // Mark checkLocker() as called
                    delay.start(100); // Start timer for 0.1 second cooldown period
                    connect(&delay, &QTimer::timeout, [&](){
                        lockerChecked = false; // Reset lockerChecked after cooldown period
                        delay.stop();
                    });
                }
                break;
            case Qt::Key_C:
                checkMachine();
                break;
            case Qt::Key_V:
                sprint();
                break;
            case Qt::Key_Up:
                if (_sprint == false)
                {
                    _p.setVitesseY(-100);
                    _p.setVitesseX(0);
                }
                else if (_sprint == true)
                {
                    _p.setVitesseY(-180);
                    _p.setVitesseX(0); 
                }
                break;
            case Qt::Key_Down:
                if (_sprint == false)
                {
                    _p.setVitesseY(100);
                    _p.setVitesseX(0);
                }
                else if (_sprint == true)
                {
                    _p.setVitesseY(180);
                    _p.setVitesseX(0);
                }
                break;
            case Qt::Key_Right:
                if (_sprint == false)
                {
                    _p.setVitesseX(100);
                    _p.setVitesseY(0);
                }
                else if (_sprint == true)
                {
                    _p.setVitesseX(180);
                    _p.setVitesseY(0);
                }
                break;
            case Qt::Key_Left:
                if (_sprint == false)
                {
                    _p.setVitesseX(-100);
                    _p.setVitesseY(0);
                }
                else if (_sprint == true)
                {
                    _p.setVitesseX(-180);
                    _p.setVitesseY(0);
                }
                break;
            default:
                break;
        }
    }

    // Call the base class implementation for other events
    return QApplication::eventFilter(obj, event);
}
