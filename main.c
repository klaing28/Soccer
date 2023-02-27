#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Pole
{
    int uzyte;

};

int dlugosc=21;
int szerokosc =21;
struct Pole map[21][21];

struct Punkt
{
    int x;
    int y;
}gracz;

struct Ruchy
{
    int rzad,kol;
    struct Ruchy* nxt;
};


int Max(int a, int b)
{
    if(a > b) return a;
    else return b;
}

int Min(int a, int b)
{
    if(a < b) return a;
    else return b;
}


void StanMapy()
{
    for(int y=0; y<dlugosc; y++)
    {
        for(int x=0; x<szerokosc; x++)
        {
            if(x==0 || x== 20)
            {
                map[x][y].uzyte=1;
            }
            else if (y==0 && x<7 || y==0 && x>13 || y==20 && x<7 || y==20 && x>13)
            {
                map[x][y].uzyte = 1;
            }
        }
    }
}

void wyswietl()
{
    for(int y=0; y<dlugosc; y++)
    {
        for(int x=0; x<szerokosc; x++)
        {
            if(x == gracz.x && y==gracz.y)
            {
                printf(" @ ");
            }
            else if(map[x][y].uzyte==0)
            {
                if(y%2 == 1 && x%2 ==1)
                {
                    printf("   ");
                }
                else if (y%2 == 1 && x%2 !=1)
                {
                    printf("   ");
                }
                else if (y%2 != 1 && x%2 ==1)
                {
                    printf("   ");
                }
                else if(y%2 != 1 && x%2 != 1)
                {
                    printf(" * ");
                }
            }
            else if(map[x][y].uzyte==1)
            {
                if(y%2 == 1 && x%2 ==1)
                {
                    printf(" ` ");
                }
                else if (y%2 == 1 && x%2 !=1)
                {
                    printf(" | ");
                }
                else if (y%2 != 1 && x%2 ==1)
                {
                    printf(" - ");
                }
                else if(y%2 != 1 && x%2 != 1)
                {
                    printf(" * ");
                }
            }
            else if(map[x][y].uzyte==2)
            {
                if(y%2 == 1 && x%2 ==1)
                {
                    printf(" / ");
                }
            }
            else if(map[x][y].uzyte==3)
            {
                if(y%2 == 1 && x%2 ==1)
                {
                    printf(" x ");
                }
            }

        }
        printf("\n");
    }
}

int ewaluacja()
{

    if(gracz.y ==0)
    {
        if(gracz.x ==8 || gracz.x==10 || gracz.x ==12)
        {
            return -5000;
        }
    }
    else if(gracz.y ==20)
    {
        if(gracz.x ==8 || gracz.x==10 || gracz.x ==12)
        {
            return 5000;
        }
    }
    return 0;
}

void zniszczliste(struct Ruchy* h)
{
    if(h==0)
    {return;}
    zniszczliste(h->nxt);
    free(h);
}

struct Ruchy* dodajruch(struct Ruchy* h, int r, int k)
{

    struct Ruchy* ptr = (struct Ruchy*) calloc(1, sizeof(struct Ruchy));
    ptr->rzad=r;
    ptr->kol=k;
    ptr->nxt=NULL;

    if(h->rzad==0&&h->kol==0)
    {
        *h=*ptr;
        return h;
    }

    while(h->nxt )
    {
        h=h->nxt;
    }
    h->nxt=ptr;
    return h;
}

struct Ruchy* możliweRuchy(struct Ruchy* h)
{
    for(int y=0;y<dlugosc; y++)
    {
        for(int x=0;x<szerokosc ; x++)
        {
            if(abs(gracz.x - x) <= 1 && abs(gracz.y -y)<=1 )
            {
                if(map[x][y].uzyte ==0  )
                {
                    if(y%2 == 1 && x%2 ==1)
                    {
                        dodajruch(h, x,y);

                    }
                    else if (y%2 == 1 && x%2 !=1)
                    {
                        dodajruch(h, x,y);

                    }
                    else if (y%2 != 1 && x%2 ==1)
                    {
                        dodajruch(h, x,y);

                    }
                }
                else if(map[x][y].uzyte ==1 || map[x][y].uzyte==2)
                {
                    if(y%2 == 1 && x%2 ==1)
                    {
                        if ((map[x][y].uzyte == 1 && x==gracz.x +1 && y==gracz.y -1) || (map[x][y].uzyte == 1 && x==gracz.x -1 && y==gracz.y +1))
                        {
                            dodajruch(h, x,y);

                        }
                        else if ((map[x][y].uzyte == 2 && x==gracz.x -1 && y==gracz.y -1) || (map[x][y].uzyte == 2 && x==gracz.x +1 && y==gracz.y +1) )
                        {
                            dodajruch(h, x,y);

                        }


                    }
                }
            }

        }
    }

}



