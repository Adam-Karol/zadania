#include "KolkoIKrzyzyk.h"
#include "Indeksy.h"
#include "mechanikaGry.h"
#include "functions.h"
#include <iostream>
#include <vector>


using namespace std;

KolkoIKrzyzyk::KolkoIKrzyzyk()
{
	srand(time(0)); // seed rand - ziarno losowania
}

int KolkoIKrzyzyk::wartoscPola(int i, int j)
{
	return this->plansza[i][j];
}

bool KolkoIKrzyzyk::czyGraTrwa()
{
	return this->gra_w_trakcie;
}

bool KolkoIKrzyzyk::wstawDoTab(int gracz, int mx, int my)
{
	Indeksy ind = indeksy_pola(mx, my);

	if (this->plansza[ind.j][ind.i] != PUSTE)
		return false;

	if (gracz == GRACZ_O)
		this->plansza[ind.j][ind.i] = GRACZ_O;
	else
		this->plansza[ind.j][ind.i] = GRACZ_X;

	return true;
}

int KolkoIKrzyzyk::wartosc_3pol(int wartosc1, int wartosc2, int wartosc3)
{
	//cout << wartosc1 << " " << wartosc2 << " " << wartosc3 << endl;

	const int puste3 = 0;
	const int zajete3 = 0;
	const int przeciwnik2 = -100;
	const int przeciwnik1 = -5;
	const int nasze3 = 100000000;
	const int nasze2 = 50;
	const int nasze1 = 5;
	const int nasze1_przeciwnik1 = 1;
	const int nasze1_przeciwnik2 = 10000;

	int wynik = 0;

	if (wartosc1 + wartosc2 + wartosc3 == 2 * GRACZ_O)
	{
		wynik += przeciwnik2;
	}
	if (wartosc1 + wartosc2 + wartosc3 == 3 * GRACZ_X)
	{
		wynik += nasze3;
	}
	if (wartosc1 + wartosc2 + wartosc3 == 2 * GRACZ_X)
	{
		wynik += nasze2;
	}
	if (wartosc1 + wartosc2 + wartosc3 == GRACZ_X)
	{
		wynik += nasze1;
	}
	if (wartosc1 + wartosc2 + wartosc3 == GRACZ_O)
	{
		wynik += przeciwnik1;
	}
	if (wartosc1 + wartosc2 + wartosc3 == GRACZ_O + GRACZ_X)
	{
		wynik += nasze1_przeciwnik1;
	}
	if (wartosc1 + wartosc2 + wartosc3 == 2 * GRACZ_O + GRACZ_X)
	{
		wynik += nasze1_przeciwnik2;
	}

	return wynik;
}

int KolkoIKrzyzyk::wartosc_planszy(Indeksy wylosowane_indeksy)
{
	int kopia[3][3] = { {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE} };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kopia[j][i] = plansza[j][i];

	if (kopia[wylosowane_indeksy.j][wylosowane_indeksy.i] != PUSTE)
		return -9999999;

	kopia[wylosowane_indeksy.j][wylosowane_indeksy.i] = GRACZ_X;

	//cout << kopia << endl;

	int wynik = 0;

	wynik += wartosc_3pol(kopia[0][0], kopia[1][1], kopia[2][2]);
	wynik += wartosc_3pol(kopia[0][2], kopia[1][1], kopia[2][0]);
	wynik += wartosc_3pol(kopia[0][0], kopia[0][1], kopia[0][2]);
	wynik += wartosc_3pol(kopia[1][0], kopia[1][1], kopia[1][2]);
	wynik += wartosc_3pol(kopia[2][0], kopia[2][1], kopia[2][2]);
	wynik += wartosc_3pol(kopia[0][0], kopia[1][0], kopia[2][0]);
	wynik += wartosc_3pol(kopia[0][1], kopia[1][1], kopia[2][1]);
	wynik += wartosc_3pol(kopia[0][2], kopia[1][2], kopia[2][2]);

	return wynik;
}

Indeksy losuj_indeksy()
{
	Indeksy wylosowane(random(0, 3), random(0, 3));

	/*cout << wylosowane.i << " " << wylosowane.j << endl;*/
	return wylosowane;
}

int znajdz_index_max(vector<int>& lista) 
{
	int max = lista[0];
	int max_index = 0;

	for (int i = 1; i < lista.size(); i++)
	{
		if (lista[i] > max)
		{
			max = lista[i];
			max_index = i;
		}
	}

	return max_index;
}


bool czy_zawiera(vector<Indeksy>& mozliwosci, Indeksy mozliwosc)
{
	for (int i = 0; i < mozliwosci.size(); i++)
	{
		if (mozliwosci[i].i == mozliwosc.i && mozliwosci[i].j == mozliwosc.j)
		{
			return true;
		}
	}
	return false;
}


Indeksy KolkoIKrzyzyk::wybierz_indeksy()
{
	vector<Indeksy> mozliwosci;
	vector<int> wartosci;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mozliwosci.push_back(Indeksy(i, j));
			wartosci.push_back(wartosc_planszy(mozliwosci[mozliwosci.size() - 1]));
		}
	}

	return mozliwosci[znajdz_index_max(wartosci)];
}


// Z programem mo¿na wygraæ graj¹c tak:
// Stawimy kó³ko w 2 naprzeciwleg³e rogi
// Dok³adamy kó³ko w 3 (obojêtnie który) róg
// Stawiamy kó³ko pomiêdzy rogami

bool KolkoIKrzyzyk::wstawDoTabSI(int gracz)
{
	cout << "ZACZALEM" << endl;
	Indeksy ind = wybierz_indeksy();

	if (this->plansza[ind.j][ind.i] != PUSTE)
		return false;

	if (gracz == GRACZ_O)
		this->plansza[ind.j][ind.i] = GRACZ_O;
	else
		this->plansza[ind.j][ind.i] = GRACZ_X;

	cout << "GOTOWE" << endl;
	return true;
}

bool KolkoIKrzyzyk::sprawdzWygrana(int gracz)
{
	if (plansza[0][0] + plansza[1][1] + plansza[2][2] == 3 * gracz) return true;
	else if (plansza[0][2] + plansza[1][1] + plansza[2][0] == 3 * gracz) return true;
	else if (plansza[0][0] + plansza[0][1] + plansza[0][2] == 3 * gracz) return true;
	else if (plansza[1][0] + plansza[1][1] + plansza[1][2] == 3 * gracz) return true;
	else if (plansza[2][0] + plansza[2][1] + plansza[2][2] == 3 * gracz) return true;
	else if (plansza[0][0] + plansza[1][0] + plansza[2][0] == 3 * gracz) return true;
	else if (plansza[0][1] + plansza[1][1] + plansza[2][1] == 3 * gracz) return true;
	else if (plansza[0][2] + plansza[1][2] + plansza[2][2] == 3 * gracz) return true;
	else return false;
}

void KolkoIKrzyzyk::zakonczGre()
{
	this->gra_w_trakcie = false;
}


void KolkoIKrzyzyk::zwieksz_runde()
{
	this->ile_rund++;
}


int KolkoIKrzyzyk::ktora_runda()
{
	return this->ile_rund;
}

bool KolkoIKrzyzyk::czyO()
{
	return ruch_o;
}

void KolkoIKrzyzyk::zmienGracza()
{
	this->ruch_o = ! this->ruch_o;
}


void KolkoIKrzyzyk::restart()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			plansza[i][j] = PUSTE;
		}
	}
	//gracz = GRACZ_O;
	gra_w_trakcie = true;
	ile_rund = 0;
	ruch_o = true;

}