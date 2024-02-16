main: main.o fenetre.o game.o
	g++ main.o fenetre.o game.o -o labyrinthus

main.o: main.cpp fenetre.h game.h personnage.h
	g++ -c main.cpp

fenetre.o: fenetre.cpp fenetre.h
	g++ -c fenetre.cpp

personnage.o: personnage.cpp personnage.h
	g++ -c personnage.cpp

game.o: game.cpp game.h
	g++ -c game.cpp

game.o: game.cpp game.h
	g++ -c game.cpp

clean:
	rm -f *.o labyrinth