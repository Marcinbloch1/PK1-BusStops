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
	int GG, MM; ///< zmienna przechowuj¹ca godziny i minuty odjazdu autobusu
	char separator; ///< zmienna przechowuj¹ca znak dwukropka, separator
	Rozklad_jazdy * nast; ///< wskaŸnik na nastêpny element
};

/** Elementy podwieszonej listy jednokierunkowej */
struct Nr_linii
{
	int numer_linii; ///< zmienna przechowuj¹ca numery linii autobusowych 
	Rozklad_jazdy * pocz; ///< wskaŸnik na pierwszy element listy podwieszonej
	Nr_linii * nast; ///< wskaŸnik na nastêpny element
};

/** Elementy listy jednokierunkowej */
struct Przystanek
{
	string nazwa_przystanku; ///< zmienna przechowuj¹ca nazwy przystanków
	Przystanek * nast; ///< wskaŸnik na nastêpny element
	Nr_linii * pocz; ///< wskaŸnik na pierwszy element listy podwieszonej
};


/** Funkcja sprawdza czy u¿ytkownik wpisa³ poprawnie dane
@param argc liczba parametrów wywo³ania funkcji main
@param argv tablica parametrów przekazywana z wiersza poleceñ*/
int SprawdzWywolanie(int argc, char * argv[]);

/** Funkcja tworzy pliki testowe po wywo³aniu programu z prze³¹cznikiem -g
@param liczba_liniiint zmienna przechowuj¹ca liczbê linii
@param liczba_kursówint zmienna przechowuj¹ca liczbê kursów
@param liczba_przystankówint zmienna przechowuj¹ca liczbê przystanków*/
void TworzeniePlikowTestowych(int liczba_liniiint, int liczba_kursowint, int liczba_przystankowint);

/** Funkcja wczytuje dane z plików wejœciowych
@param glowa wskaŸnik na pierwszy element listy przystanków
@param argc liczba parametrów wywo³ania funkcji main
@param argv tablica parametrów przekazywana z wiersza poleceñ*/
int WczytajDoStruktury(Przystanek * & glowa, int argc, char * argv[]);

/** Funkcja dodaje dane wczytame wczeœniej z plików wejœciowych do listy
@param glowa wskaŸnik na pierwszy element listy przystanków
@param nazwa_przystanku zmienna przechowuj¹ca nazwê przystanku
@param numer_linii zmienna przechowuj¹ca numer linii
@param GG zmienna przechowuj¹ca godzinê odjazdu
@param MM zmienna przechowuj¹ca minuty odjazdu
@param separator zmienna przechowuj¹ca œrednik (separator)
*/
void DodajDoStruktury(Przystanek * & glowa, string nazwa_przystanku, int numer_linii, int GG, int MM, char separator);

/** Funkcja sortuje odjazdy na przystankach wed³ug godziny odjazdu
@param glowa wskaŸnik na pierwszy element listy przystanków
*/
void SortujStrukture(Przystanek * glowa);

/** Funkcja tworzy pliki tekstowe z nazw¹ przystanku oraz wypisuje do nich posortowane odjazdy
@param glowa wskaŸnik na pierwszy element listy przystanków
*/
void WypiszDoPlikow(Przystanek * glowa);

/** Funkcja kasuje strukturê danych przystanków, numerów linii, rozk³adów jazdy
@param glowa wskaŸnik na pierwszy element listy przystanków
*/
void KasowanieStruktury(Przystanek * & glowa);

#endif