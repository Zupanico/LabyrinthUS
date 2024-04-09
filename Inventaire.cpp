// Fichier : Inventaire.cpp
// Description : Fichier source de la classe inventaire
// Date : 2024-02-24
// Auteur : Evan Frappier

#include "Inventaire.h"

inventaire::inventaire()
{
	_selectedSlot = 0;
	_taille = 0;
}

inventaire::~inventaire()
{
}

int inventaire::getCapacite()
{
	return MAX_ITEMS;
}

item* inventaire::getItem(int index) const
{
	return _inventaire[index];
}

void inventaire::selectSlot(int index)
{
	_selectedSlot = index;
}

int inventaire::inventairePlein()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (_inventaire[i] == NULL)
		{
			return 0;
		}
	}
	return 1;
}

bool inventaire::estCle()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (_inventaire[i] != NULL && _inventaire[i]->getNom() == "cle")
		{
			return true;
		}
	}
	return false;
}

void inventaire::afficherInventaire() const
{
	cout << "Inventaire :";
	for (int i = 0; i < _taille; i++)
	{
		cout << " " << _inventaire[i]->getNom();
	}
	cout << endl;
}

void inventaire::removeItem() 
{
     for (int i = 0; i < MAX_ITEMS; i++) 
	 {
        if (_inventaire[i] != nullptr && _inventaire[i]->getNom() == "cle") 
		{
            delete _inventaire[i]; // Supprime l'objet pour éviter les fuites de mémoire.
            _inventaire[i] = nullptr; // Enlève l'item de l'inventaire en mettant son emplacement à nullptr.

            break; // Sort de la boucle après avoir trouvé et retiré la clé.
        }
    }
}

void inventaire::addItem(item* item)
{
	_inventaire[_taille] = item;
	_taille++;
}

void inventaire::operator ++()
{
	_selectedSlot++ % MAX_ITEMS;
}