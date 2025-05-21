/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#include "Maze.h"
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

void kirajzol(Maze *m);
bool joLepes(Cell cell);
int jatek(Maze *m, Pont kezdet, Pont veg);

#endif // JATEK_H_INCLUDED
