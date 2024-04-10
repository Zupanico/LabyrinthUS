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
#include "MainWindow.h"
#include <QTimer>
#include <QApplication>

// Nouvelle bibliothèque
#include <chrono> // Pour le timing
#include <thread> // Pour la pause
#include <cmath>  // Pour la fonction abs()

using namespace std;

// Définition de la classe game
class game : public QApplication
{
    Q_OBJECT
private:
    int _clavier;
    int _vies;

    int _niveau = 0;

    fenetre         _f;
    personnage      _p;
    monster         _m;
    inventaire      _inv;
    ComArduino      _a;

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

    maps _map;
    bool _keyCollect;
    bool _coinCollect;
    bool _flashCollect;
    bool _foodCollect;
    bool _checkmachine;
    bool _choixfood;
    bool _choixvies;

    int _lastpx;
    int _lastpy;

    string _mapNiveau[3]={"map1.txt", "map2.txt", "map3.txt"};
    MainWindow _w;



public:
    // Constructeur et destructeur
    game(int &argc, char **argv);
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

    bool getGameOver();

public slots:
    void loop();
    void updateGame();

};

#endif
