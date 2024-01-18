#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "graf.h"

using namespace std;

HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );

void menu1();

Graf stworzGraf(int w);

int main()
{
    int wybor1;
    srand(time(NULL));

    do
    {
        cout << "W jaki sposob chcesz uzupelnic strukture grafu?\n" << endl;
        menu1();
        cin >> wybor1;
        system("cls");

         // Wczytanie danych: 1 - z pliku, 2 - wygenerowanie losowo

        switch(wybor1)
        {
            case 1:
                {
                    string nazwa;   // = "ftv44.atsp";
                    cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane: ";
                    cin >> nazwa;
                    int blad= 0;

                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                       string linia;
                       int wierzcholki;
                       int droga;

                       plik >> wierzcholki;

                       Graf graf(wierzcholki);
                       graf.completeWierzcholki();

                       // Uzupelnienie macierzy

                       for(int i=0; i<wierzcholki; i++)
                       {
                           for(int j=0; j<wierzcholki; j++)
                           {
                               plik >> droga;

                               graf.completeMacierz(droga, i, j);
                           }
                       }

                       plik.close();
                       graf.choice();
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;

                    break;
                }
            case 2:
                {
                    // LOSOWO
                    int wierzcholki, droga, droga2;
                    cout << "Podaj liczbe wierzcholkow\n";
                    cin >> wierzcholki;

                    // LOSOWO

                    Graf graf(wierzcholki);
                    graf.completeWierzcholki();

                    int index = 0;

                    // Uzupelnienie macierzy wartosciami -1

                    for(int i=0; i<wierzcholki; i++)
                    {
                        for(int j=0; j<wierzcholki; j++)
                        {
                            graf.completeMacierz(-1, i, j);
                        }
                    }

                    // Uzupe³nienie macierzy

                    for(int i=0; i<wierzcholki; i++)
                    {
                        for(int j=0; j<wierzcholki; j++)
                        {
                            if(graf.matrixValue(i, j) == -1)
                            {
                                // Uzupelnienie

                                if(i == j)
                                {
                                    droga = 0;
                                    droga2 = 0;
                                }
                                else
                                {
                                    droga = rand() % 1000 + 1;         // Losowanie odleglosci z zakresu <1, 1000>

                                    // Wylosowanie odleglosci przeciwnej

                                    // Losowanie znaku + lub -

                                    int znak = rand() % 2;

                                    // 0 -
                                    // 1 +

                                    // Losowanie roznicy

                                    int roznica = rand() % 51;

                                    if(znak == 0)
                                        droga2 = droga - roznica;
                                    else
                                        droga2 = droga + roznica;
                                }

                                graf.completeMacierz(droga, i, j);

                                // Uzupelnienie odbicia lustrzanego

                                graf.completeMacierz(droga2, j, i);
                            }
                        }
                    }

                    graf.choice();
                    cout << endl;

                    break;
                }
            case 3:
                {
                     // LOSOWO

                    int droga, droga2;

                    int wierzcholki=44;

                    // Seria losowych instancji - 100

                    for(int i=0; i<10; i++)
                    {
                        Graf graf(wierzcholki);

                        // Losowe uzupelnienie

                        graf.completeWierzcholki();

                        // Uzupelnienie macierzy wartosciami -1

                        for(int i=0; i<wierzcholki; i++)
                        {
                            for(int j=0; j<wierzcholki; j++)
                            {
                                graf.completeMacierz(-1, i, j);
                            }
                        }

                        // Uzupelnienie macierzy

                        for(int i=0; i<wierzcholki; i++)
                        {
                            for(int j=0; j<wierzcholki; j++)
                            {
                                if(graf.matrixValue(i, j) == -1)
                                {
                                    // Uzupelnienie

                                    if(i == j)
                                    {
                                        droga = 0;
                                        droga2 = 0;
                                    }
                                    else
                                    {
                                        droga = rand() % 1000 + 1;         // Losowanie odleglosci z zakresu <1, 1000>

                                        // Wylosowanie odleglosci przeciwnej

                                        // Losowanie znaku + lub -

                                        int znak = rand() % 2;

                                        // 0 -
                                        // 1 +

                                        // Losowanie roznicy

                                        int roznica = rand() % 51;

                                        if(znak == 0)
                                            droga2 = droga - roznica;
                                        else
                                            droga2 = droga + roznica;
                                    }

                                    graf.completeMacierz(droga, i, j);

                                    // Uzupelnienie odbicia lustrzanego

                                    graf.completeMacierz(droga2, j, i);
                                }
                            }
                        }

                        graf.pomiary(wierzcholki);
                    }

                    break;
                }
        }
    }while(wybor1!=0);

    return 0;
}

void menu1()
{
    cout << "1. Wczytanie danych z pliku\n";
    cout << "2. Losowe wygenerowanie grafu\n";
    cout << "3. POMIARY\n";
    cout << "0. EXIT" << endl;
}
