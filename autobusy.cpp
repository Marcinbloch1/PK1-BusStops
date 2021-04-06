#define _CRT_SECURE_NO_WARNINGS
#include "autobusy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int SprawdzWywolanie(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Podano zbyt mala ilosc parametrow! Podaj przelacznik -i lub -g" << endl;
		cout << "Podaj -g <liczba_linii> <liczba_kursow> <liczba_przystankow> lub -i <nazwa_pliku_z_linia.txt>" << endl;
		return 0;
	}
	string przelacznik = argv[1];
	if (przelacznik != "-i" && przelacznik != "-g")
	{
		cout << "Brak przelacznika." << endl << "Podaj -g <liczba_linii> <liczba_kursow> <liczba_przystankow> lub -i <nazwa_pliku_z_linia.txt>" << endl;
		system("pause");
		return 0;
	}
	else if (przelacznik == "-i")
	{
		if (argc < 3)
		{
			cout << "Podano zbyt mala ilosc parametrow! Podaj przelacznik -i lub -g" << endl;
			cout << "Podaj -g <liczba_linii> <liczba_kursow> <liczba_przystankow> lub -i <nazwa_pliku_z_linia.txt>" << endl;
			return 0;
		}
		else
			return 1;

	}
	else if (przelacznik == "-g")
	{
		if (argc != 5)
		{
			cout << "Podano zbyt mala lub zbyt duza ilosc parametrow!" << endl;
			cout << "Podaj -g <liczba_linii> <liczba_kursow> <liczba_przystankow> lub -i <nazwa_pliku_z_linia.txt>" << endl;
			return 0;
		}
		else
			return 2;

	}
}

void TworzeniePlikowTestowych(const int liczba_liniiint, int liczba_kursowint, int liczba_przystankowint)
{
	srand(time(NULL));
	for (int i = 1; i <= liczba_liniiint; i++)
	{
		int przystanek = 1;

		string tmp;
		sprintf((char*)tmp.c_str(), "%d", i);
		string str = tmp.c_str();
		string txt = ".txt";
		string plik = str + txt;
		ofstream zapis(plik);
		zapis << "Linia " + str << endl;
		for (int j = 0; j < liczba_kursowint; j++)
		{
			int godzina = (rand() % 24);
			int minuty = (rand() % 60);

			string tmpgodz;
			sprintf((char*)tmpgodz.c_str(), "%d", godzina);
			string strgodz = tmpgodz.c_str();
			if (godzina >= 0 && godzina <= 9)
			{
				strgodz = "0" + strgodz;
			}

			string tmpmin;
			sprintf((char*)tmpmin.c_str(), "%d", minuty);
			string strmin = tmpmin.c_str();
			if (minuty >= 0 && minuty <= 9)
			{
				strmin = "0" + strmin;
			}

			string kurs = strgodz + ":" + strmin;

			if (przystanek > liczba_przystankowint)
				przystanek = 1;

			string tmpprz;
			sprintf((char*)tmpprz.c_str(), "%d", przystanek);
			string strprz = tmpprz.c_str();

			zapis << kurs + " Przystanek" + strprz << endl;;
			przystanek++;
		}
		zapis.close();
	}
}

int WczytajDoStruktury(Przystanek * & glowa, int argc, char * argv[])
{
	string nazwa_przystanku;
	string linia;
	string pomoc_wczytania, p1, p2;
	int nr_linii_autobusowej = 0, godzina, minuta, licznik = 1, licznik2 = 1;
	char separator;
	bool pierwszy_wiersz, prawda;
	int nr_linii = 1;

	for (int j = 2; j < argc; j++)
	{
		ifstream plik(argv[j]);
		pierwszy_wiersz = true;
		licznik2 = 1;
		if (plik)
		{
			prawda = true;
			while (getline(plik, linia))
			{

				if (pierwszy_wiersz)
				{
					pomoc_wczytania = linia;
					pomoc_wczytania.erase(0, 6);
					for (int i = 0; i < linia.length(); i++)
						if ('0' > linia[i] > '9')
							prawda = false;
					if (prawda)
					{

						nr_linii_autobusowej = atoi(pomoc_wczytania.c_str());
						pierwszy_wiersz = false;
					}
				}

				if (prawda)
				{

					if ('0' <= linia[0] && linia[0] <= '9' && '0' <= linia[1] && linia[1] <= '9' &&
						linia[2] == ':' &&
						'0' <= linia[3] && linia[3] <= '9' && '0' <= linia[4] && linia[4] <= '9')
					{
						p1 = linia[0];
						p2 = linia[1];
						pomoc_wczytania = p1 + p2;
						godzina = atoi(pomoc_wczytania.c_str());
						separator = linia[2];
						p1 = linia[3];
						p2 = linia[4];
						pomoc_wczytania = p1 + p2;
						minuta = atoi(pomoc_wczytania.c_str());
						linia.erase(0, 6);
						nazwa_przystanku = linia;

						DodajDoStruktury(glowa, nazwa_przystanku, nr_linii_autobusowej, godzina, minuta, separator);
					}
				}
			}
			plik.close();
			licznik++;

			if (argc == licznik)
			{
				return 0;
			}
		}
		else
		{
			cout << "Plik < " << argv[j] << " > nie zostal odnaleziony!  " << endl;
			return 1;
		}
	}
}

