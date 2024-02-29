/* Fichier : main.cpp
Description : Fichier d'en-tête du main
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "game.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    

    game g;
    g.actualiserMur();
    while (true)
    {
        g.loop();
    } 
    return 0;
}
