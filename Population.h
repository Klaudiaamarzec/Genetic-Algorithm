#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "Travel.h"
#include "Tablica.h"

using namespace std;

class Population
{
private:
    int populationSize, matrixSize, start;
    int** population;
    int **matrix;
    HANDLE hOut1 = GetStdHandle( STD_OUTPUT_HANDLE );

public:

    // konstruktor populacji
    Population(int sizePop, int **matrixx, int matrixSixe, int start);

    void generatePopulation();

    int getDistance(int *droga);

    int* generateTravel();

    void display();

    void displayTravel(int index);

    int selection(int selectedIndex);

    void crossover(int choose);

    int* crossoverPMX(int parent1, int parent2, int x1, int x2);

    int* crossoverOX(int parent1, int parent2, int x1, int x2);

    void addtoPopulation(int *travel);

    void inversionMutation();

    void deleteTravels(int popSize);

    int* returnBest();

    ~Population();
};

#endif // POPULATION_H_INCLUDED
