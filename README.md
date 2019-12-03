# Nim-Mk2

Jeu de Nim en console, avec couleurs et interface utilisateur.

## installation et lancement

### Windows CMD

taper dans l'invite de commande :
```batch
compile
nim
```
ou
```batch
gcc src/main.c src/consoleManagement.c src/game.c src/help.c src/GamePlate.c src/Position.c src/utilities.c -o nim.exe
nim
```

### Windows Powershell

taper dans l'invite de commande powershell :
```powershell
./compile
./nim
```
ou
```powershell
gcc src/main.c src/consoleManagement.c src/game.c src/help.c src/GamePlate.c src/Position.c src/utilities.c -o nim.exe
./nim
```

### Linux Shell

taper dans le terminal (ne pas oublier de changer les permissions du fichier créé) :
```powershell
./compile.sh
./nim
```
ou
```powershell
gcc src/main.c src/consoleManagement.c src/game.c src/help.c src/GamePlate.c src/Position.c src/utilities.c -o nim
./nim
```

