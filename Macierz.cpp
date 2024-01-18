#include "Macierz.h"

 /**

 macierz krawedzi, kazda krawedz ma swoja wage

 1  jezeli a(i) jest lukiem wychodzacym
 -1 jezeli a(i) jest lukiem wchodzacym
 0  jezeli inaczej

**/

    int Macierz::matrixValue(int i, int j)
    {
        return macierz[i][j];
    }

    // Konstruktor domyslny

    Macierz::Macierz(): macierz(nullptr) {}

    void Macierz::stworz(int rw)
    {
        // Przekazujemy tablice wierzcholkow
        this->rozmiar_w = rw;

        // Stworzenie tablicy dwuwymiarowej

        // alokacja pamieci dla wierszy
        macierz = new int*[rozmiar_w];

        // alokacja pamiêci dla kolumn
        for (int i = 0; i < rozmiar_w; i++)
        {
            macierz[i] = new int[rozmiar_w];
        }
    }

    void Macierz::completeMacierz(int droga, int i, int j)
    {
        macierz[i][j] = droga;
    }

    // REPREZENTACJA MACIERZOWA - wyswietlenie grafu

    void Macierz::displayMacierz()
    {
        cout << endl << " MIASTA" << endl;

        cout << "   |";

        for(int i=0; i<rozmiar_w; i++)
            cout << setw(6) << i << " |";

        cout << endl;

        cout << "----";

        for(int i=0; i<rozmiar_w*8; i++)
            cout << "-";

        cout << endl;

        for(int i=0; i<rozmiar_w; i++)
        {
            cout << setw(2) << i << " |";
            for(int j=0; j<rozmiar_w; j++)
            {

                cout << setw(4) << macierz[i][j] << "   |";

            }
            cout << endl;
        }
    }

    bool Macierz::findd(int arr[], int siize, int value)
    {
        for(int i=0; i<siize; ++i)
        {
            if(arr[i] == value)
                return true;
        }

        return false;
    }

    void Macierz::algorytm(int droga[], int koszt, int miasto, int odwiedzone, int start)
    {
        if(odwiedzone == rozmiar_w)
        {
            // Powrot do miasta poczatkowego
            koszt += macierz[miasto][start];

            if(koszt < minKoszt)
            {
                minKoszt = koszt;
                for(int i=0; i<rozmiar_w; i++)
                    najDroga[i] = droga[i];
            }

            /*for(int i=0; i<rozmiar_w; i++)
                cout << droga[i] << " -> ";

            cout << droga[rozmiar_w] << ": " << koszt << endl;*/

            return;
        }

        for(int miasto2 = 0; miasto2 < rozmiar_w; miasto2++)
        {
            if(miasto2 == miasto)
                continue;

            if(!findd(droga, odwiedzone, miasto2))
            {
                int nowyKoszt = koszt + macierz[miasto][miasto2];
                droga[odwiedzone] = miasto2;
                algorytm(droga, nowyKoszt, miasto2, odwiedzone+1, start);
            }
        }
    }

    // ALGORYTM BRUTEFORCE

    int* Macierz::bruteForce(int start)
    {
        int droga[rozmiar_w+1];

        // Pierwszym wierzcholkiem jest wierzcholek startowy
        droga[0] = start;
        droga[rozmiar_w] = start;

        algorytm(droga, 0, start, 1, start);

        return najDroga;
    }

    int Macierz::returnCost()
    {
        return minKoszt;
    }

    int Macierz::bestDist()
    {
        return bestDistance;
    }

    int Macierz::getDistance(int *droga)
    {
        int koszt = 0;

        for(int i=0; i<rozmiar_w; i++)
            koszt += macierz[droga[i]][droga[i+1]];

        return koszt;
    }

    // ALGORYTM SYMULOWANEGO WYZARZANIA

    Travel Macierz::simulatedAnnealing(double startingTemperature, int iterations, double coolingRate, int start)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        double t = startingTemperature;

        Travel bestTravel(rozmiar_w, start);

        // Przed startem algorytmu generuje poczatkowa (losowa) trase i obliczam jej koszt

        Travel currentTravel(rozmiar_w, start);
        currentTravel.generateTravel();

        int *best = new int[rozmiar_w+1];

        for(int j=0; j<=rozmiar_w; j++)
            best[j] = currentTravel.returnTravel()[j];

        int currentDistance = getDistance(best);

        //for(int i=0; i<=rozmiar_w; i++)
            //najDroga2[i] = firstTravel.returnTravel()[i];

        bestDistance = currentDistance;

        for(int i=0; i<=currentTravel.size1; i++)
            bestTravel.travel[i] = currentTravel.travel[i];

        int iter = 0;

        // glowna petla

        //for(int i=0; i<iterations; i++)
        //{
            while(t>0.1)
            {
                // W kazdej iteracji nastepuje zmaiana dwoch losowych miast w sciezce

                currentTravel.swapCities();

                int *trav = new int[rozmiar_w+1];

                for(int j=0; j<=rozmiar_w; j++)
                    trav[j] = currentTravel.returnTravel()[j];

                currentDistance = getDistance(trav);

                //cout << "Current distance " << currentDistance << endl;
                //cout << "Best distance " << bestDistance << endl;

                if(currentDistance < bestDistance)
                {
                    bestDistance = currentDistance;

                    best = trav;

                    for(int i=0; i<=currentTravel.size1; i++)
                        bestTravel.travel[i] = currentTravel.travel[i];

                }
                else
                {
                    // Sprawdzenie czy funkcja Boltzmana rozkladu prawdopodobienstwa
                    // jest mniejsza od losowo wybranej wartosci z przedzialu [0,1]
                    // Jesli tak, to cofamy zamiane miast
                    // Jesli nie, zachowujemy nowy porzadek miast, gdyz moze to pomoc w
                    // uniknieciu lokalnych minimow

                    long probability = exp(-(bestDistance - currentDistance)/t);
                    double random = static_cast<double>(std::rand()) / RAND_MAX;      // [0,1)

                    if(probability<random)
                        currentTravel.revertSwap();
                }

                delete[] trav;
                t *= coolingRate;

                // Po kazdej iteracji temperatura jest zmniejszana
                // Sposob obnizania temperatury: T(i+1) = a * T(i)

                iter++;
            }
            //else
                //continue;
        //}

        //cout << "Number of iterations: " << iter << endl;

        return bestTravel;
    }

    int* Macierz::geneticAlgorithm(int populationSize, int reproductionRate, int crossCoefficient, int mutationRate, int start, int choose)
    {
        Population population(populationSize, macierz, rozmiar_w, start);
        population.generatePopulation();

        // Uzytkownik moze wybrac dany operator krzyzowania - 1 lub 2 ( bo na 2 sposoby ma byc zrobione)

        for(int j=0; j<reproductionRate; j++)
        {
            for(int i=0; i<crossCoefficient; i++)
                population.crossover(choose);

            for(int i=0; i<mutationRate; i++)
                population.inversionMutation();

            population.deleteTravels(populationSize);

            /*cout <<"Po jednej petli\n";
            population.display();
            cout << endl;*/
        }

        //cout << "Finalna populacja\n";
        //population.display();

        int *best = new int[rozmiar_w+1];

        for(int i=0; i<=rozmiar_w; i++)
            best[i] = population.returnBest()[i];

        return best;
    }

    void Macierz::menu()
    {
        cout << "1. Krzyzowanie PMX\n";
        cout << "2. Krzyzowanie OX\n";
        cout << "0. EXIT\n";
    }

    Macierz::~Macierz()
    {
        for (int i = 0; i < rozmiar_w; i++) {
            delete[] macierz[i];
        }

        delete[] macierz;

        if(najDroga!=nullptr)
            delete[] najDroga;
    }
