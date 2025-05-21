/***************************************************

Körömi Roland, G3A4MA, Labirintus játék, 2023.11.26

***************************************************/
#include <stdbool.h>
#include <time.h>
#include "Maze.h"

typedef struct CsoportElem{     //Kruskalhoz, csoportok
    int meret;
    Pont pont;
    int azon;
}CsoportElem;

static void csoportBeszur2(CsoportElem *tomb, int meret, CsoportElem mihez, CsoportElem mit){
    //atirja a csoportszamat a megfelelo elemeknek
    for(int i=0; i<meret; i++)
    {
        if(tomb[i].azon == mit.azon)
        {
            tomb[i].azon=mihez.azon;
        }
    }

    int ujmeret=mihez.meret+mit.meret;
    //atmeretezi az adott csoportba tartozo eelemek meretet
    for(int i=0; i<meret; i++)
    {
        if(tomb[i].azon == mihez.azon)
        {
            tomb[i].meret=ujmeret;
        }
    }
}
//vegig megy a csoportok tombjen es visszaadja a keresett pont indexet
static int csoportokKoztKeres(CsoportElem *tomb, int meret, Pont mit ){
    for(int i=0; i<meret; i++)
    {
        if(mit.x == tomb[i].pont.x && mit.y == tomb[i].pont.y)
            return i;
    }
    return -1;
}

static void kever(int *iranyok, int meret){
    if(iranyok==NULL)
        return;
    int r;
    for(int i=0; i<meret; i++)
    {
        r=rand()%meret;
        if(i != r)
        {
            int temp=iranyok[i];
            iranyok[i]=iranyok[r];
            iranyok[r]=temp;
        }
    }
}

//rekurzív DFS
void DFS(Maze *m, Pont kezdes, Pont goal){
        if(m->maze==NULL)
        return;


    int iranyok[4]={0, 1, 2, 3};  //0-balra, 1-fel, 2-jobbra, 3-le
    Pont mozgo;
    mozgo.x=kezdes.x; mozgo.y=kezdes.y;

    m->maze[kezdes.y][kezdes.x].ch=' ';  //kezdes nem lehet a falon
    m->maze[goal.y][goal.x+1].ch=' ';

    m->maze[goal.y][goal.x].visited=false; //kiveve a kijarat
    int irany;
        kever(iranyok,4);

        for(int i=0; i<4; i++) //megnezi a szomszedokat
        {
            irany=iranyok[i];

            switch( irany )
            {
                case 0:
                    if(mozgo.x-2 > 0)
                    {
                        if(m->maze[mozgo.y][mozgo.x-2].visited==false && m->maze[mozgo.y][mozgo.x-1].ch != ' ')
                        {
                            m->maze[mozgo.y][mozgo.x-2].visited = true;
                            m->maze[mozgo.y][mozgo.x-1].ch =' ';
                            mozgo.x = mozgo.x-2;
                            DFS(m,mozgo,goal);
                        }
                    }
                    break;

                case 1:
                    if(mozgo.y-2 > 0)
                    {
                        if(m->maze[mozgo.y-2][mozgo.x].visited==false && m->maze[mozgo.y-1][mozgo.x].ch != ' ')
                        {
                            m->maze[mozgo.y-2][mozgo.x].visited = true;
                            m->maze[mozgo.y-1][mozgo.x].ch =' ';
                            mozgo.y = mozgo.y-2;
                            DFS(m,mozgo,goal);
                        }
                    }
                    break;
                case 2:
                    if(mozgo.x+2 < m->szelesseg-1)
                    {
                        if(m->maze[mozgo.y][mozgo.x+2].visited==false && m->maze[mozgo.y][mozgo.x+1].ch != ' ')
                        {
                            m->maze[mozgo.y][mozgo.x+2].visited = true;
                            m->maze[mozgo.y][mozgo.x+1].ch =' ';
                            mozgo.x = mozgo.x+2;
                            DFS(m,mozgo,goal);
                        }
                    }
                    break;
                case 3:
                    if(mozgo.y+2 < m->magassag-1)
                    {
                        if(m->maze[mozgo.y+2][mozgo.x].visited==false && m->maze[mozgo.y+1][mozgo.x].ch !=' ')
                        {
                            m->maze[mozgo.y+2][mozgo.x].visited = true;
                            m->maze[mozgo.y+1][mozgo.x].ch  =' ';
                            mozgo.y = mozgo.y+2;
                            DFS(m,mozgo,goal);
                        }
                    }
                    break;
            }
        }
}

