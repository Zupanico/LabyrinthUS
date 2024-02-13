# Makefile

main: main.o fenetre.o personnage.o
	g++ main.o fenetre.o personnage.o -o main -lncursesw

main.o: main.cpp fenetre.h personnage.h
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp
	
personnage.o: personnage.cpp personnage.h
	g++ -c personnage.cpp

clean:
	rm *.o main