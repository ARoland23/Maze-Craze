/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#include "Maze.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool mentes(Maze *m, char *nev){
    // nev bekero muveletek
    printf(" El szeretned menteni?\n"
           "(i)/(n)\n"
           );
    char c;
    fflush(stdin);
    while(true)
    {
        c=getch();
        if(c == 'n')
        {
            return false;
        }
        else if (c == 'i')
            break;
    }
    printf("Mi legyen a labirintus neve?(100 karakter hosszu!)\n");
    scanf("%[^\n]",nev);

    //file muveletek
    FILE *fp = fopen(nev, "w");

    if( nev == NULL)
        return false;
    if( fp == NULL )
        return false;
    if( m == NULL )
    {
        return false;
    }

        fprintf(fp,"%s\n",nev);
        fprintf(fp,"%d\n",m->magassag);
        fprintf(fp,"%d\n",m->szelesseg);
        for(int y=0; y< m->magassag; y++)
        {
            for(int x=0; x< m->szelesseg; x++)
            {
                fprintf(fp,"%c",m->maze[y][x].ch);
            }
        }
    fclose(fp);
    return true;
}

bool mentesRanglista(char *nev, char *jatekos, int lepesszam){
    //nev bekero muveletek
    fflush(stdin);
    printf("Mi a jatekos neved?(100 karakter hosszu!)\n");
    scanf("%[^\n]",jatekos);
    if( nev == NULL || jatekos == NULL)
        return false;

    char rangListaNev[100 +1 +4];
    sprintf(rangListaNev,"%sRANG",nev);

    //file muveletek
    FILE *fp = fopen(rangListaNev, "a");

    if( fp == NULL )
    {
        return false;
    }

        fprintf(fp,"%s\t%d\n",jatekos,lepesszam);

    fclose(fp);
    return true;
}

bool beolvas(Maze *maze, char *labirintusNev){
    Maze *m=maze;

    int magassag;
    int szelesseg;

    fflush(stdin);
    printf("Melyik labirintust szeretned beolvasni?(100 karakter hosszu!)\n");
    scanf("%[^\n]",labirintusNev);

    FILE *fp = fopen(labirintusNev,"r");
    if(fp == NULL)
        return false;
    if(fscanf(fp,"%s\n",labirintusNev) == 0)
        return false;
    fscanf(fp,"%d\n",&magassag);
    fscanf(fp,"%d\n",&szelesseg);
    ujlabirintus(m, magassag, szelesseg);
    for(int i=0; i<magassag; i++)
        for(int j=0; j<szelesseg; j++)
        m->maze[i][j].ch=fgetc(fp);
    fclose(fp);
    return true;
}
