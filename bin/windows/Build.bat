@echo off
gcc ../../src/Main.c ../../src/Array.c ../../src/Script.c -Wall -Wextra -mwindows -o Program -std=c99 -lSDL2 -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lm -llua53
echo(
echo Build Done
echo(
pause