void Kruskal(Maze *m, Pont kezdes, Pont goal){
        if(m->maze==NULL)
        return;

    CsoportElem *csoportok =(CsoportElem*)malloc( ( (m->magassag/2) * (m->szelesseg/2) ) * sizeof(CsoportElem));  //FREEzni kell
    Pont *falak =(Pont*)malloc( ( (m->magassag-2) * (m->szelesseg-2) ) * sizeof(Pont));                           //FREEzni kell
    int csoportokSzama=0;
    int falakSzama =0;

 //uj csoportot hoz letre minden bejarhato cellahoz
 int id =0;
 for(int i=1; i<=m->magassag-2; i++)
 {
        for(int j=1; j<=m->szelesseg-2; j++)
        {
            if( m->maze[i][j].visited == false ) //nem fal
            {
                CsoportElem uj;
                uj.pont.y=i;
                uj.pont.x=j;
                uj.meret=1;
                uj.azon=id;
                id++;

                csoportok[csoportokSzama] = uj;
                csoportokSzama++;
            }
            else if(m->maze[i][j].ch !='+') // fal, de nem sarok
            {
                Pont ujPont;
                ujPont.y=i;
                ujPont.x=j;
                falak[falakSzama] = ujPont;
                falakSzama++;
            }
        }
 }
        //megkeveri a falak tombjet, hogy veletlenszeru sorrendben lehessen rajta vegig haladni
    for(int i=0; i<falakSzama; i++)
    {
        int r=rand()%falakSzama;
        if(i != r)
        {
            Pont temp=falak[i];
            falak[i]=falak[r];
            falak[r]=temp;
        }
    }

    for(int n=0; n<falakSzama ; n++)
    {

                Pont tempFel;
                Pont tempLe;
                Pont tempBalra;
                Pont tempJobbra;
                tempFel.y=falak[n].y-1; tempFel.x=falak[n].x;
                tempLe.y=falak[n].y+1; tempLe.x=falak[n].x;
                tempBalra.y=falak[n].y; tempBalra.x=falak[n].x-1;
                tempJobbra.y=falak[n].y; tempJobbra.x=falak[n].x+1;

                int indexFel=csoportokKoztKeres(csoportok, csoportokSzama, tempFel);
                int indexLe=csoportokKoztKeres(csoportok, csoportokSzama, tempLe);
                int indexBalra=csoportokKoztKeres(csoportok, csoportokSzama, tempBalra);
                int indexJobbra=csoportokKoztKeres(csoportok, csoportokSzama, tempJobbra);

                if(indexFel >=0 && indexLe>=0)
                {

                    if(csoportok[indexFel].azon != csoportok[indexLe].azon)//kulonbozo csoportokban vannak
                    {

                        m->maze[ falak[n].y ][ falak[n].x ].ch=' ';
                        if(csoportok[indexFel].meret > csoportok[indexLe].meret)
                        {
                            csoportBeszur2(csoportok,csoportokSzama,csoportok[indexFel],csoportok[indexLe]);
                        }
                        else
                        {
                            csoportBeszur2(csoportok,csoportokSzama,csoportok[indexLe],csoportok[indexFel]);
                        }

                    }

                }

                else if(indexBalra >=0 && indexJobbra>=0)
                {

                    if(csoportok[indexBalra].azon != csoportok[indexJobbra].azon)//kulonbozo csoportokban vannak
                    {
                        m->maze[ falak[n].y ][ falak[n].x ].ch=' ';
                        if(csoportok[indexBalra].meret > csoportok[indexJobbra].meret)
                        {
                            csoportBeszur2(csoportok,csoportokSzama,csoportok[indexBalra],csoportok[indexJobbra]);
                        }
                        else
                        {
                            csoportBeszur2(csoportok,csoportokSzama,csoportok[indexJobbra],csoportok[indexBalra]);
                        }

                    }
                }
    }

    free(falak);
    free(csoportok);
}
