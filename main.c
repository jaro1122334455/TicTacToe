#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>




const int rozmiar_planszy = 3;
const char puste_pole = ' ';

void wyswietl_logo();

void rysuj_plansze (char tablica[rozmiar_planszy][rozmiar_planszy]);
void ruch_gracz (char tablica[rozmiar_planszy][rozmiar_planszy]);
void ruch_komputera (char tablica[rozmiar_planszy][rozmiar_planszy]);

bool czy_gracz_wygral(const char tablica[rozmiar_planszy][rozmiar_planszy], char gracz);
int sprawdz_wynik(const char tablica[rozmiar_planszy][rozmiar_planszy]);
void wyswietl_wynik(char wynik);

int min_max(char tablica[rozmiar_planszy][rozmiar_planszy], int glebokosc, bool maksymalizuj);

void wykonaj_najlepszy_ruch(char tablica[rozmiar_planszy][rozmiar_planszy]);

bool czy_plansza_pelna(const char tablica[rozmiar_planszy][rozmiar_planszy]);

int main() {

    char tablica_2 [3][3] = {
        {' ', ' ', ' '}, 
        {' ', ' ', ' '}, 
        {' ', ' ', ' '}
    };

    int liczba_ruchów = 0;

    char wynik = 'R';


    while(1){
        


        wyswietl_logo();

        wykonaj_najlepszy_ruch(tablica_2);

        if(czy_gracz_wygral(tablica_2, 'O'))
        {
            wynik = 'O';
            break;
            
        }
        
        if(czy_plansza_pelna(tablica_2))
        {
            break;
        }



        rysuj_plansze(tablica_2);

        ruch_gracz(tablica_2);

        if(czy_gracz_wygral(tablica_2, 'X'))
        {
            wynik = 'X';
            break;
        }



        system("clear");
    }

    rysuj_plansze(tablica_2);
    wyswietl_wynik(wynik);


    printf("\nKoniec gry");
        return 0;

}

void wyswietl_logo()
{
        printf(
"                    _____ _     _____         _____                   \n"
"                   |_   _(_) __|_   _|_ _  __|_   _|__   ___          \n"
"                     | | | |/ __|| |/ _` |/ __|| |/ _ \\ / _ \\       \n"
"                     | | | | (__ | | (_| | (__ | | (_) |  __/         \n"
"                     |_| |_|\\___||_|\\__,_|\\___||_|\\___/ \\___|    \n\n\n\n"  );

}

void rysuj_plansze (char tablica[rozmiar_planszy][rozmiar_planszy])
{
    for(int i=0; i<rozmiar_planszy; i++)
    {
        printf("                                       %c | %c | %c \n", tablica[i][0], tablica[i][1], tablica[i][2]);
        if (i != 2){
            printf("                                      ---|---|---\n");
        }
    }
}

void ruch_gracz (char tablica[rozmiar_planszy][rozmiar_planszy]){

    int i, j;
    printf("\n\nPodaj wspolrzedne:");
    scanf("%d %d", &i, &j);

    if ( i<=0 || j <=0 || i>rozmiar_planszy || j>rozmiar_planszy){                  // Sprawdzenie czy nie wykroczono poza plansze
        printf("Zle dane!\n");
        ruch_gracz(tablica);
    }

    else if(tablica[i-1][j-1] == 'X'){                                              // Sprawdzenie czy nie powtórzono współrzędnych
        printf("Wspolrzedne sie powtarzaja\n");
        ruch_gracz(tablica);
    }
    else if(tablica[i - 1][j - 1] == 'O')
    {
        printf("Wspolrzedne należą do przeciwnika\n");
        ruch_gracz(tablica);
    }
    else
    {
        tablica[i-1][j-1] = 'X';
    }
    
}

bool czy_plansza_pelna(const char tablica[rozmiar_planszy][rozmiar_planszy])
{
    for(int i = 0; i < rozmiar_planszy; ++i)
    {
        for(int j = 0; j < rozmiar_planszy; ++j)
        {

            if(tablica[i][j] == puste_pole)
            {

                return false;
            }


        }
    }

    return true;

}

