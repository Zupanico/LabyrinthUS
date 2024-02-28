/*Fichier: monster.cpp
Description : Fichier d'en-tête de la classe monster
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "monster.h"

// Constructeur
monster::monster() : Se_Deplace(false)
{
    
}

// Destructeur
monster::~monster()
{
    Arreter_Deplacement_continu();
}

// Méthode pour démarrer le déplacement continu du monstre
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

// Méthode pour arrêter le déplacement continu du monstre
void monster::Arreter_Deplacement_continu()
{
      Se_Deplace = false;
    if (Deplacement_Continu.joinable()) 
    {
        Deplacement_Continu.join(); // Attendre que le thread de déplacement se termine
    }
}

// Méthode pour poursuivre le joueur
void monster::Poursuivre_Joueur(int joueurX, int joueurY)
{
    // Récupérer les coordonnées actuelles du monstre
    int monsterX = getX();
    int monsterY = getY();

    // Calculer le déplacement du monstre vers le joueur
    // déplacer le monstre d'une case vers le joueur
    if (abs(monsterX - joueurX) > abs(monsterY - joueurY))
    {
        if (monsterX < joueurX) 
        {
            setX(monsterX + 1); // Déplacer le monstre vers la droite
        } 
        else if (monsterX > joueurX) 
        {
            setX(monsterX - 1); // Déplacer le monstre vers la gauche
        }
        else
        {
            if (monsterY < joueurY) 
            {
                setY(monsterY + 1); // Déplacer le monstre vers le bas
            } 
            else if (monsterY > joueurY) 
            {
                setY(monsterY - 1); // Déplacer le monstre vers le haut
            }
        }
    }
    else
    {
        if (monsterY < joueurY) 
        {
            setY(monsterY + 1); // Déplacer le monstre vers le bas
        } 
        else if (monsterY > joueurY) 
        {
            setY(monsterY - 1); // Déplacer le monstre vers le haut
        }
    }    
}

// Méthode pour déplacer le monstre vers le joueur
void monster::Deplacement_vers_pers(const personnage& joueur)
{
    int joueurX = joueur.getX();
    int joueurY = joueur.getY();
    
    // Poursuivre le joueur (déplacer le monstre vers le joueur
    Poursuivre_Joueur(joueurX, joueurY); 
}