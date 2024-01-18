#include "Travel.h"

    Travel::Travel(int roz, int start)
    {
        this->size1 = roz;
        this->start = start;

        travel = new int[size1+1];
    }

    void Travel::display()
    {
        for(int i=0; i<size1; i++)
            cout << travel[i] << "->";

        cout << travel[size1] << endl;
    }

    void Travel::generateTravel()
    {
        Tablica wierzcholki(size1, hOut1);

        // Dodanie wszystkich wierzcholkow do tablicy

        for(int i=0; i<size1; i++)
        {
            wierzcholki.complete(i, i);
        }

        wierzcholki.deleteElemAny(start+1);

        travel[0] = start;
        travel[size1] = start;

        for(int i=1; i<size1; i++)
        {
            int finder = -1;

            do
            {
                travel[i] = rand() % size1;

                // Znalezienie wierzcholka

                finder = wierzcholki.findElem(travel[i]);

            }while(finder==-1);

            // Usuniecie wierzcholka z tablicy wierzcholkow

            wierzcholki.deleteElemAny(finder+1);
        }
    }

    // Metoda zamieniajaca losowe dwa miasta w sciezce

    void Travel::swapCities()
    {
        int* newTravel = new int[size1+1];

        // uzupelnienie nowej tabeli

        for(int i=0; i<=size1; i++)
            newTravel[i] = travel[i];

        // losowanie indeksow miast

        do
        {
            city1 = rand() % size1;

        }while(city1 == 0);

        do
        {
            city2 = rand() % size1;

        }while(city2 == 0 || city2 == city1);

        newTravel[city1] = travel[city2];
        newTravel[city2] = travel[city1];

        delete[] travel;
        travel = newTravel;
    }

    void Travel::revertSwap()
    {
        int* newTravel = new int[size1+1];

        // uzupelnienie nowej tabeli

        for(int i=0; i<=size1; i++)
            newTravel[i] = travel[i];

        newTravel[city2] = travel[city1];
        newTravel[city1] = travel[city2];

        delete[] travel;
        travel = newTravel;
    }

    int* Travel::returnTravel()
    {
        return travel;
    }

    Travel::~Travel()
    {
        if(travel!=nullptr)
            delete[] travel;
    }