bool czy_gracz_wygral(const char tablica[rozmiar_planszy][rozmiar_planszy], char gracz)
{

    // Sprawdzenie wierszy
    for(int i = 0; i < rozmiar_planszy; ++i)
    {
        if(tablica[i][0] == gracz && tablica[i][1] == gracz && tablica[i][2] == gracz)
        {
            return true;
        }
    }

    //sprawdzenie kolumn
    for(int i = 0; i < rozmiar_planszy; ++i)
    {
        if(tablica[0][i] == gracz && tablica[1][i] == gracz && tablica[2][i] == gracz)
        {
            return true;
        }
    }


    //sprawdzenie przekątnych
    if(tablica[0][0] == gracz && tablica[1][1] == gracz && tablica[2][2] == gracz)
    {
        return true;
    }

    if(tablica[0][2] == gracz && tablica[1][1] == gracz && tablica[2][0] == gracz)
    {
        return true;
    }

    return false;



}

int sprawdz_wynik(const char tablica[rozmiar_planszy][rozmiar_planszy])
{
    //sprawdenie czy wygrał gracz X
    if(czy_gracz_wygral(tablica, 'X'))
    {
        return 10;
    }
    //sprawdznie czy wygrał gracz O
    else if(czy_gracz_wygral(tablica, 'O'))
    {
        return -10;
    }
    else
    {
        // Sprawdzenie czy gra dalej trwa plansza nie pełna
        if(!czy_plansza_pelna(tablica))
        {
            return 0;
        }

    }

    //plansza pełna - remis
    return 0;
}

void wyswietl_wynik(char wynik)
{
    if(wynik == 'X')
    {
        printf("\nWygrał X");
    }

    else if(wynik == 'O')
    {
        printf("\nWygrał O");
    }

    else if(wynik == 'R')
    {
        printf("\nRemis");
    }

}

int min_max(char tablica[rozmiar_planszy][rozmiar_planszy], int glebokosc, bool maksymalizuj)
{
    int obecny_wynik = sprawdz_wynik(tablica);

    //Bazowy przypadek - jeśli wynik != 0 czyli gra się zakończyła (możliwe wyniki 10, -10, 1)
    if(obecny_wynik != 0)
    {
        return obecny_wynik;
    }

    if(maksymalizuj)
    {
        int najlepszy_wynik = INT_MIN;

        for(int i = 0; i < rozmiar_planszy; ++i)
        {
            for(int j = 0; j < rozmiar_planszy; ++j)
            {
                if(tablica[i][j] == puste_pole)
                {
                    tablica[i][j] = 'X';
                    obecny_wynik = min_max(tablica, glebokosc + 1, false);
                    tablica[i][j] = puste_pole;

                    if(obecny_wynik > najlepszy_wynik)
                    {
                        najlepszy_wynik = obecny_wynik;
                    }
                }
            }
        }

        return najlepszy_wynik;
    }

    else
    {
        int najlepszy_wynik = INT_MAX;

        for(int i = 0; i < rozmiar_planszy; ++i)
        {
            for(int j = 0; j < rozmiar_planszy; ++j)
            {
                if(tablica[i][j] == puste_pole)
                {
                    tablica[i][j] = 'O';
                    obecny_wynik = (tablica, glebokosc + 1, true);
                    tablica[i][j] = puste_pole;

                    if(obecny_wynik < najlepszy_wynik)
                    {
                        najlepszy_wynik = obecny_wynik;
                    }
                }
            }
        }

        return najlepszy_wynik;
    }

    // return 10;
}

void wykonaj_najlepszy_ruch(char tablica[rozmiar_planszy][rozmiar_planszy])
{
    int najlepszy_wynik = INT_MAX;
    int ruch_x = -1;
    int ruch_y = -1;

    //Algorytm przechodzi przez całą planszę i na każdym polu uruchamia algorytm minmax
    for(int i = 0; i < rozmiar_planszy; ++i)
    {
        for(int j = 0; j < rozmiar_planszy; ++j)
        {
            if(tablica[i][j] == puste_pole)
            {
                tablica[i][j] = 'O';
                int obecny_ruch = min_max(tablica, 0, true);   //false - ponieważ O jest graczem minimalizującym
                tablica[i][j] = puste_pole;


                if(obecny_ruch < najlepszy_wynik)
                {
                    najlepszy_wynik = obecny_ruch;

                    ruch_x = i;
                    ruch_y = j;
                }

            }
        }
    }


    tablica[ruch_x][ruch_y] = 'O';

}

