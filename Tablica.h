#ifndef TABLICA_H_INCLUDED
#define TABLICA_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <windows.h>

using namespace std;

/// a) Tablica

class Tablica
{

 private:
    int* head;        //wskaŸnik na pocz¹tek tablicy
    int rozmiar;      //liczba elementów w tablicy
    HANDLE hOut;

 public:

     //konstruktor tablicy
     Tablica(int rozmiar, HANDLE h);

     //Menu dla tablicy

     void menu();

     void choice();

     //Uzupe³nienie tablicy wartosciami z pliku tekstowego

     void complete(int indeks, int liczba);

     //Wyswietlenie tablicy

     void display();

     void displayColor(int index);

     //dodawanie elementów na poczatek tablicy

     void addFirst(int dane);

     //dodawanie elementów na koñcu tablicy

     void addLast(int dane);

     //dodawanie elementów w dowolnym miejscu tablicy

     int addAnywhere(int indeks, int dane);

     //Wyszukiwanie elementu w tablicy

     int findElem(int value);

     //usuwanie elementu w dowolnym miejscu tablicy

     int deleteElemAny(int indeks);

     //Usuniecie pierwszego elementu z tablicy

     int deleteElemFirst();

     //Usuniecie ostatniego elementu z tablicy

     int deleteElemLast();

     //destruktor
     ~Tablica();
};

#endif // TABLICA_H_INCLUDED