void Ruszaniegracz()
{
    char opcja;
    char whate;
    printf("Podaj ruch\n");
    scanf("%c", &opcja);
    scanf("%c", &whate);

    if(opcja=='w')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x][gracz.y-1].uzyte=1;
        gracz.y = gracz.y -2;
    }
    else if (opcja=='q')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x-1][gracz.y-1].uzyte=map[gracz.x-1][gracz.y-1].uzyte + 1;
        gracz.x = gracz.x -2;
        gracz.y = gracz.y -2;
    }
    else if (opcja == 'e')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x+1][gracz.y-1].uzyte=map[gracz.x+1][gracz.y-1].uzyte+2;
        gracz.x = gracz.x+2;
        gracz.y = gracz.y-2;
    }
    else if (opcja=='a')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x-1][gracz.y].uzyte=1;
        gracz.x = gracz.x -2;
    }
    else if(opcja=='d')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x+1][gracz.y].uzyte=1;
        gracz.x = gracz.x +2;
    }
    else if(opcja=='z')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x-1][gracz.y+1].uzyte=map[gracz.x-1][gracz.y+1].uzyte +2;
        gracz.x = gracz.x -2;
        gracz.y = gracz.y +2;
    }
    else if(opcja=='x')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x][gracz.y+1].uzyte=1;
        gracz.y = gracz.y +2;
    }
    else if(opcja == 'c')
    {
        map[gracz.x][gracz.y].uzyte=1;
        map[gracz.x+1][gracz.y+1].uzyte=map[gracz.x+1][gracz.y+1].uzyte+1;
        gracz.x=gracz.x+2;
        gracz.y=gracz.y+2;
    }


}

int minmax(int depth, int isMax)
{
    int kux = gracz.x;
    int kuy = gracz.y;
    depth =depth+1;

    if(isMax==1)
    {

        isMax=0;


    }
    else if(isMax ==0)
    {

        isMax=1;

    }
    int score = 0;
    score = ewaluacja();
    int punkty=0;
    if(score == 5000 || score == -5000)
    {
        return score;
    }

    if(depth == 6 || depth>6) // tu zmieniamy poziom trudności //
    {

        kuy=kuy*kuy;
        kux=kux-10;
        kux=kux*kux;
        kux=kux*(-1);
        punkty = kuy + kux;
        return punkty;
    }
    else if(isMax)
    {
        int best = -10000;
        int startx=gracz.x;
        int starty=gracz.y;

        struct Ruchy* h=(struct Ruchy*) calloc(1, sizeof(struct Ruchy));
        możliweRuchy(h);
        while(h)
        {
            gracz.x=gracz.x+2*(h->rzad - gracz.x);
            gracz.y=gracz.y+2*(h->kol - gracz.y);

            best = Max(best,minmax(depth,isMax));


            gracz.x=startx;
            gracz.y=starty;

            h=h->nxt;
        }
        zniszczliste(h);
        return best;
    }
    else
    {
        int best = 10000;
        int startx = gracz.x;
        int starty = gracz.y;

        struct Ruchy* h=(struct Ruchy*) calloc(1, sizeof(struct Ruchy));
        możliweRuchy(h);

        while(h)
        {
            gracz.x=gracz.x+2*(h->rzad - gracz.x);
            gracz.y=gracz.y+2*(h->kol - gracz.y);



            best = Min(best,minmax(depth, isMax));



            gracz.x=startx;
            gracz.y=starty;

            h=h->nxt;
        }
        zniszczliste(h);
        return best;
    }

}

void najlepszy()
{
    int bestVal= -10000;
    int startx=gracz.x;
    int starty=gracz.y;
    int nX, nY;

    struct Ruchy* h=(struct Ruchy*) calloc(1, sizeof(struct Ruchy));
    możliweRuchy(h);

    while(h)
    {
        gracz.x=gracz.x+2*(h->rzad - gracz.x);
        gracz.y=gracz.y+2*(h->kol - gracz.y);

        int xx = gracz.x;
        int yy = gracz.y;



        int moveVal = minmax( 0 , 0);

        if(moveVal>bestVal)
        {
            bestVal=moveVal;
            nX=xx;
            nY=yy;
        }
        gracz.x=startx;
        gracz.y=starty;


        h=h->nxt;
    }
    zniszczliste(h);



    printf("Obecna pozycja : %d %d \n \n",
           gracz.x, gracz.y);
    printf("Ruch silnika :  %d %d \n \n \n",
           nX, nY);


}




int main()
{
    printf("Twoim celem jest dostanie sie do gornej bramki. \n Poruszaj sie za pomoca q,w,e,a,d,z,x,c. Pamietaj aby wykonywac ruchy komputera. Powodzenia. \n"
           "Legenda Planszy: \n"
           "0 2 4 \n"
           "2 x x \n"
           "4 x x \n "
           "etc... \n");


    gracz.x=10;
    gracz.y=10;
    int gra=0;
    int tura;
    tura =1;

    while(gra<4)
    {
        struct Ruchy* h=(struct Ruchy*) calloc(1, sizeof(struct Ruchy));

        if(tura==1)
        {


            StanMapy();
            wyswietl();
            Ruszaniegracz();
            if(map[gracz.x][gracz.y].uzyte==0)
            {
                tura =0;
            }

            if(gracz.y ==0)
            {
                if(gracz.x ==8 || gracz.x==10 || gracz.x ==12)
                {
                    gra=10;
                    printf("Koniec gry, wow gratulacje, wygrales");
                }
            }
        }
        else if(tura == 0)
        {
            StanMapy();
            wyswietl();

            if(gracz.y ==20 || gracz.y ==18)
            {
                if(gracz.x ==6 || gracz.x ==8 || gracz.x==10 || gracz.x ==12 || gracz.x==14)
                {
                    gra=10;
                    printf("Koniec gry, nastepnym razem ci sie uda");
                }
            }
            else
            {

                najlepszy();
                Ruszaniegracz();
                if(map[gracz.x][gracz.y].uzyte==0)
                {
                    tura =1;
                }
            }


        }



    }


    return 0;
}

