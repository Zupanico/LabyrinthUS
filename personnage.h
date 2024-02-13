// Fichier: personnage.h
// Description: Fichier d'en-tête de la classe Personnage
// Date: 2024-02-12
// Auteur: Nicolas Garant

// =========================

class personnage
{
private:
    int _x = 0;
    int _y = 0;
public:
    const char *_cr = "\u25A0";
    
    personnage();
    ~personnage();
};

