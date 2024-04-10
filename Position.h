/*Fichier: Position.h
Description : Fichier d'en-tête de la classe Position
Date : 2024-03-31
Auteur : Bakayoko Kanvali*/


#ifndef POSITION_H // Directives de préprocesseur pour éviter les inclusions multiples
#define POSITION_H

struct Position {
    int x;
    int y;

    Position(); // Constructeur par défaut
    Position(int x, int y); // Constructeur avec paramètres

    void setX(int newX);
    void setY(int newY);

    int getX() const;
    int getY() const;
};

#endif // POSITION_H
