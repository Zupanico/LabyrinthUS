// Fichier : fenetre.h
// Description : Fichier d'en-tête de la classe Fenetre
// Date : 2024-02-10
// Auteur : Nicolas Garant

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif


#ifdef _WIN32
_setmode(_fileno(stdout), _O_U16TEXT);
#endif

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
    void afficher() const;
};
