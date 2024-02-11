# Makefile

main: main.o fenetre.o
	g++ main.o fenetre.o -o main

main.o: main.cpp fenetre.h
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp

clean:
	rm *.o main