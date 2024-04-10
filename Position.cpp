// Position.cpp
/*Fichier: Position.cpp
Description : Fichier d'en-tête de la classe Position
Date : 2024-03-31
Auteur : Bakayoko Kanvali*/

#include "Position.h"

Position::Position() : x(0), y(0) {} // Constructeur par défaut

Position::Position(int x, int y) : x(x), y(y) {} // Constructeur avec paramètres

void Position::setX(int newX) { x = newX; }

void Position::setY(int newY) { y = newY; }

int Position::getX() const { return x; }

int Position::getY() const { return y; }
