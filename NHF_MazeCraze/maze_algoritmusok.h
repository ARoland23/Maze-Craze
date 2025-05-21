/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#ifndef MAZE_ALGORITMUSOK_H_INCLUDED
#define MAZE_ALGORITMUSOK_H_INCLUDED
#include <stdbool.h>
#include <time.h>
#include "Maze.h"

void DFS(Maze *m, Pont kezdes, Pont goal);
void Kruskal(Maze *m, Pont kezdes, Pont goal);

#endif // MAZE_ALGORITMUSOK_H_INCLUDED
