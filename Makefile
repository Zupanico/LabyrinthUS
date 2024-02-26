# Fichier : Makefile
# Description : Fichier d'en-tête du projet Labyrinthus
# Date : 2024-02-22
# Auteur : Bakayoko Kanvali

main: main.o fenetre.o game.o personnage.o mur.o clee.o monster.o
	g++ main.o fenetre.o game.o personnage.o mur.o clee.o monster.o -o labyrinthus

main.o: main.cpp fenetre.h game.h personnage.h mur.h clee.h monster.h
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp

personnage.o: personnage.cpp personnage.h
	g++ -c personnage.cpp

game.o: game.cpp game.h
	g++ -c game.cpp

mur.o: mur.cpp mur.h
	g++ -c mur.cpp

clee.o: clee.cpp clee.h
	g++ -c clee.cpp
	
monster.o: monster.cpp monster.h
	g++ -c monster.cpp
	
clean:
	rm -f *.o labyrinthus