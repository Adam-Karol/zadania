#include "KolkoIKrzyzyk.h"
#include "Indeksy.h"
#include "mechanikaGry.h"
#include "functions.h"
#include <iostream>


using namespace std;

KolkoIKrzyzyk::KolkoIKrzyzyk()
{

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

	if (gracz == 1)
		this->plansza[ind.j][ind.i] = GRACZ1;
	else
		this->plansza[ind.j][ind.i] = GRACZ2;

	return true;
}

Indeksy losuj_indeksy()
{
	Indeksy wylosowane(random(0, 3), random(0, 3));

	cout << wylosowane.i << " " << wylosowane.j << endl;
	return wylosowane;
}

bool KolkoIKrzyzyk::wstawDoTabSI(int gracz)
{
	Indeksy ind = losuj_indeksy();

	if (this->plansza[ind.j][ind.i] != PUSTE)
		return false;

	if (gracz == 1)
		this->plansza[ind.j][ind.i] = GRACZ1;
	else
		this->plansza[ind.j][ind.i] = GRACZ2;

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

bool KolkoIKrzyzyk::czyX()
{
	return ruch_x;
}

void KolkoIKrzyzyk::zmienGracza()
{
	this->ruch_x = ! this->ruch_x;
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
	//gracz = GRACZ1;
	gra_w_trakcie = true;
	ile_rund = 0;
	ruch_x = false;

}