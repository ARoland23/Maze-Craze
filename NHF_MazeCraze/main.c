/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.25

***************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "debugmalloc.h"
#include "Maze.h"
#include "Jatek.h"
#include "maze_algoritmusok.h"
#include "Menu.h"

int main()
{
    srand(time(NULL));
    char gomb;
    Maze maze;

    Pont kezdet1;
    Pont veg1;
    int lepesSzam1;

    do
    {
        system("cls");
        printMenu();
        gomb=getch();
        if(gomb=='q' || gomb=='Q')
            break;
        printf("%c\n",gomb);
        switch(gomb)
        {
            case '1':
                labirintusValaszto(&maze);
                break;
            case '2':
                fflush(stdin);
                char labirintusNev[100+1];
                char jatekosNev[100+1];

                if( beolvas(&maze, labirintusNev) )
                {
                   kezdet1.x=1; kezdet1.y=1;
                    veg1.y=maze.magassag-2; veg1.x=maze.szelesseg-2;
                    lepesSzam1=jatek(&maze,kezdet1,veg1);
                    system("cls");

                    mentesRanglista(labirintusNev,jatekosNev,lepesSzam1);
                    felszabadit(&maze);
                }
                break;
        }
    }while(isalnum(gomb));

    //felszabadit(&maze);
    system("cls");
    printf("A jatek veget ert. Most kilep!\n");
    return 0;
}
