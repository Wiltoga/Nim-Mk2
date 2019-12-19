# PathToMake -f PathToMakeFile GCC=PathToGCC workspace=PathToProjectFolder
# -f, GCC and workspace are optionnal

GCC := gcc
workspace := 
args := -W -Wall -ansi -pedantic

all: nim.exe

nim.exe: main.o consoleManagement.o game.o help.o GamePlate.o Position.o utilities.o
	$(GCC) -o $(workspace)bin/nim $(workspace)obj/main.o $(workspace)obj/consoleManagement.o $(workspace)obj/game.o $(workspace)obj/help.o $(workspace)obj/GamePlate.o $(workspace)obj/Position.o $(workspace)obj/utilities.o

main.o: $(workspace)src/main.c
	$(GCC) -o $(workspace)obj/main.o -c $(workspace)src/main.c

consoleManagement.o: $(workspace)src/consoleManagement.c
	$(GCC) -o $(workspace)obj/consoleManagement.o -c $(workspace)src/consoleManagement.c

game.o: $(workspace)src/game.c
	$(GCC) -o $(workspace)obj/game.o -c $(workspace)src/game.c

help.o: $(workspace)src/help.c
	$(GCC) -o $(workspace)obj/help.o -c $(workspace)src/help.c

GamePlate.o: $(workspace)src/GamePlate.c
	$(GCC) -o $(workspace)obj/GamePlate.o -c $(workspace)src/GamePlate.c

Position.o: $(workspace)src/Position.c
	$(GCC) -o $(workspace)obj/Position.o -c $(workspace)src/Position.c

utilities.o: $(workspace)src/utilities.c
	$(GCC) -o $(workspace)obj/utilities.o -c $(workspace)src/utilities.c

clean:
	rm -r -Force $(workspace)obj/*.o

mrproper: clean
	rm -r -Force $(workspace)bin/nim.exe
