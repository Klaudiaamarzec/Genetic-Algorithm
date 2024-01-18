#ifndef TRAVEL_H_INCLUDED
#define TRAVEL_H_INCLUDED
#include "Tablica.h"

using namespace std;

class Travel
{
public:
    int start;
    int size1;
    int *travel;
    int city1, city2;                   // indeksy miast do zamiany
    HANDLE hOut1 = GetStdHandle( STD_OUTPUT_HANDLE );

    Travel(int roz, int start);

    void display();

    void generateTravel();

    // Metoda zamieniajaca losowe dwa miasta w sciezce

    void swapCities();

    void revertSwap();

    int* returnTravel();

    ~Travel();
};

#endif // TRAVEL_H_INCLUDED
