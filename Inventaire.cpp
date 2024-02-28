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

void inventaire::selectSlot(int index)
{
	_selectedSlot = index;
}

void inventaire::removeItem()
{
	_inventaire[_selectedSlot] = NULL;
}

void inventaire::dropItem()
{
	_inventaire[_selectedSlot] = NULL;
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
	for (int i = 0; i < _taille; i++)
	{
		cout << " " << _inventaire[i]->getNom();
	}
	cout << endl;
}

void inventaire::addItem(item* item)
{

	_inventaire[_taille] = item;
	_taille++;

/*	if (inventairePlein() == 1)
	{
		dropItem();
		_inventaire[_selectedSlot] = item;
		_taille++;
	}
	else
	{
		if (_inventaire[_selectedSlot] != NULL)
		{
			_inventaire[_selectedSlot] = item;
			_taille++;
		}
		else
		{
			for (int i = 0; i < MAX_ITEMS; i++)
			{
				if (_inventaire[i] != NULL)
				{
					_inventaire[i] = item;
					_taille++;
					_selectedSlot = i;
				}
			}
		}
	} */
}

void inventaire::operator ++()
{
	_selectedSlot++ % MAX_ITEMS;
}