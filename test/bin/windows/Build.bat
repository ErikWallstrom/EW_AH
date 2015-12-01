@echo off
gcc ../../src/Main.c ../../src/Array.c ../../src/Script.c ../../src/Libraries.c ../../src/Entity.c ../../src/Error.c ../../src/Components.c -Wall -Wextra -Wshadow -Wfatal-errors -g -o Program -std=c99 -lSDL2 -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lm -llua53
echo(
echo Build Done
echo(
pause