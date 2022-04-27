#include "kontroler.h"


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

void ruchGracza(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl, int gracz)
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
				poprawnyRuch = kik.wstawDoTabSI(gracz);

			if (poprawnyRuch)
			{
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

void klikMyszka(SDL_Event& event, KolkoIKrzyzyk& kik, SdlStruct& sdl, vector<string>& napisy)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		ruchGracza(kik, napisy, sdl, GRACZ_O);
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

void obslugaZdarzen(SdlStruct& sdl, KolkoIKrzyzyk& kik, bool& quit, vector<string>& napisy)
{
	// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		sdl.wezPozycjeMyszki(event);

		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				klikMyszka(event, kik, sdl, napisy);
				break;

			case SDL_KEYDOWN:
				klawisz(event, kik, sdl, quit, napisy);
				break;

			case SDL_QUIT: // Zamkniêcie okna. Klikniêcie X.
				quit = true;
				break;
		}
	}

}



void sprRemis(KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	// Musi byæ sprawdzenie czy gra trwa.
	if (kik.czyGraTrwa() && kik.ktora_runda() == 9)
	{
		kik.zakonczGre();
		napisy.push_back("REMIS");
	}
}

void mechanika_gry(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl)
{
	//ruchO(kik, napisy);
	ruchGracza(kik, napisy, sdl, GRACZ_X);

	sprRemis(kik, napisy);

}

void glowaPetlaGry(SdlStruct& sdl, Surface& plansza, Surface& kursor, Surface& kolo, KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	bool quit = false;

	//cout << endl << "czyX: " << kik.czyO() << endl;

	while(quit == false)
	{
		rysuj_plansze(sdl, plansza);

		rysuj_o_i_x(sdl, kolo, kik);

		rysuj_napisy(napisy, sdl);

		rysuj_kursor(sdl, kursor);

		sdl.ticks();

		sdl.updateTextureAndRender();

		obslugaZdarzen(sdl, kik, quit, napisy);
		
		mechanika_gry(kik, napisy, sdl);
		
		sdl.nextFrame();
	} // while end

}
