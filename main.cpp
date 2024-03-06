/* Fichier : main.cpp
Description : Fichier d'en-tête du main
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include <string>
#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

void HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO _info; 
    _info.dwSize = 100; 
    _info.bVisible = FALSE; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_info);
}

int main(int argc, char const *argv[])
{
    system("cls"); 
    HideConsoleCursor();
    SetConsoleOutputCP(CP_UTF8);
    
    game g;
    g.actualiserMur();
    while (true && !g.getGameOver())
    {
        g.loop();
    }

    cout << "=================== Game Over!===================" << endl;
    return 0;
}
