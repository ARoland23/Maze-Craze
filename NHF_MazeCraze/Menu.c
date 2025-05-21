/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#include <windows.h>
#include "Maze.h"
#include "maze_algoritmusok.h"
#include "Jatek.h"
#include "file_muveletek.h"
#include "Menu.h"

void printMenu(){
    printf(
           "(1.) Uj labirintus\n"
           "(2.) Mentett labirintus betoltese\n"
           "(Q) Kilepes\n"
           );
}

void printValaszto(){
    system("cls");
    printf("Milyen algoritmussal generalja a labirintusodat?\n");
    printf(
        "(1.) Depth-First Search\n"
        "(2.) Kruskal-algoritmus\n"
        "(Q) vissza\n"
           );
}

void labirintusValaszto(Maze *maze){
    Maze *m=maze;
    int szelesseg, magassag;

    Pont kezdet;
    Pont veg;
    int lepesSzam;

    char labirintusNev[100+1];
    char jatekosNev[100+1];

    char gomb;
    do
    {
        printValaszto();
        gomb=getch();
        if(gomb=='q' || gomb=='Q')
            break;

        switch(gomb)
        {
            case '1':
                if( labirintusIO(&magassag,&szelesseg) )
                {
                  ujlabirintus(m, magassag, szelesseg);
                    kezdet.x=1; kezdet.y=1;
                    veg.y=m->magassag-2; veg.x=m->szelesseg-2;
                    teljesFeltolt(m);
                    DFS(m, kezdet, veg);
                    lepesSzam=jatek(m,kezdet,veg);
                    system("cls");

                    if( mentes(m, labirintusNev) )
                        mentesRanglista(labirintusNev,jatekosNev,lepesSzam);
                    felszabadit(m);
                }
                break;
            case '2':
                if( labirintusIO(&magassag,&szelesseg) )
                {
                  ujlabirintus(m, magassag, szelesseg);
                    kezdet.x=1; kezdet.y=1;
                    veg.y=m->magassag-2; veg.x=m->szelesseg-2;
                    teljesFeltolt(m);
                    Kruskal(m, kezdet, veg);
                    lepesSzam=jatek(m,kezdet,veg);
                    system("cls");

                    if( mentes(m, labirintusNev) )
                        mentesRanglista(labirintusNev,jatekosNev,lepesSzam);
                    felszabadit(m);
                }
                break;
        }

    }while(isalnum(gomb));
}

