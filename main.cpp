#define _CRT_SECURE_NO_WARNINGS
#include "autobusy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "vld.h"



int main(int argc, char * argv[])
{
	//funkcja sprawdza czy dane s¹ wprowadzone poprawnie

	int check = SprawdzWywolanie(argc, argv);
	if (check == 0)
	{
		return 0;
	}

	else if (check == 1)
	{
		Przystanek * glowa = nullptr; // wskaznik zerowy
		WczytajDoStruktury(glowa, argc, argv); // funkcja wczytuje dane do programu 
		SortujStrukture(glowa); //funkcja sortuje godziny odjazdow
		WypiszDoPlikow(glowa); // funkcja wypisuje do plików rozk³ady 
		KasowanieStruktury(glowa); // funkcja kasuje pamiêæ alokowan¹ dynamicznie
	}

	else if (check == 2)
	{
		string liczba_linii = argv[2];
		string liczba_kursow = argv[3];
		string liczba_przystankow = argv[4];
		const int liczba_liniiint = atoi(liczba_linii.c_str());
		int liczba_kursowint = atoi(liczba_kursow.c_str());
		int liczba_przystankowint = atoi(liczba_przystankow.c_str());
		TworzeniePlikowTestowych(liczba_liniiint, liczba_kursowint, liczba_przystankowint);
	}

	return 0;
}