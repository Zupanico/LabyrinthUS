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

    fenetre         _f;
    personnage      _p;
    monster         _m;
    inventaire      _inv;
    ComArduino      _a;

    const char* _cle = "\U0001F511";
    const char* _cr = "\u25A0 ";
    const char* _player = "\U0001F468";
    const char *_monster = "\U0001F47E";
    const char* _door = "\U0001F6AA";
    const char* _locker = "\U0001F5C4 ";
    const char* _coin = "\U0001FA99";
    const char* _machine = "\U0001F4F1";
    const char* _flash = "\U0001F526";
    const char* _heart = "\U00002764";
    const char* _food = "\U0001F36B";

    bool _gameOver;

    maps _map;
    bool _keyCollect;
    bool _coinCollect;
    bool _flashCollect;
    bool _foodCollect;

    int _lastpx;
    int _lastpy;

public:
    // Constructeur et destructeur
    game();
    ~game();

    // Accesseurs
    int getclavier() const;
    void setclavier();
    void setJoystick();   

    // Nouvelle méthode
    void reinitialiserPositionJoueur();
    void mettreAJourVies(int changement);

    void libererDuMonstre();
    void getBouton();
    void checkLocker();
    void checkMachine();


    // Méthodes
    void afficher() const;
    void deplacerJoueur();

    void deplacerMonster();
    void patrouillageMonster();
    bool checkTriggerPoints();
    void poursuiteJoueur();

    void actualiserMap(string fichier);

    bool collision(int x, int y);
    void loop();

    bool getGameOver();
};
#endif
