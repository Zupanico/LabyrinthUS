/*Fichier: monster.cpp
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "monster.h"

monster::monster() : Se_Deplace(false)
{
}

monster::~monster()
{
    Arreter_Deplacement_continu();
}

void monster::Deplacement_vers_pers(const personnage& joueur)
{
    int joueurX = joueur.getX();
    int joueurY = joueur.getY();

    // Récupérer les coordonnées actuelles du monstre
    int monsterX = getX();
    int monsterY = getY();

    // Calculer le déplacement du monstre vers le joueur
    // déplacer le monstre d'une case vers le joueur
    if (monsterX < joueurX) 
    {
        setX(monsterX + 1); // Déplacer le monstre vers la droite
    } 
    else if (monsterX > joueurX) 
    {
        setX(monsterX - 1); // Déplacer le monstre vers la gauche
    }

    if (monsterY < joueurY) 
    {
        setY(monsterY + 1); // Déplacer le monstre vers le bas
    } 
    else if (monsterY > joueurY) 
    {
        setY(monsterY - 1); // Déplacer le monstre vers le haut
    }
}

void monster::Demarrage_Deplacement_continu(const personnage& joueur)
{
    // Vérifier si le monstre est déjà en mouvement
    if (!Se_Deplace) 
    {
        Se_Deplace = true;
        Deplacement_Continu = thread([this, &joueur]() 
        {
            while (Se_Deplace) 
            {
                Deplacement_vers_pers(joueur); // Déplacer le monstre vers le joueur
                this_thread::sleep_for(chrono::milliseconds(500)); // Attendre un certain délai entre les déplacements
            }
        });
        Deplacement_Continu.detach(); // Détacher le thread pour qu'il s'exécute en arrière-plan
    }
}

void monster::Arreter_Deplacement_continu()
{
      Se_Deplace = false;
    if (Deplacement_Continu.joinable()) 
    {
        Deplacement_Continu.join(); // Attendre que le thread de déplacement se termine
    }
}