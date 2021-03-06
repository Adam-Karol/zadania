#include "kontroler.h"
#include <iostream>


void rysuj_plansze(SdlStruct &sdl, Surface &plansza)
{
	DrawSurface(sdl.screen.getPtr(), plansza.getPtr(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	DrawLine(sdl.screen.getPtr(), SCREEN_WIDTH / 3, 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), SCREEN_WIDTH / 3 + 1, 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), SCREEN_WIDTH / 3 + 2, 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);

	DrawLine(sdl.screen.getPtr(), 2 * (SCREEN_WIDTH / 3), 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 2 * (SCREEN_WIDTH / 3) + 1, 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 2 * (SCREEN_WIDTH / 3) + 2, 0, SCREEN_HEIGHT, 0, 1, sdl.czarny);

	DrawLine(sdl.screen.getPtr(), 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, 1, 0, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 0, SCREEN_HEIGHT / 3 + 1, SCREEN_WIDTH, 1, 0, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 0, SCREEN_HEIGHT / 3 + 2, SCREEN_WIDTH, 1, 0, sdl.czarny);

	DrawLine(sdl.screen.getPtr(), 0, 2 * (SCREEN_HEIGHT / 3), SCREEN_WIDTH, 1, 0, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 0, 2 * (SCREEN_HEIGHT / 3) + 1, SCREEN_WIDTH, 1, 0, sdl.czarny);
	DrawLine(sdl.screen.getPtr(), 0, 2 * (SCREEN_HEIGHT / 3) + 2, SCREEN_WIDTH, 1, 0, sdl.czarny);
}

void rysuj_o_i_x(SdlStruct& sdl, Surface& kolo, KolkoIKrzyzyk& kik)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (kik.wartoscPola(i, j) == GRACZ_O)
				rysuj_o(j, i, sdl.screen, kolo);
			else if (kik.wartoscPola(i, j) == GRACZ_X)
				rysuj_x(j, i, sdl.screen);
}

void rysuj_napisy(vector<string>& napisy, SdlStruct& sdl)
{
	for (int i = 0; i < napisy.size(); i++)
		DrawString(sdl.screen.getPtr(), SCREEN_WIDTH / 2 - 23, SCREEN_HEIGHT / 2.5 + i*12, napisy[i].c_str(), sdl.charset->getPtr());
}

void rysuj_kursor(SdlStruct& sdl, Surface& kursor)
{
	DrawSurface(sdl.screen.getPtr(), kursor.getPtr(), sdl.mx, sdl.my);
}

void ruchGracza(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl, int gracz, double& czas)
{
	bool warunek = gracz == GRACZ_O;

	//cout << "gracz: " << gracz << endl;
	//cout << "warunek: " << warunek << endl;

	if (kik.czyGraTrwa())
	{
		if (kik.czyO() == warunek)
		{
			bool poprawnyRuch = false;
			if (warunek)
				poprawnyRuch = kik.wstawDoTab(gracz, sdl.mx, sdl.my);
			else
			{
				if (sdl.worldTime > czas + czas_oczekiwania)
					poprawnyRuch = kik.wstawDoTabSI(gracz);
			}
		
			if (poprawnyRuch)
			{
				if (warunek)
					czas = sdl.worldTime;

				if (kik.sprawdzWygrana(gracz))
				{
					kik.zakonczGre();

					napisy.push_back(warunek ? "Wygral gracz O" :  "Wygral gracz X");
				}

				kik.zwieksz_runde();
				kik.zmienGracza();
			}
		}
	}
}

void klikMyszka(SDL_Event& event, KolkoIKrzyzyk& kik, SdlStruct& sdl, vector<string>& napisy, double& czas)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		ruchGracza(kik, napisy, sdl, GRACZ_O, czas);
		break;
	}
}


void klawisz(SDL_Event& event, KolkoIKrzyzyk& kik, SdlStruct& sdl, bool& quit, vector<string>& napisy)
{
	if(event.key.keysym.sym == SDLK_SPACE)
		quit = true;

	if (event.key.keysym.sym == SDLK_r)
	{
		kik.restart();
		SDL_FillRect(sdl.screen.getPtr(), NULL, sdl.czarny);
		napisy.clear();
	}
}

void obslugaZdarzen(SdlStruct& sdl, KolkoIKrzyzyk& kik, bool& quit, vector<string>& napisy, double& czas)
{
	// obs?uga zdarze? (o ile jakie? zasz?y) / handling of events (if there were any)
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		sdl.wezPozycjeMyszki(event);

		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				klikMyszka(event, kik, sdl, napisy, czas);
				break;

			case SDL_KEYDOWN:
				klawisz(event, kik, sdl, quit, napisy);
				break;

			case SDL_QUIT: // Zamkni?cie okna. Klikni?cie X.
				quit = true;
				break;
		}
	}

}

void sprRemis(KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	// Musi by? sprawdzenie czy gra trwa.
	if (kik.czyGraTrwa() && kik.ktora_runda() == 9)
	{
		kik.zakonczGre();
		napisy.push_back("REMIS");
	}
}

void mechanika_gry(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl, double& czas)
{
	ruchGracza(kik, napisy, sdl, GRACZ_X, czas);

	sprRemis(kik, napisy);
}

void rysuj_pasek_oczekiwania(SdlStruct& sdl, double czas)
{
	if (sdl.worldTime - czas <= czas_oczekiwania && sdl.worldTime > 1)
		DrawRectangle(sdl.screen.getPtr(), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / (2 * czas_oczekiwania) * (sdl.worldTime - czas), 10, sdl.czarny, sdl.czarny);
}

void glowaPetlaGry(SdlStruct& sdl, Surface& plansza, Surface& kursor, Surface& kolo, KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	bool quit = false;

	//cout << endl << "czyX: " << kik.czyO() << endl;
	double czas = 0;
	while(quit == false)
	{
		rysuj_plansze(sdl, plansza);

		rysuj_o_i_x(sdl, kolo, kik);

		rysuj_pasek_oczekiwania(sdl, czas);

		rysuj_napisy(napisy, sdl);

		rysuj_kursor(sdl, kursor);

		sdl.ticks();

		sdl.updateTextureAndRender();

		//std::cout << sdl.worldTime << " " << sdl.worldTime - czas << " " << sdl.fps << " " << sdl.fpsTimer << " " << sdl.frames / sdl.worldTime << std::endl;


		obslugaZdarzen(sdl, kik, quit, napisy, czas);
		
		mechanika_gry(kik, napisy, sdl, czas);
		
		sdl.nextFrame();
	} // while end

}


void rysuj_x(int x, int y, Surface& plansza)
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



void rysuj_o(int x, int y, Surface& plansza, Surface& kolo)
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
