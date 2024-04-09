 /*Fichier : game.h
 Description : Fichier d'en-tête de la classe game
 Date : 2024-02-22
 Auteur : Bakayoko Kanvali*/

#ifndef GAME_H
#define GAME_H

// Déclaration avancée des classes
class personnage;
class monster;

#include <iostream>
#include <windows.h>
#include "ComArduino.h"
#include "fenetre.h"
#include <vector>
#include <cstdlib>
#include "monster.h"
#include <conio.h>
#include "Inventaire.h"
#include "Item.h"
#include "map.h"

// Nouvelle bibliothèque
#include <chrono> // Pour le timing
#include <thread> // Pour la pause
#include <cmath> // Pour la fonction abs()


using namespace std;

// Définition de la classe game
class game
{
private:
    int             _clavier;
    int             _vies;
    int             _positionPrecedante;
    int             _lastpx;
    int             _lastpy;

    const float     _seuilDistance = 8;
    const double    _seuilAccel = 4;

    bool            _longerMur;
    bool            _gameOver;    
    bool            _keyCollect;
    bool            _murDroite;
    bool            _murGauche;
    bool            _murHaut;
    bool            _murBas;
    bool            _clePossedee;

    fenetre         _f;
    personnage      _p;
    monster         _m;
    inventaire      _inv;
    ComArduino      _a;
    maps            _map;
    Position        _positionInitialeCle;

    const char* _cle = "\U0001F511";
    const char* _cr = "\u25A0 ";
    const char* _player = "\U0001F468";
    const char *_monster = "\U0001F47E";
    const char* _door = "\U0001F6AA";
    const char* _locker = "\U0001F5C4";


public:
    // Constructeur et destructeur
    game();
    ~game();

    // Accesseurs
    float distance;
    int getclavier() const;
    void setclavier();
    void setJoystick();

    // Nouvelle méthode
    void remettreClePositionInitiale(Position positionInitialeCle);
    void reinitialiserPositionJoueur();
    void mettreAJourVies(int changement);

    void vibreur();
    void libererDuMonstre();
    void getBouton();
    void checkLocker();

    // Méthodes
    void afficher() const;
    bool collision(int x, int y);
    void deplacerJoueur();
    void patrouillageMonster();
    void deplacerMonster();
    bool checkTriggerPoints();
    void poursuiteJoueur();

    void actualiserMap(string fichier);
    void ajoutCle();

    void loop();

    bool getGameOver();

};
#endif
