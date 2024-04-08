TEMPLATE = app
TARGET = Labyrinthus
CONFIG += warn_on qt debug windows console
INCLUDEPATH += . ./include ./include/serial

QT += widgets multimedia

# Input
HEADERS = ComArduino.h fenetre.h game.h Inventaire.h Item.h map.h monster.h ./include/json.hpp ./include/serial/SerialPort.hpp personnage.h MainWindow.h
SOURCES = ComArduino.cpp fenetre.cpp game.cpp Inventaire.cpp Item.cpp main.cpp map.cpp monster.cpp ./include/serial/SerialPort.cpp personnage.cpp MainWindow.cpp