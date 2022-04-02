#include "mechanikaGry.h"
#include "stale.h"

void postaw_x(int x, int y, Surface& plansza)
{
	int szerokosc_pola = SCREEN_WIDTH / 3;
	int wysokosc_pola = SCREEN_HEIGHT / 3;

	x = (x + 1) * (SCREEN_WIDTH / 3) - szerokosc_pola / 2;
	y = (y + 1) * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2;
	
	if (x < SCREEN_WIDTH / 3)
	{
		int x_poz = SCREEN_WIDTH / 3 - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawX(plansza.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else // lewy dolny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
	}
	else if (x < 2 * (SCREEN_WIDTH / 3))
	{
		int x_poz = 2 * (SCREEN_WIDTH / 3) - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawX(plansza.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else // lewy dolny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
	}
	else
	{
		int x_poz = SCREEN_WIDTH - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawX(plansza.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
		else // lewy dolny
		{
			DrawX(plansza.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
		}
	}
}



void postaw_o(int x, int y, Surface& plansza, Surface& kolo)
{
	int szerokosc_pola = SCREEN_WIDTH / 3;
	int wysokosc_pola = SCREEN_HEIGHT / 3;

	x = (x + 1) * (SCREEN_WIDTH / 3) - szerokosc_pola / 2;
	y = (y + 1) * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2;

	if (x < SCREEN_WIDTH / 3)
	{
		int x_poz = SCREEN_WIDTH / 3 - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2);
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2);
		}
		else // lewy dolny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2);
		}
	}
	else if (x < 2 * (SCREEN_WIDTH / 3))
	{
		int x_poz = 2 * (SCREEN_WIDTH / 3) - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2);
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2);
		}
		else // lewy dolny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2);
		}
	}
	else
	{
		int x_poz = SCREEN_WIDTH - szerokosc_pola / 2;
		if (y < SCREEN_HEIGHT / 3) // lewy gorny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT / 3 - wysokosc_pola / 2);
		}
		else if (y < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, 2 * (SCREEN_HEIGHT / 3) - wysokosc_pola / 2);
		}
		else // lewy dolny
		{
			DrawSurface(plansza.getPtr(), kolo.getPtr(), x_poz, SCREEN_HEIGHT - wysokosc_pola / 2);
		}
	}
}

Indeksy indeksy_pola(int mx, int my)
{
	int szerokosc_pola = SCREEN_WIDTH / 3;
	int wysokosc_pola = SCREEN_HEIGHT / 3;

	if (mx < SCREEN_WIDTH / 3)
	{
		int x_poz = SCREEN_WIDTH / 3 - szerokosc_pola / 2;
		if (my < SCREEN_HEIGHT / 3) // lewy gorny
		{
			return Indeksy(0, 0);
		}
		else if (my < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			return Indeksy(0, 1);
		}
		else // lewy dolny
		{
			return Indeksy(0, 2);
		}
	}
	else if (mx < 2 * (SCREEN_WIDTH / 3))
	{
		int x_poz = 2 * (SCREEN_WIDTH / 3) - szerokosc_pola / 2;
		if (my < SCREEN_HEIGHT / 3) // lewy gorny
		{
			return Indeksy(1, 0);
		}
		else if (my < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			return Indeksy(1, 1);
		}
		else // lewy dolny
		{
			return Indeksy(1, 2);
		}
	}
	else
	{
		int x_poz = SCREEN_WIDTH - szerokosc_pola / 2;
		if (my < SCREEN_HEIGHT / 3) // lewy gorny
		{
			return Indeksy(2, 0);
		}
		else if (my < 2 * (SCREEN_HEIGHT / 3)) // lewy srodkowy
		{
			return Indeksy(2, 1);
		}
		else // lewy dolny
		{
			return Indeksy(2, 2);
		}
	}
}


int sprawdz_wygrana(int plansza2[3][3], int gracz)
{
	if (plansza2[0][0] + plansza2[1][1] + plansza2[2][2] == 3 * gracz) return gracz;
	else if (plansza2[0][2] + plansza2[1][1] + plansza2[2][0] == 3 * gracz) return gracz;
	else if (plansza2[0][0] + plansza2[0][1] + plansza2[0][2] == 3 * gracz) return gracz;
	else if (plansza2[1][0] + plansza2[1][1] + plansza2[1][2] == 3 * gracz) return gracz;
	else if (plansza2[2][0] + plansza2[2][1] + plansza2[2][2] == 3 * gracz) return gracz;
	else if (plansza2[0][0] + plansza2[1][0] + plansza2[2][0] == 3 * gracz) return gracz;
	else if (plansza2[0][1] + plansza2[1][1] + plansza2[2][1] == 3 * gracz) return gracz;
	else if (plansza2[0][2] + plansza2[1][2] + plansza2[2][2] == 3 * gracz) return gracz;
	else return 0;
}


bool wstaw_do_tab(int gracz, int plansza2[3][3], int mx, int my)
{
	Indeksy ind = indeksy_pola(mx, my);

	if (plansza2[ind.j][ind.i] != PUSTE)
	{
		return false;
	}

	if (gracz == 1)
		plansza2[ind.j][ind.i] = GRACZ1;
	else
		plansza2[ind.j][ind.i] = GRACZ2;

	return true;
}