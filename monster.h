/*Fichier: monster.h
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#ifndef MONSTER_H
#define MONSTER_H

// Déclaration avancée des classes
class game;
class personnage;

#include <windows.h>
#include <iostream>

#include "personnage.h"
#include <thread>
#include <chrono>

using namespace std;

class monster : public personnage
{
private:
    thread Deplacement_Continu; // Thread pour le déplacement continu du monstre
    bool Se_Deplace; // Indicateur pour savoir si le monstre est en mouvement
    void Deplacement_vers_pers(const personnage& joueur); // Méthode pour déplacer le monstre vers le joueur
    

public:
    monster();
    ~monster();
    void Demarrage_Deplacement_continu(const personnage& joueur); // Méthode pour démarrer le déplacement continu du monstre
    void Arreter_Deplacement_continu(); // Méthode pour arrêter le déplacement continu du monstre
};
#endif
