#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <QApplication>
#include "Play.h"


void HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO _info;
    _info.dwSize = 100;
    _info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_info);
}

int main(int argc, char* argv[])
{
    system("cls");
    HideConsoleCursor(); // Appel de la fonction pour masquer le curseur
    SetConsoleOutputCP(CP_UTF8);

    QApplication app(argc, argv);
    Play play;
    play.show();

    return app.exec();
}
