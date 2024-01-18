#include "Graf.h"

// konstruktor grafu

    Graf::Graf(int w)
    {
        this->rozmiarw = w;

        // Stworzenie tablicy dynamicznej dlawierzcholków
        this->wierzcholki = new int[w];

        build();
    }

    // Uzupelnienie tablic

    void Graf::completeWierzcholki()
    {
        for(int i=0; i<rozmiarw; i++)
        {
            wierzcholki[i] = i;
        }
    }

    int Graf::matrixValue(int i, int j)
    {
        return macierz.matrixValue(i, j);
    }

    void Graf::completeMacierz(int droga, int i, int j)
    {
        macierz.completeMacierz(droga, i, j);
    }

    // Wyswietlenie tablicy wierzcholkow

    void Graf::displayWierzcholki()
    {
        for(int i=0; i<rozmiarw; i++)
            cout << wierzcholki[i] << " ";

        cout << endl;
    }

    void Graf::choice()
    {
        int wybor, wierzcholek=0;

        //cout <<"Podaj indeks wierzcholka startowego: ";
        //cin >> wierzcholek;

        macierz.displayMacierz();
        cout << endl;

        do
        {
            menu();
            cin >> wybor;
            system("cls");

            switch(wybor)
            {
                case 1:
                    {
                        // Brute Force

                        cout << endl << "ALGORYTM BRUTE FORCE" << endl;

                        macierz.displayMacierz();

                        int blad;

                        do
                        {
                            blad=0;

                            if(wierzcholek>=rozmiarw || wierzcholek<0)
                                blad=1;

                        }while(blad==1);

                        int *wynik = macierz.bruteForce(wierzcholek);

                        cout << endl << "NAJLEPSZE ROZWIAZANIE: ";
                        for (int i = 0; i < rozmiarw; i++)
                            cout << wynik[i] << " -> ";

                        cout << wynik[rozmiarw] << endl;

                        int wynik2 = macierz.returnCost();

                        cout << "Koszt: " << wynik2 << endl << endl;

                        break;
                    }
                case 2:
                    {
                        // Symulowane Wyzarzanie

                        cout << endl << "ALGORYTM SYMULOWANEGO WYZARZANIA" << endl;

                        //macierz.displayMacierz();

                        int blad;

                        do
                        {
                            blad=0;

                            if(wierzcholek>=rozmiarw || wierzcholek<0)
                                blad=1;

                        }while(blad==1);

                        Travel best = macierz.simulatedAnnealing(startingTemp, iterations, alpha, wierzcholek);

                        cout << "NAJLEPSZE ROZWIAZANIE" << endl;
                        best.display();

                        int wynik2 = macierz.bestDist();

                        cout << "Najlepszy koszt: " << wynik2 << endl << endl;

                        break;
                    }

                case 3:
                    {
                        // Uzupelnienie parametrow przez uzzytkownika

                        int popSize;    // rozmiar populacji

                        int repRate;    // czestosc reprodukcji (iteracje algorytmu)

                        int crossCoeff;  // czestosc krzyzowania

                        int mutRate;    // czestosc mutacji

                        cout << "PODAJ PARAMETRY ALGORYTMU:\n";

                        cout << "Rozmiar populacji: ";
                        cin >> popSize;

                        cout << "Czestosc reprodukcji: ";
                        cin >> repRate;

                        cout << "Czestosc krzyzowania: ";
                        cin >> crossCoeff;

                        cout << "Czestosc mutacji: ";
                        cin >> mutRate;

                        cout << endl;

                        while(popSize<=0 || repRate<=0 || crossCoeff<0 || mutRate<0)
                        {
                            cout << "PODANO NIEPRAWIDLOWE PARAMETRY! PODAJ PARAMETRY JESZCZE RAZ:\n";

                            cout << "Rozmiar populacji: ";
                            cin >> popSize;

                            cout << "Czestosc reprodukcji: ";
                            cin >> repRate;

                            cout << "Czestosc krzyzowania: ";
                            cin >> crossCoeff;

                            cout << "Czestosc mutacji: ";
                            cin >> mutRate;

                            cout << endl;
                        }

                        int wybor;

                        menu2();
                        cin >> wybor;
                        system("cls");

                        int *best = macierz.geneticAlgorithm(popSize, repRate, crossCoeff, mutRate, wierzcholek, wybor);

                        int bestCost = macierz.getDistance(best);

                        cout <<"Najlepsze rozwiazanie\n";

                        for(int i=0; i<rozmiarw; i++)
                                cout << best[i] << "->";

                        cout << wierzcholek  << ": " << bestCost << endl << endl;

                        break;
                    }
                case 4:
                    {
                        macierz.displayMacierz();
                        cout << endl;
                        break;
                    }
            }
        }
        while(wybor!=0);
    }

    void Graf::build()
    {
        macierz.stworz(rozmiarw);
    }

    // POMIARY

    void Graf::pomiary(int rozmiar)
    {
        ofstream plik("pomiary.txt", std::ios::app);
        srand(time(NULL));

        int *best;

        if(plik.is_open())
        {
            // 2. Algorytm Genetyczny

            // Losowanie wierzcholka startowego

            //cout <<"Wh\n";

            //wierzcholek = rand()%rozmiarw;

            //pomiar czasu przed wykonaniem operacji
            LARGE_INTEGER start;
            QueryPerformanceCounter(&start);

            best = macierz.geneticAlgorithm(200, 100, 200, 2, 0, 2);

            //pomiar czasu po wykonaniu operacji
            LARGE_INTEGER koniec;
            QueryPerformanceCounter(&koniec);

            //obliczenie czasu
            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);
            double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

            plik << czas << "   ";

            plik << endl;
        }
        else
            cout << "Nie udalo sie otworzyc pliku" << endl;

        plik.close();

        /*int *wynik = macierz.bruteForce(0);
        int wynik2 = macierz.returnCost();

        ofstream plik2("blad.txt", std::ios::app);

        plik2 << "BEST: " << wynik2 << ", ";

        int bestCost = macierz.getDistance(best);

        if(plik2.is_open())
        {
            plik2 << bestCost << endl;
        }
        else
            cout <<"Nie udalo sie otworzyc pliku BLAD" << endl;

        plik2.close();*/
    }

    void Graf::menu2()
    {
        cout << "1. Krzyzowanie PMX\n";
        cout << "2. Krzyzowanie OX\n";
        cout << "0. EXIT\n";
    }

    void Graf::menu()
    {
        cout << "1. Algorytm Brute Force\n";
        cout << "2. Algorytm Symulowanego Wyzarzania\n";
        cout << "3. Algorytm Genetyczny\n";
        cout << "4. Wyswietlenie macierzy\n";
        cout << "0. EXIT\n";
    }
