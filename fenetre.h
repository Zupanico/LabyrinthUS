/* Fichier : fenetre.h
Description : Fichier d'en-tête de la classe fenetre
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <windows.h>
#include <iostream>
#include <string>

#define MAX_HAUTEUR  100
#define MAX_LARGEUR  100

#define RESET "\033[0m"
#define VERT "\033[32m"
#define ROUGE "\033[31m" 
#define BLEU  "\033[34m"
#define JAUNE "\033[33m"
#define CYAN  "\033[36m"
#define MAGENTA "\033[35m"
#define BLANC "\033[37m"

using namespace std;
class fenetre
{
private:

    int _largeur;
    int _hauteur;

    const char* _ecran[MAX_HAUTEUR][MAX_LARGEUR]; 
    const char * _cr = "\u25A0";

public:
    // Constructeur et destructeur
    fenetre(int largeur, int hauteur);
    ~fenetre();

    // Accesseurs
    int getLargeur() const;
    int getHauteur() const;

    void setEcran(const char* c, int row, int column);
    const char* getEcran(int row, int column) const;

    // Méthodes
    void print(ostream &output) const;
};
