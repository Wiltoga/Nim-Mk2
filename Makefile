# PathToMake -f PathToMakeFile GCC=PathToGCC workspace=PathToProjectFolder
# -f, GCC and workspace are optionnal

GCC := gcc
workspace := 

all: nim

nim: obj/main.o obj/consoleManagement.o obj/game.o obj/help.o obj/GamePlate.o obj/Position.o obj/utilities.o
	$(GCC) -o $(workspace)bin/nim $(workspace)obj/main.o $(workspace)obj/consoleManagement.o $(workspace)obj/game.o $(workspace)obj/help.o $(workspace)obj/GamePlate.o $(workspace)obj/Position.o $(workspace)obj/utilities.o

obj/main.o: $(workspace)src/main.c
	$(GCC) -o $(workspace)obj/main.o -c $(workspace)src/main.c

obj/consoleManagement.o: $(workspace)src/consoleManagement.c
	$(GCC) -o $(workspace)obj/consoleManagement.o -c $(workspace)src/consoleManagement.c

obj/game.o: $(workspace)src/game.c
	$(GCC) -o $(workspace)obj/game.o -c $(workspace)src/game.c

obj/help.o: $(workspace)src/help.c
	$(GCC) -o $(workspace)obj/help.o -c $(workspace)src/help.c

obj/GamePlate.o: $(workspace)src/GamePlate.c
	$(GCC) -o $(workspace)obj/GamePlate.o -c $(workspace)src/GamePlate.c

obj/Position.o: $(workspace)src/Position.c
	$(GCC) -o $(workspace)obj/Position.o -c $(workspace)src/Position.c

obj/utilities.o: $(workspace)src/utilities.c
	$(GCC) -o $(workspace)obj/utilities.o -c $(workspace)src/utilities.c
