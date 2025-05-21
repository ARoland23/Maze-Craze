/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#include "Maze.h"
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

void kirajzol(Maze *m){
    for(int i=0; i<m->magassag; i++)
    {
        for(int j=0; j<m->szelesseg; j++)  //csak kirajzolja a betoltott labirintustban levo karaktereket
            putchar(m->maze[i][j].ch);
        putchar('\n');
    }
}

bool joLepes(Cell cell){
    return cell.ch!='|' && cell.ch!='-' && cell.ch!='+';
}

int jatek(Maze *m, Pont kezdet, Pont veg){
    kezdet.x=1; kezdet.y=1;  //kezdet pontja
    veg.y=m->magassag-2; veg.x=m->szelesseg-2; //A cel pontja, jobb also szoba fala
    Pont karakterPont; karakterPont.x=kezdet.x; karakterPont.y=kezdet.y; //jatekos helyenek a koordinataja, a kezdesnel kezd
    m->maze[veg.y][veg.x].ch=' ';
    m->maze[kezdet.y][kezdet.x].ch=' ';
    char const figura ='A';
    m->maze[karakterPont.y][karakterPont.x].ch=figura;
    bool jatekVege=false;
    int lepessSzam=0;

    kirajzol(m);
    while(!jatekVege)
    {
        char iranyitas=getch();
        if(iranyitas == 'q' || iranyitas=='Q')
            return -1;
        switch(iranyitas)
        {
            case 'w':
                if(joLepes(m->maze[karakterPont.y-1][karakterPont.x]) && karakterPont.y-1 > 0)
                {
                    m->maze[karakterPont.y][karakterPont.x].ch=' ';
                    karakterPont.y-=1;
                    m->maze[karakterPont.y][karakterPont.x].ch=figura;
                    system("cls");
                    kirajzol(m);
                    printf("\n %d",++lepessSzam);
                }
                break;
            case 'a':
                if(joLepes(m->maze[karakterPont.y][karakterPont.x-1]) && karakterPont.x-1 > 0)
                {
                    m->maze[karakterPont.y][karakterPont.x].ch=' ';
                    karakterPont.x-=1;
                    m->maze[karakterPont.y][karakterPont.x].ch=figura;
                    system("cls");
                    kirajzol(m);
                    printf("\n %d",++lepessSzam);
                }
                break;
            case 's':
                if(joLepes(m->maze[karakterPont.y+1][karakterPont.x]) && karakterPont.y+1 < m->magassag-1)
                {
                    m->maze[karakterPont.y][karakterPont.x].ch=' ';
                    karakterPont.y+=1;
                    m->maze[karakterPont.y][karakterPont.x].ch=figura;
                    system("cls");
                    kirajzol(m);
                    printf("\n %d",++lepessSzam);
                }
                break;
            case 'd':
                if(joLepes(m->maze[karakterPont.y][karakterPont.x+1])&& karakterPont.x+1 < m->szelesseg-1)
                {
                    m->maze[karakterPont.y][karakterPont.x].ch=' ';
                    karakterPont.x+=1;
                    m->maze[karakterPont.y][karakterPont.x].ch=figura;
                    system("cls");
                    kirajzol(m);
                    printf("\n %d",++lepessSzam);
                }
                break;
        }
        if(karakterPont.x==veg.x && karakterPont.y==veg.y)
        {
            jatekVege=true;
            m->maze[karakterPont.y][karakterPont.x].ch=' ';
        }
    }
    return lepessSzam;
}
