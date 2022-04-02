#pragma once

#include "Indeksy.h"
#include "Surface.h"

void postaw_x(int x, int y, Surface& plansza);
void postaw_o(int x, int y, Surface& plansza, Surface& kolo);
Indeksy indeksy_pola(int mx, int my);
int sprawdz_wygrana(int plansza2[3][3], int gracz);
bool wstaw_do_tab(int gracz, int plansza2[3][3], int mx, int my);
