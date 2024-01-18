#ifndef MACIERZ_H_INCLUDED
#define MACIERZ_H_INCLUDED
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "Travel.h"
#include "Population.h"

using namespace std;

 /**

 macierz krawedzi, kazda krawedz ma swoja wage

 1  jezeli a(i) jest lukiem wychodzacym
 -1 jezeli a(i) jest lukiem wchodzacym
 0  jezeli inaczej

**/


class Macierz
{

public:

    int rozmiar_w;
    int **macierz;       // Wskaznik na tablice dwuwymiarowa (macierz)

    int *najDroga = new int[rozmiar_w];
    //int *najDroga2 = new int[rozmiar_w+1];

    // koszt najkrotszej trasy
    int minKoszt= INT_MAX;

    int bestDistance;

    // Konstruktor domyslny

    Macierz();

    int matrixValue(int i, int j);

    void stworz(int rw);

    void completeMacierz(int droga, int i, int j);

    // REPREZENTACJA MACIERZOWA - wyswietlenie grafu

    void displayMacierz();

    bool findd(int arr[], int siize, int value);

    void algorytm(int droga[], int koszt, int miasto, int odwiedzone, int start);

    // ALGORYTM BRUTEFORCE

    int* bruteForce(int start);

    int returnCost();

    int bestDist();

    int getDistance(int *droga);

    // ALGORYTM SYMULOWANEGO WYZARZANIA

    Travel simulatedAnnealing(double startingTemperature, int iterations, double coolingRate, int start);

    // ALGORYTM GENETYCZNY

    int* geneticAlgorithm(int populationSize, int reproductionRate, int crossCoefficient, int mutationRate, int start, int choose);

    void menu();

    ~Macierz();
};

#endif // MACIERZ_H_INCLUDED

