# Fichier : Makefile
# Description : Fichier d'en-tête du projet Labyrinthus
# Date : 2024-02-22
# Auteur : Bakayoko Kanvali

main: main.o fenetre.o game.o personnage.o mur.o clee.o monster.o portail.o
	g++ main.o fenetre.o game.o personnage.o mur.o clee.o monster.o portail.o -o labyrinthus

main.o: main.cpp fenetre.h game.h 
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp

personnage.o: personnage.cpp personnage.h
	g++ -c personnage.cpp

game.o: game.cpp game.h mur.h monster.h fenetre.h
	g++ -c game.cpp

mur.o: mur.cpp mur.h
	g++ -c mur.cpp

clee.o: clee.cpp clee.h
	g++ -c clee.cpp
	
monster.o: monster.cpp monster.h personnage.h
	g++ -c monster.cpp

portail.o: portail.cpp portail.h
	g++ -c portail.cpp
	
clean:
	rm -f *.o labyrinthus