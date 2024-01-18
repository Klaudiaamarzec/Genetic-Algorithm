#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include "macierz.h"
#include <ctime>
#include <cstdlib>
using namespace std;

class Graf
{

public:
    int rozmiarw = 0;
    int *wierzcholki;                   // wskaznik na poczatek tablicy wierzcholkow

    Macierz macierz;

    // PARAMETRY SIMULATED ANNEALING

    int wierzcholek;

    // poczatkowa wartosc temperatury
    double startingTemp = 150;

    int iterations = 1000;

    // Wspolczynnik - mozliwosc wprowadzenia przez uzytkownika
    double alpha = 0.99999;

    // konstruktor grafu

    Graf(int w);

    // Uzupelnienie tablic

    void completeWierzcholki();

    int matrixValue(int i, int j);

    void completeMacierz(int droga, int i, int j);

    // Wyswietlenie tablicy wierzcholkow

    void displayWierzcholki();

    void choice();

    void build();

    // POMIARY

    void pomiary(int rozmiar);

    void menu();

    void menu2();
};

#endif // GRAF_H_INCLUDED

