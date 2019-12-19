all: nim.exe

nim.exe: main.o consoleManagement.o game.o help.o GamePlate.o Position.o utilities.o
	gcc -o bin/nim obj/main.o obj/consoleManagement.o obj/game.o obj/help.o obj/GamePlate.o obj/Position.o obj/utilities.o

main.o: src/main.c
	gcc -o obj/main.o -c src/main.c

consoleManagement.o: src/consoleManagement.c
	gcc -o obj/consoleManagement.o -c src/consoleManagement.c

game.o: src/game.c
	gcc -o obj/game.o -c src/game.c

help.o: src/help.c
	gcc -o obj/help.o -c src/help.c

GamePlate.o: src/GamePlate.c
	gcc -o obj/GamePlate.o -c src/GamePlate.c

Position.o: src/Position.c
	gcc -o obj/Position.o -c src/Position.c

utilities.o: src/utilities.c
	gcc -o obj/utilities.o -c src/utilities.c

clean:
	rm -r -Force obj/*.o

mrproper: clean
	rm -r -Force bin/nim.exe
