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
	int GG, MM; ///< zmienna przechowuj�ca godziny i minuty odjazdu autobusu
	char separator; ///< zmienna przechowuj�ca znak dwukropka, separator
	Rozklad_jazdy * nast; ///< wska�nik na nast�pny element
};

/** Elementy podwieszonej listy jednokierunkowej */
struct Nr_linii
{
	int numer_linii; ///< zmienna przechowuj�ca numery linii autobusowych 
	Rozklad_jazdy * pocz; ///< wska�nik na pierwszy element listy podwieszonej
	Nr_linii * nast; ///< wska�nik na nast�pny element
};

/** Elementy listy jednokierunkowej */
struct Przystanek
{
	string nazwa_przystanku; ///< zmienna przechowuj�ca nazwy przystank�w
	Przystanek * nast; ///< wska�nik na nast�pny element
	Nr_linii * pocz; ///< wska�nik na pierwszy element listy podwieszonej
};


/** Funkcja sprawdza czy u�ytkownik wpisa� poprawnie dane
@param argc liczba parametr�w wywo�ania funkcji main
@param argv tablica parametr�w przekazywana z wiersza polece�*/
int SprawdzWywolanie(int argc, char * argv[]);

/** Funkcja tworzy pliki testowe po wywo�aniu programu z prze��cznikiem -g
@param liczba_liniiint zmienna przechowuj�ca liczb� linii
@param liczba_kurs�wint zmienna przechowuj�ca liczb� kurs�w
@param liczba_przystank�wint zmienna przechowuj�ca liczb� przystank�w*/
void TworzeniePlikowTestowych(int liczba_liniiint, int liczba_kursowint, int liczba_przystankowint);

/** Funkcja wczytuje dane z plik�w wej�ciowych
@param glowa wska�nik na pierwszy element listy przystank�w
@param argc liczba parametr�w wywo�ania funkcji main
@param argv tablica parametr�w przekazywana z wiersza polece�*/
int WczytajDoStruktury(Przystanek * & glowa, int argc, char * argv[]);

/** Funkcja dodaje dane wczytame wcze�niej z plik�w wej�ciowych do listy
@param glowa wska�nik na pierwszy element listy przystank�w
@param nazwa_przystanku zmienna przechowuj�ca nazw� przystanku
@param numer_linii zmienna przechowuj�ca numer linii
@param GG zmienna przechowuj�ca godzin� odjazdu
@param MM zmienna przechowuj�ca minuty odjazdu
@param separator zmienna przechowuj�ca �rednik (separator)
*/
void DodajDoStruktury(Przystanek * & glowa, string nazwa_przystanku, int numer_linii, int GG, int MM, char separator);

/** Funkcja sortuje odjazdy na przystankach wed�ug godziny odjazdu
@param glowa wska�nik na pierwszy element listy przystank�w
*/
void SortujStrukture(Przystanek * glowa);

/** Funkcja tworzy pliki tekstowe z nazw� przystanku oraz wypisuje do nich posortowane odjazdy
@param glowa wska�nik na pierwszy element listy przystank�w
*/
void WypiszDoPlikow(Przystanek * glowa);

/** Funkcja kasuje struktur� danych przystank�w, numer�w linii, rozk�ad�w jazdy
@param glowa wska�nik na pierwszy element listy przystank�w
*/
void KasowanieStruktury(Przystanek * & glowa);

#endif