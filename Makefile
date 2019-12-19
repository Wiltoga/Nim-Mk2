all: nim.exe

nim.exe: main.o consoleManagement.o game.o help.o GamePlate.o Position.o utilities.o
	gcc -o nim main.o consoleManagement.o game.o help.o GamePlate.o Position.o utilities.o

main.o: src/main.c
	gcc -o main.o -c src/main.c

consoleManagement.o: src/consoleManagement.c
	gcc -o consoleManagement.o -c src/consoleManagement.c

game.o: src/game.c
	gcc -o game.o -c src/game.c

help.o: src/help.c
	gcc -o help.o -c src/help.c

GamePlate.o: src/GamePlate.c
	gcc -o GamePlate.o -c src/GamePlate.c

Position.o: src/Position.c
	gcc -o Position.o -c src/Position.c

utilities.o: src/utilities.c
	gcc -o utilities.o -c src/utilities.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf nim.exe
