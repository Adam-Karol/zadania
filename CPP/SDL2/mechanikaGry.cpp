#include "mechanikaGry.h"
#include "stale.h"


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





