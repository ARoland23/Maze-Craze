/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#include "Maze.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MIN 11
#define MAX 101


void felszabadit(Maze *m){
    if(m->maze[0]==NULL)
        return;
    free(m->maze[0]);
    free(m->maze);
}

bool labirintusIO(int *m, int *sz){ //pointerek!
    if(m == NULL || sz == NULL)
        return false;

    printf("Mekkora legyen a labirintus?\n");
    printf("szelesseg: ");
    if( scanf("%d",sz) == 1)
    {
        if(*sz%2 == 0)
            *sz+=1;             //paratlan kell, hogy legyen, a falak miatt
    }
    else
        return false;

    printf("magassag: ");
    if( scanf("%d",m) == 1)
    {
        if(*m%2 == 0)
            *m+=1;              //paratlan kell, hogy legyen, a falak miatt
    }
    else
        return false;

    if( *sz < MIN )
        *sz= MIN;
    if( *sz > MAX )
        *sz=MAX;

    if( *m < MIN )
        *m=MIN;
    if( *m > MAX )
        *m=MAX;

    return true;
}

void ujlabirintus(Maze *ujMaze, int magassag, int szelesseg){
        //ha mar van egy labirintusunk, /kesobb a jatek vege megoldja/
    //if(ujMaze->maze[0]!=NULL)
    //   felszabadit(ujMaze);
    ujMaze->magassag=magassag;
    ujMaze->szelesseg=szelesseg;

    ujMaze->maze=(Cell**)malloc(magassag * sizeof(Cell*));
    ujMaze->maze[0]=(Cell*)malloc(szelesseg * magassag * sizeof(Cell));

    for(int i=1; i<magassag; i++)
        ujMaze->maze[i]=ujMaze->maze[0]+ i*szelesseg;
}

void teljesFeltolt(Maze *m){
    if(m->maze==NULL)
        return;

    for(int i=0; i<m->magassag; i++)
        for(int j=0; j<m->szelesseg; j++)
        {
              if(i==0 || i==m->magassag-1)              //teteje, alja
              {
                    m->maze[i][j].ch='-';
                    m->maze[i][j].visited=true;
                    m->maze[i][j].ajto=true;
              }
              else if(j==0 || j==m->szelesseg-1)        //ket szele
              {
                  m->maze[i][j].ch='|';
                  m->maze[i][j].visited=true;
                  m->maze[i][j].ajto=true;
              }
              else if(i%2==0 && j%2==0)                 //sarkok
              {
                  m->maze[i][j].ch='+';
                  m->maze[i][j].visited=true;
                  m->maze[i][j].ajto=true;
              }
              else if(i%2==0)                           //vizszintes ajtok
              {
                    m->maze[i][j].ch='-';
                    m->maze[i][j].visited=true;
                    m->maze[i][j].ajto=true;
              }
              else if(j%2==0)                           //fuggoleges ajtok
              {
                  m->maze[i][j].ch='|';
                  m->maze[i][j].visited=true;
                  m->maze[i][j].ajto=true;
              }
              else                                  //minden mas
              {
                m->maze[i][j].visited=false;
                m->maze[i][j].ajto=false;
                m->maze[i][j].ch=' ';
              }
        }
}
