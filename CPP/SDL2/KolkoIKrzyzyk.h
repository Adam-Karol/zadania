#pragma once

#include "stale.h"
#include "Indeksy.h"

// Deklaracje pól i metod klasy.

class KolkoIKrzyzyk
{
private:
	int plansza[3][3] = { {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE}};
	bool gra_w_trakcie = true;
	int ile_rund = 0;
	bool ruch_o = true;

public:
	KolkoIKrzyzyk();
	int wartoscPola(int i, int j);
	bool czyGraTrwa();
	bool wstawDoTab(int gracz, int mx, int my);
	bool wstawDoTabSI(int gracz); // HW
	bool sprawdzWygrana(int gracz);
	void zakonczGre();
	void zwieksz_runde();
	int ktora_runda();
	bool czyO();
	void zmienGracza();
	void restart();
	Indeksy wybierz_indeksy();
	int wartosc_planszy(Indeksy wylosowane_indeksy);
	int wartosc_3pol(int wartosc1, int wartosc2, int wartosc3);
};
