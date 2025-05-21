/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct Cell{
    char ch;
    bool visited;       //a labirintus cellai
    bool ajto;          //falak
}Cell;

typedef struct Maze{
    int szelesseg;
    int magassag;       //labirintus
    Cell **maze;
}Maze;

typedef struct Pont{
    int x;
    int y;              //a labirintus egy pontjanak a kkordinataja
}Pont;

void felszabadit(Maze *m);
bool labirintusIO(int *m, int *sz);
void ujlabirintus(Maze *ujMaze, int magassag, int szelesseg);
void teljesFeltolt(Maze *m);

#endif // MAZE_H_INCLUDED
