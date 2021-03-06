#ifndef FUNCKJE_H
#define FUNCKJE_H

#include <iostream>
using namespace std;

/**
@author Marcin Bloch
*/

/** Elementy podwieszonej listy jednokierunkowej */
struct Rozklad_jazdy
{
	int GG, MM; ///< zmienna przechowująca godziny i minuty odjazdu autobusu
	char separator; ///< zmienna przechowująca znak dwukropka, separator
	Rozklad_jazdy * nast; ///< wskaźnik na następny element
};

/** Elementy podwieszonej listy jednokierunkowej */
struct Nr_linii
{
	int numer_linii; ///< zmienna przechowująca numery linii autobusowych 
	Rozklad_jazdy * pocz; ///< wskaźnik na pierwszy element listy podwieszonej
	Nr_linii * nast; ///< wskaźnik na następny element
};

/** Elementy listy jednokierunkowej */
struct Przystanek
{
	string nazwa_przystanku; ///< zmienna przechowująca nazwy przystanków
	Przystanek * nast; ///< wskaźnik na następny element
	Nr_linii * pocz; ///< wskaźnik na pierwszy element listy podwieszonej
};


/** Funkcja sprawdza czy użytkownik wpisał poprawnie dane
@param argc liczba parametrów wywołania funkcji main
@param argv tablica parametrów przekazywana z wiersza poleceń*/
int SprawdzWywolanie(int argc, char * argv[]);

/** Funkcja tworzy pliki testowe po wywołaniu programu z przełącznikiem -g
@param liczba_liniiint zmienna przechowująca liczbę linii
@param liczba_kursówint zmienna przechowująca liczbę kursów
@param liczba_przystankówint zmienna przechowująca liczbę przystanków*/
void TworzeniePlikowTestowych(int liczba_liniiint, int liczba_kursowint, int liczba_przystankowint);

/** Funkcja wczytuje dane z plików wejściowych
@param glowa wskaźnik na pierwszy element listy przystanków
@param argc liczba parametrów wywołania funkcji main
@param argv tablica parametrów przekazywana z wiersza poleceń*/
int WczytajDoStruktury(Przystanek * & glowa, int argc, char * argv[]);

/** Funkcja dodaje dane wczytame wcześniej z plików wejściowych do listy
@param glowa wskaźnik na pierwszy element listy przystanków
@param nazwa_przystanku zmienna przechowująca nazwę przystanku
@param numer_linii zmienna przechowująca numer linii
@param GG zmienna przechowująca godzinę odjazdu
@param MM zmienna przechowująca minuty odjazdu
@param separator zmienna przechowująca średnik (separator)
*/
void DodajDoStruktury(Przystanek * & glowa, string nazwa_przystanku, int numer_linii, int GG, int MM, char separator);

/** Funkcja sortuje odjazdy na przystankach według godziny odjazdu
@param glowa wskaźnik na pierwszy element listy przystanków
*/
void SortujStrukture(Przystanek * glowa);

/** Funkcja tworzy pliki tekstowe z nazwą przystanku oraz wypisuje do nich posortowane odjazdy
@param glowa wskaźnik na pierwszy element listy przystanków
*/
void WypiszDoPlikow(Przystanek * glowa);

/** Funkcja kasuje strukturę danych przystanków, numerów linii, rozkładów jazdy
@param glowa wskaźnik na pierwszy element listy przystanków
*/
void KasowanieStruktury(Przystanek * & glowa);

#endif