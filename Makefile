main: main.o fenetre.o game.o
	g++ main.o fenetre.o game.o -o labyrinthus

main.o: main.cpp fenetre.h game.h
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp

game.o: game.cpp game.h
	g++ -c game.cpp

clean:
	rm -f *.o labyrinth