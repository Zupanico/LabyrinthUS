/*Fichier : game.h
 Description : Fichier d'en-tête de la classe game
 Date : 2024-02-22
 Auteur : Bakayoko Kanvali*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QObject>
#include <windows.h>
#include "ComArduino.h"
#include "fenetre.h"
#include <vector>
#include <cstdlib>
#include "monster.h"
#include <conio.h>
#include "Inventaire.h"
#include "map.h"
#include <chrono>
#include <thread>
#include <cmath>

class Authentification;
class Window;

// Définition de la classe game
class game : public QObject
{
    Q_OBJECT;

private:
    int _clavier;
    int _vies;

    int _niveau = 0;

    fenetre         _f;
    personnage      _p;
    monster         _m;
    inventaire      _inv;
    ComArduino      _a;
    maps            _map;
    Window*         _w;
    const char* _cle = "\U0001F511";
    const char* _cr = "\u25A0 ";
    const char* _player = "\U0001F468";
    const char* _monster = "\U0001F47E";
    const char* _door = "\U0001F6AA";
    const char* _locker = "\U0001F5C4 ";
    const char* _coin = "\U0001FA99";
    const char* _machine = "\U0001F4F1";
    const char* _flash = "\U0001F526";
    const char* _heart = "\U00002764";
    const char* _food = "\U0001F36B";

    bool _gameOver;

    bool _keyCollect;
    bool _coinCollect;
    bool _flashCollect;
    bool _foodCollect;
    bool _checkmachine;
    bool _choixfood;
    bool _choixvies;

    int _lastpx;
    int _lastpy;

    string _mapNiveau[3] = { "map1.txt", "map2.txt", "map3.txt" };
    

public:
    // Constructeur et destructeur
    explicit game(QObject* parent = nullptr);
    ~game();

    // Clavier
    int getclavier() const;
    void setclavier();
    void setJoystick();

    // Manette
    void getBouton();

    // Joueur
    void reinitialiserPositionJoueur();
    void mettreAJourVies(int changement);
    void libererDuMonstre();
    void checkLocker();
    void checkMachine();

    bool getGameOver();

    // Méthodes
    void deplacerJoueur();

    // Monstre
    void patrouillageMonster();
    void deplacerMonster();
    void poursuiteJoueur();

    // Map
    bool collision(int x, int y);
    bool checkTriggerPoints();
    void actualiserMap(string fichier);
    bool checkNiveau(int x, int y);
    int getNiveau() const;
    void prochainNiveau();

    // Jeu
    void afficher();

public slots:
    void updateGame();
    void GameOver();
};

#endif
