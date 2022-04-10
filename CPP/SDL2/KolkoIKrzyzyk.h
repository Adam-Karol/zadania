#pragma once

#include "stale.h"

// Deklaracje pól i metod klasy.

class KolkoIKrzyzyk
{
private:
	int plansza[3][3] = { {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE}, {PUSTE, PUSTE, PUSTE}};
	//int gracz = GRACZ1;
	bool gra_w_trakcie = true;
	int ile_rund = 0;
	bool ruch_x = false;

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
	bool czyX();
	void zmienGracza();
	void restart();

};
