# Fichier : Makefile
# Description : Fichier makefile du projet Labyrinthus
# Date : 2024-02-22
# Auteur : Olympus
 
main: main.o fenetre.o game.o personnage.o map.o monster.o  Inventaire.o Item.o SerialPort.o ComArduino.o
	g++ main.o fenetre.o game.o personnage.o map.o monster.o Inventaire.o Item.o -o labyrinthus SerialPort.o ComArduino.o
 
SerialPort.o: ./include/serial/SerialPort.cpp ./include/serial/SerialPort.hpp
	g++ -c ./include/serial/SerialPort.cpp
 
ComArduino.o: ComArduino.cpp ComArduino.h 
	g++ -c ComArduino.cpp
 
main.o: main.cpp fenetre.h game.h 
	g++ -c main.cpp
 
fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp
 
personnage.o: personnage.cpp personnage.h
	g++ -c personnage.cpp

game.o: game.cpp game.h map.h monster.h fenetre.h
	g++ -c game.cpp

map.o: map.cpp map.h
	g++ -c map.cpp

monster.o: monster.cpp monster.h personnage.h
	g++ -c monster.cpp
 
Inventaire.o: Inventaire.cpp Inventaire.h Item.h
	g++ -c Inventaire.cpp
 
Item.o: Item.cpp Item.h
	g++ -c Item.cpp

clean:
	del *.o labyrinthus
