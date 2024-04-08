// Fichier : Inventaire.cpp
// Description : Fichier source de la classe inventaire
// Date : 2024-02-24
// Auteur : Evan Frappier

#include "Inventaire.h"

using namespace std;

inventaire::inventaire()
{
	_selectedSlot = 0;
	_taille = 0;

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		_inventaire[i] = new item(" ");
	}
}

inventaire::~inventaire()
{
}

int inventaire::getCapacite()
{
	return MAX_ITEMS;
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

void inventaire::afficherInventaire() const
{
	cout << "Inventaire :";
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		cout << " " << _inventaire[i]->getNom();
	}
	cout << endl;
}

void inventaire::addCle(item* item)
{
	_inventaire[0] = item;
	_taille++;
}

void inventaire::addFlash(item* item)
{
	_inventaire[1] = item;
	_taille++;
}

void inventaire::addCoin(item* item)
{
	_inventaire[2] = item;
	_taille++;
}

void inventaire::removeItem(int index)
{
	_inventaire[index] = new item(" ");
	_taille--;
}

void inventaire::operator ++()
{
	_selectedSlot++ % MAX_ITEMS;
}
