/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#ifndef FILE_MUVELETEK_H_INCLUDED
#define FILE_MUVELETEK_H_INCLUDED
#include "Maze.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

bool mentes(Maze *m, char *nev);
bool mentesRanglista(char *nev, char *jatekos, int lepesszam);
bool beolvas(Maze *maze, char *labirintusNev);


#endif // FILE_MUVELETEK_H_INCLUDED
