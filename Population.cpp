#include "Population.h"

    Population::Population(int sizePop, int **matrixx, int matrixSize, int start)
    {
        this->populationSize = sizePop;
        this->matrixSize = matrixSize;
        this->matrix = new int*[matrixSize];

        for(int i=0; i<matrixSize; i++)
        {
            matrix[i] = new int[matrixSize];

            for(int j=0; j<matrixSize; j++)
            {
                matrix[i][j] = matrixx[i][j];
            }
        }

        this->start = start;
        this->population = new int*[populationSize];

        for(int i=0; i<populationSize; i++)
        {
            this->population[i] = new int[matrixSize+1];
        }
    }

    int* Population::generateTravel()
    {
        // wygenerowanie losowej sciezki

        int *travel = new int[matrixSize+1];

        Tablica wierzcholki(matrixSize, hOut1);

        // Dodanie wszystkich wierzcholkow do tablicy

        for(int i=0; i<matrixSize; i++)
        {
            wierzcholki.complete(i, i);
        }

        wierzcholki.deleteElemAny(start+1);

        travel[0] = start;
        travel[matrixSize] = start;

        for(int i=1; i<matrixSize; i++)
        {
            int finder = -1;

            do
            {
                travel[i] = rand() % matrixSize;

                // Znalezienie wierzcholka

                finder = wierzcholki.findElem(travel[i]);

            }while(finder==-1);

            // Usuniecie wierzcholka z tablicy wierzcholkow

            wierzcholki.deleteElemAny(finder+1);
        }

        return travel;
    }

    void Population::generatePopulation()
    {
        // WYGENEROWANIE POPULACJI

        for(int i=0; i<populationSize; i++)
        {
            int *travel = generateTravel();

            for(int j=0; j<=matrixSize; j++)
                this->population[i][j] = travel[j];
        }
    }

    void Population::display()
    {
        for (int i = 0; i < populationSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                cout << population[i][j] << "->";
            }

            cout << population[i][matrixSize] << ": ";

            int cost = getDistance(population[i]);

            cout << cost << endl;
        }

        cout << endl;
    }

    void Population::displayTravel(int index)
    {
        for(int i=0; i<matrixSize; i++)
            cout << population[index][i] << "->";

        cout << population[index][matrixSize] << ": " << getDistance(population[index]) << endl;
    }

    int Population::getDistance(int *travel)
    {
        int cost = 0;

        for(int i=0; i<matrixSize; i++)
            cost += matrix[travel[i]][travel[i+1]];

        return cost;
    }

    int Population::selection(int selectedIndex)
    {
        srand(time(NULL));

         // 1. Selekcja turniejowa: Najsilniejsi osobnicy moga przekazac swoja informacje genetyczna potomstwu

        // Losowy wybor czterech grup zawodnikow. W kazdej po (populationSize/4 zawodnikow)

        int groupSize = ceil(populationSize/8); //ceil(populationSize/10);

        // Wylosowanie zawodnikow do danych grup (ideksy)

        int group1[groupSize];

        // Tablica do œledzenia wylosowanych indeksów

        bool* used = new bool[populationSize];
        for(int i = 0; i < populationSize; i++)
            used[i] = false;

        used[selectedIndex] = true;

        for(int i=0; i<groupSize; i++)
        {
            int los;

            do
            {
                los = rand() % populationSize;

            }while(used[los]);

            group1[i] = los;
            used[los] =true;
        }

        int group2[groupSize];

        for(int i = 0; i < populationSize; i++)
            used[i] = false;

        used[selectedIndex] = true;

        for(int i=0; i<groupSize; i++)
        {
            int los;

            do
            {
                los = rand() % populationSize;

            }while(used[los]);

            group2[i] = los;
            used[los] = true;
        }

        int group3[groupSize];

        for(int i = 0; i < populationSize; i++)
            used[i] = false;

        used[selectedIndex] = true;

        for(int i=0; i<groupSize; i++)
        {
            int los;

            do
            {
                los = rand() % populationSize;

            }while(used[los]);

            group3[i] = los;
            used[los] = true;
        }

        int group4[groupSize];

        for(int i = 0; i < populationSize; i++)
            used[i] = false;

        used[selectedIndex] = true;

        for(int i=0; i<groupSize; i++)
        {
            int los;

            do
            {
                los = rand() % populationSize;

            }while(used[los]);

            group4[i] = los;
            used[los] = true;
        }

        // Zwyciezcy grup

        int group5[4];

        // Grupa1

        int mini = getDistance(population[group1[0]]);
        int winner = group1[0];

        for(int j=1; j<groupSize; j++)
        {
            int newCost = getDistance(population[group1[j]]);
            if(newCost < mini)
            {
                mini = newCost;
                winner = group1[j];
            }
        }

        group5[0] = winner;

        mini = getDistance(population[group2[0]]);
        winner = group2[0];

        for(int j=1; j<groupSize; j++)
        {
            int newCost = getDistance(population[group2[j]]);
            if(newCost < mini)
            {
                mini = newCost;
                winner = group2[j];
            }
        }

        group5[1] = winner;

        mini = getDistance(population[group3[0]]);
        winner = group3[0];

        for(int j=1; j<groupSize; j++)
        {
            int newCost = getDistance(population[group3[j]]);
            if(newCost < mini)
            {
                mini = newCost;
                winner = group3[j];
            }
        }

        group5[2] = winner;

        mini = getDistance(population[group4[0]]);
        winner = group4[0];

        for(int j=1; j<groupSize; j++)
        {
            int newCost = getDistance(population[group4[j]]);
            if(newCost < mini)
            {
                mini = newCost;
                winner = group4[j];
            }
        }

        group5[3] = winner;

        // NAJLEPSZY Z NAJLEPSZYCH

        mini = getDistance(population[group5[0]]);;
        winner = group5[0];

        for(int j=1; j<4; j++)
        {
            int newCost = getDistance(population[group5[j]]);
            if(newCost < mini)
            {
                mini = newCost;
                winner = group5[j];
            }
        }

        return winner;
    }

    void Population::crossover(int choose)
    {
        // Wybor dwoch osobnikow do krzyzowania

        int candidate1 = rand() % populationSize;//selection(-1); //rand() % populationSize;
        int candidate2;
        //

        bool result = false;

        do
        {
            candidate2 = rand() % populationSize; //selection(candidate1); //rand() % populationSize;

            if(candidate1 == candidate2)
                result = true;
            else
                result = false;

        }while(result);

        // Krzyzowanie

        // Wybor losowy dwoch punktow krzyzowania - bez pierwszego i ostatniego bo to ten sam punkt startowy

        int x2, x1 = rand() % (matrixSize-1) +1;

        result = false;

        do
        {
            x2 = rand() % (matrixSize-1) +1;

            if(x1 == x2)
                result = true;
            else
                result = false;

        }while(result);

        int *child1, *child2;

        if(x2<x1)
        {
            // zamiana
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        //cout << "Przedzial: " << x1 << " " << x2 << endl;

        switch(choose)
        {
            case 1:
            {
                child1 = crossoverPMX(candidate1, candidate2, x1, x2);
                child2 = crossoverPMX(candidate2, candidate1, x1, x2);

                break;
            }
            case 2:
            {
                child1 = crossoverOX(candidate1, candidate2, x1, x2);
                child2 = crossoverOX(candidate2, candidate1, x1, x2);

                break;
            }
        }

        int cost1 = getDistance(child1);
        int cost2 = getDistance(child2);

        if(cost1<cost2)
            addtoPopulation(child1);
        else
            addtoPopulation(child2);
    }

    int* Population::crossoverPMX(int parent1, int parent2, int x1, int x2)
    {
        int sizee = x2-x1 +1;

        int *child1 = new int[sizee];
        int *child2 = new int[sizee];

        for(int i=x1, j=0; i<=x2; i++, j++)
        {
            child1[j] = population[parent1][i]; //parent1.getTravel()[i];
            child2[j] = population[parent2][i]; //parent2.getTravel()[i];
        }

        /*cout << "KIDS\n";

        for(int i=0; i<sizee; i++)
            cout << child1[i] << " ";

        cout << endl;

        for(int i=0; i<sizee; i++)
            cout << child2[i] << " ";

        cout << endl;*/

        // POTOMEK

        int *child = new int[matrixSize+1];

        for(int i=0; i<=matrixSize; i++)
            child[i] = 0;

        for(int i=x1; i<=x2; i++)
            child[i] = population[parent1][i];

        // Zamiana wycietych czesci

        /*for (int i = x1, j = 0; i <= x2; i++, j++)
        {
            parent2.getTravel()[i] = child1[j];
            parent1.getTravel()[i] = child2[j];
        }

        parent1.display();
        parent2.display();*/

        // Znalezienie elementow ktore nie zostaly skopiowane

        for(int i=0; i<sizee; i++)
        {
            bool result = true;
            for(int j=0; j<sizee; j++)
            {
                if(child2[i] == child1[j])
                {
                    result = true;
                    break;
                }
                else
                    result = false;
            }

            // Elementy ktore nie zostaly skopiowane

            if(!result)
            {
                // child1[i] eleemnt skopiowany z P1 na jego miejsce

                // (i,j) = (child2[i], child1[i])

                // Proba umieszczenia child2[i] na pozycji zajmowanej przez child1[i] w rodzicu P2

                for(int j=0; j<=matrixSize; j++)
                {
                    if(population[parent2][j] == child1[i])
                    {
                        // Sprawdzenie, czy mozna tu umiescic i - mozna tylko w obszarze poza wycieciem

                        if(j < x1 || j > x2)
                        {
                            // Umieszczenie

                            child[j] = child2[i];
                        }
                        else
                        {
                            // Sprawdzenie, ktory wierzcholek zostal skopiowany na miejsce child1
                            int index, newIndex, exitIndex;
                            int oldIndex = i;

                            //cout << "RODZICE\n";

                            //displayTravel(parent1);
                            //displayTravel(parent2);

                            do
                            {
                                //cout << "Para: " << child2[oldIndex] << ", " << child1[oldIndex] << endl;

                                for(int k=0; k<matrixSize; k++)
                                {
                                    if(child1[oldIndex] == population[parent2][k])
                                        exitIndex = k;
                                }

                                if(exitIndex < x1 || exitIndex > x2)
                                {
                                    newIndex = exitIndex;
                                }
                                else
                                {
                                    for(int k=0; k<sizee; k++) //sizee
                                    {
                                        if(child1[oldIndex] == child2[k])
                                            index = k;
                                    }

                                    // Skopiowany wierzcholek to child1[index]

                                    // Miejsce zajmowane przez child1[index] w P2

                                    for(int k=0; k<matrixSize; k++)
                                    {
                                        if(child1[index] == population[parent2][k])
                                            newIndex = k;
                                    }

                                    // Znalezienie indeksu elementu pod parent2[index] w child2

                                    for(int b=0; b<sizee; b++)
                                    {
                                        if(child2[b] == population[parent2][newIndex])
                                            oldIndex = b;
                                    }

                                }

                            }while(newIndex >= x1 && newIndex <=x2);

                            // Umieszczenie child2 na miejsce zajmowane w P2 przez child2[j]

                            child[newIndex] = child2[i];
                        }
                    }
                }
            }
        }

        // Skopiowanie pozostalych wierzcholkow z P2

        for(int i=0; i<=matrixSize; i++)
        {
            if(child[i] == 0)
            {
                child[i] = population[parent2][i];
            }
        }

        /*cout << "KIDOOO\n";

        for(int i=0; i<=matrixSize; i++)
            cout << child[i] << " ";

        cout << endl;*/

        return child;
    }

    int* Population::crossoverOX(int parent1, int parent2, int x1, int x2)
    {

        //cout <<"Kandydaci\n";
        //displayTravel(parent1);
        //displayTravel(parent2);

        int sizee = x2-x1 +1;

        int *child1 = new int[sizee];
        int *child2 = new int[sizee];

        for(int i=x1, j=0; i<=x2; i++, j++)
        {
            child1[j] = population[parent1][i]; //parent1.getTravel()[i];
            child2[j] = population[parent2][i]; //parent2.getTravel()[i];
        }

        // POTOMEK

        int *child = new int[matrixSize+1];

        for(int i=0; i<=matrixSize; i++)
            child[i] = 0;

        for(int i=x1; i<=x2; i++)
            child[i] = population[parent1][i];

        // Stowrzenie tablicy z elmentami z P2 ktore moga zostac wstawione do potomka (pomijajac pierwszy i ostatni element poniewaz jest to wierzcholek startowy

        int parSize = matrixSize-1-sizee;

        int *parent = new int[parSize];

        // Uzupelnienie zerami dla przejrzystosci

        for(int i=0; i<parSize; i++)
            parent[i] = 0;

        int parentIndex = x2+1;

        for(int i=0; i<parSize; i++, parentIndex++)
        {
            // Sprawdzenie czy nie wyszlo poza zakres

            if(parentIndex>matrixSize)
                parentIndex = 1;

            // Sprawdzenie czy element ktory ma byc skopiowany nie znajduje sie juz w potomku

            bool result = false;

            for(int k=0; k<=matrixSize; k++)
            {
                if(child[k] == population[parent2][parentIndex])
                    result = true;
            }

            if(!result)
            {
                // Mozna skopiowac

                //cout << "Element z P2: " << population[parent2][parentIndex] << " nie wystepuje w potomku\n";

                parent[i] = population[parent2][parentIndex];
            }
            else
            {
                i--;    // Aby jeszcze raz rozpatrzec dla tego indeksu
            }
        }

        // Uzupelnienie potomka wartosciami w parent

        int childIndex = x2+1;

        for(int i=0; i<parSize; i++, childIndex++)
        {
            // Sprawdzenie czy indeks nie wyszedl poza zakres

            if(childIndex>=matrixSize)
                childIndex = 1;

            child[childIndex] = parent[i];
        }

        /*cout <<"CHILD\n";

        for(int i=0; i<matrixSize; i++)
            cout << child[i] << "->";

        cout << child[matrixSize] << endl;*/

        return child;
    }

    void Population::inversionMutation()
    {
        // Wybranie losowo sciezki do mutacji

        int candidate = rand() % populationSize;    //selection();

        // Wybranie losowo dwoch pozycji

        int x2, x1 = rand() % (matrixSize-1) +1;

        bool result = false;

        do
        {
            x2 = rand() % (matrixSize-1) +1;

            if(x1 == x2)
                result = true;
            else
                result = false;

        }while(result);

        if(x2<x1)
        {
            // zamiana
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        //cout << "Pozycje: od " << x1 << " do " << x2 << endl;

        int sizee = x2-x1 +1;

        int *table = new int[sizee];

        for(int i=x1, j=0; i<=x2; i++, j++)
        {
            table[j] = population[candidate][i];
        }

        // Odworcenie kolejnosci wierzcholkow pomiedzy nimi

        int idx = sizee-1;
        int *secondTable = new int[sizee];

        for(int i=0; i<sizee; i++)
            secondTable[i] = table[idx-i];

        // Zmodyfikowanie wylosowanej tablicy

        for(int i=0, j=x1; j<=x2; j++, i++)
            population[candidate][j] = secondTable[i];
    }

    void Population::addtoPopulation(int *travel)
    {
        int** newPopulation = new int*[populationSize+1];

        for(int i=0; i<populationSize; i++)
        {
            newPopulation[i] = new int[matrixSize+1];
            for(int j=0; j<=matrixSize; j++)
            {
                newPopulation[i][j] = population[i][j];
            }
            delete[] population[i];
        }

        delete[] population;

        newPopulation[populationSize] = new int[matrixSize+1];

        for(int i=0; i<=matrixSize; i++)
            newPopulation[populationSize][i] = travel[i];

        population = newPopulation;
        populationSize++;
    }

    void Population::deleteTravels(int popSize)
    {
        // 1. Posortowanie sciezek rosnaco wedlug dlugosci

        for(int i=0; i<populationSize; i++)
        {
            for(int j=0; j<populationSize-1; j++)
            {
                int cost1 = getDistance(population[j]);
                int cost2 = getDistance(population[j+1]);

                if(cost1 > cost2)
                {
                    int *temp = population[j];
                    population[j] = population[j+1];
                    population[j+1] = temp;
                }
            }
        }

        // 2. Usuniecie najgorszych rozwiazan

        int **newPopulation = new int*[popSize];

        for(int i=0; i<popSize; i++)
        {
            newPopulation[i] = new int[matrixSize+1];
            for(int j=0; j<=matrixSize; j++)
            {
                newPopulation[i][j] = population[i][j];
            }
        }

        // Zwolnienie pamieci zajmowanej przez istniejaca tablice

        for(int i=0; i<populationSize; i++)
            delete[] population[i];

        delete[] population;
        population = newPopulation;
        populationSize = popSize;
    }

    int* Population:: returnBest()
    {
        return population[0];
    }

    Population::~Population()
    {
        for(int i=0; i<matrixSize; i++)
            delete[] matrix[i];

        delete[] matrix;

        for (int i = 0; i < populationSize; i++)
        {
            if(population[i] != nullptr)
                delete[] population[i];
        }

        if(population!=nullptr)
            delete[] population;
    }
