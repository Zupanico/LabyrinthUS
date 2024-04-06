# Fichier : Makefile
# Description : Fichier makefile du projet Labyrinthus
# Date : 2024-02-22
# Auteur : Olympus

CXX = g++

main: main.o fenetre.o game.o personnage.o map.o monster.o  Inventaire.o Item.o SerialPort.o ComArduino.o
	$(CXX) main.o fenetre.o game.o personnage.o map.o monster.o Inventaire.o Item.o -o labyrinthus SerialPort.o ComArduino.o

SerialPort.o: ./include/serial/SerialPort.cpp ./include/serial/SerialPort.hpp
	$(CXX) -c ./include/serial/SerialPort.cpp

ComArduino.o: ComArduino.cpp ComArduino.h
	$(CXX) -c ComArduino.cpp

main.o: main.cpp fenetre.h game.h
	$(CXX) -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	$(CXX) -c fenetre.cpp

personnage.o: personnage.cpp personnage.h
	$(CXX) -c personnage.cpp

game.o: game.cpp game.h map.h monster.h fenetre.h
	$(CXX) -c game.cpp

map.o: map.cpp map.h
	$(CXX) -c map.cpp

monster.o: monster.cpp monster.h personnage.h
	$(CXX) -c monster.cpp

Inventaire.o: Inventaire.cpp Inventaire.h Item.h
	$(CXX) -c Inventaire.cpp

Item.o: Item.cpp Item.h
	$(CXX) -c Item.cpp

clean:
	rm -f *.o labyrinthus
