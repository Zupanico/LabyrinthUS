// Fichier : fenetre.h
// Description : Fichier d'en-tête de la classe Fenetre
// Date : 2024-02-10
// Auteur : Nicolas Garant
#include <Windows.h>
class fenetre
{
private:
    int _largeur;
    int _hauteur;
    const char * _cr = "\u25A0";

public:
    // Constructeur et destructeur
    fenetre(int largeur, int hauteur);
    ~fenetre();

    // Accesseurs
    int getLargeur() const;
    int getHauteur() const;

    // Méthodes
    void print(ostream &output) const;
};