void DodajDoStruktury(Przystanek * & glowa, string nazwa_przystanku, int numer_linii, int GG, int MM, char separator)
{
	Przystanek * p = glowa;
	Nr_linii * g;
	Rozklad_jazdy * w;
	while (p && p->nazwa_przystanku != nazwa_przystanku)
		p = p->nast;

	if (!p)
	{

		Przystanek * p = new Przystanek;
		p->nazwa_przystanku = nazwa_przystanku;
		p->nast = glowa;
		glowa = p;

		glowa->pocz = nullptr;

		Nr_linii * k = new Nr_linii;
		k->numer_linii = numer_linii;
		k->nast = glowa->pocz;
		glowa->pocz = k;

		glowa->pocz->pocz = nullptr;

		Rozklad_jazdy * m = new Rozklad_jazdy;
		m->GG = GG;
		m->separator = separator;
		m->MM = MM;

		m->nast = glowa->pocz->pocz;
		glowa->pocz->pocz = m;
	}
	else
	{
		g = p->pocz;

		while (g && g->numer_linii != numer_linii)
			g = g->nast;

		if (!g)
		{
			Nr_linii * z = new Nr_linii;
			z->numer_linii = numer_linii;
			z->nast = p->pocz;
			p->pocz = z;

			z->pocz = nullptr;

			Rozklad_jazdy * m = new Rozklad_jazdy;
			m->GG = GG;
			m->separator = separator;
			m->MM = MM;

			m->nast = z->pocz;
			z->pocz = m;


		}
		else
		{
			w = g->pocz;
			while (w && (w->GG != GG || w->MM != MM || w->separator != separator))
				w = w->nast;

			if (!w)
			{
				Rozklad_jazdy * m = new Rozklad_jazdy;

				m->GG = GG;
				m->separator = separator;
				m->MM = MM;

				m->nast = g->pocz;
				g->pocz = m;
			}
		}
	}
}

void SortujStrukture(Przystanek * glowa)
{
	Rozklad_jazdy * temp = nullptr;
	Rozklad_jazdy * help = nullptr;
	Nr_linii *pomoc;

	while (glowa)
	{
		pomoc = glowa->pocz;
		while (pomoc)
		{
			for (temp = pomoc->pocz; temp != nullptr; temp = temp->nast)
			{
				for (help = temp; help != nullptr; help = help->nast)
				{
					if (temp->GG == help->GG)
					{
						if (temp->MM > help->MM)
						{
							int GG = help->GG;
							help->GG = temp->GG;
							temp->GG = GG;
							int MM = help->MM;
							help->MM = temp->MM;
							temp->MM = MM;

						}
					}
					else if (temp->GG > help->GG)
					{
						int GG = help->GG;
						help->GG = temp->GG;
						temp->GG = GG;
						int MM = help->MM;
						help->MM = temp->MM;
						temp->MM = MM;
					}
				}
			}
			pomoc = pomoc->nast;
		}
		glowa = glowa->nast;
	}
}

void WypiszDoPlikow(Przystanek * glowa)
{

	fstream plik;
	string dlugosc;

	Nr_linii *pomoc;
	Rozklad_jazdy * pomoc2;
	bool licznik = true;
	bool licznik2 = true;

	while (glowa)
	{
		plik.open(glowa->nazwa_przystanku + ".txt", ios::out);
		pomoc = glowa->pocz;


		plik << glowa->nazwa_przystanku << endl;
		plik << "=====" << endl;


		while (pomoc)
		{
			plik << "LINIA : " << pomoc->numer_linii << endl;
			pomoc2 = pomoc->pocz;

			while (pomoc2)
			{

				if (pomoc2->GG >= 0 && pomoc2->GG <= 9)
				{
					int godz = pomoc2->GG;
					string tmpgodz;
					sprintf((char*)tmpgodz.c_str(), "%d", godz);
					string strgodz = tmpgodz.c_str();
					strgodz = "0" + strgodz;
					plik << strgodz;
				}
				else
				{
					plik << pomoc2->GG;
				}

				plik << pomoc2->separator;

				if (pomoc2->MM >= 0 && pomoc2->MM <= 9)
				{
					int min = pomoc2->MM;
					string tmpmin;
					sprintf((char*)tmpmin.c_str(), "%d", min);
					string strmin = tmpmin.c_str();
					strmin = "0" + strmin;
					plik << strmin;
				}
				else
				{
					plik << pomoc2->MM;
				}
				plik << ", ";
				pomoc2 = pomoc2->nast;
			}
			plik << endl;
			pomoc = pomoc->nast;
		}
		plik << endl;

		plik.close();
		glowa = glowa->nast;
	}
}

void KasowanieStruktury(Przystanek * & glowa)
{

	while (glowa)
	{
		Przystanek * nast = glowa->nast;
		while (glowa->pocz)
		{
			Nr_linii * nastepnik = glowa->pocz->nast;
			while (glowa->pocz->pocz)
			{
				Rozklad_jazdy * nastepniczek = glowa->pocz->pocz->nast;
				delete glowa->pocz->pocz;
				glowa->pocz->pocz = nastepniczek;
			}
			delete glowa->pocz;
			glowa->pocz = nastepnik;
		}
		delete glowa;
		glowa = nast;
	}
}

