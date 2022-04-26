#define _USE_MATH_DEFINES
#include <string.h>
#include <time.h> // time()
#include <stdlib.h> // srand(), rand()

#include "drawing.h"
#include <iostream>

#include "stale.h"
#include "Surface.h"
#include "mechanikaGry.h"
#include "KolkoIKrzyzyk.h"
#include "SdlStruct.h"
#include <vector>

using namespace std;

#ifdef __cplusplus
extern "C"
#endif

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
			if (kik.wartoscPola(i, j) == GRACZ1)
				rysuj_o(j, i, sdl.screen, kolo);
			else if (kik.wartoscPola(i, j) == GRACZ2)
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

void obslugaZdarzen(SdlStruct& sdl, KolkoIKrzyzyk& kik, bool quit, vector<string>& napisy)
{
	// obs�uga zdarze� (o ile jakie� zasz�y) / handling of events (if there were any)
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		sdl.wezPozycjeMyszki(event);

		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:

					if (kik.czyGraTrwa())
					{
						if (kik.czyX()) // ruch x
						{
							if (kik.wstawDoTab(GRACZ2, sdl.mx, sdl.my))
							{
								if (kik.sprawdzWygrana(GRACZ2))
								{
									kik.zakonczGre();
									//napisy.clear();
									napisy.push_back("Wygral gracz X");
								}

								kik.zwieksz_runde();
								kik.zmienGracza();

							}


						}

							
								
					}

					break;


				}
				break;

			case SDL_KEYDOWN:

				if(event.key.keysym.sym == SDLK_SPACE)
					quit = true;

					
				if (event.key.keysym.sym == SDLK_r)
				{
					kik.restart();
					SDL_FillRect(sdl.screen.getPtr(), NULL, sdl.czarny);
					napisy.clear();
				}


				break;

			case SDL_QUIT:
				quit = true;
				break;
		}
	}

}

void mechanika_gry(KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	if (kik.czyGraTrwa())
	{
		if (!kik.czyX()) // ruch o - robota
		{
			if (kik.wstawDoTabSI(GRACZ1))
			{
				if (kik.sprawdzWygrana(GRACZ1))
				{
					kik.zakonczGre();
					napisy.push_back("Wygral gracz O");
				}

				kik.zwieksz_runde();
				kik.zmienGracza();
			}

		}
	
		if (kik.ktora_runda() == 9)
		{
			kik.zakonczGre();
			napisy.push_back("REMIS");
		}
	}
}

void glowaPetlaGry(SdlStruct& sdl, Surface& plansza, Surface& kursor, Surface& kolo, KolkoIKrzyzyk& kik, vector<string>& napisy)
{
	bool quit = false;

	while(quit == false)
	{
		rysuj_plansze(sdl, plansza);

		rysuj_o_i_x(sdl, kolo, kik);

		rysuj_napisy(napisy, sdl);

		rysuj_kursor(sdl, kursor);

		sdl.ticks();

		sdl.updateTextureAndRender();

		obslugaZdarzen(sdl, kik, quit, napisy);
		
		mechanika_gry(kik, napisy);
		
		sdl.nextFrame();
	} // while end

}

int main(int argc, char **argv)
{
	KolkoIKrzyzyk kik; // Odpowiedzialne za logik� gry. Model.
	SdlStruct sdl; // Odpowiedzialne za rysowanie okna. Widok.
	sdl.uruchom();

	Surface plansza("./plansza.bmp");
	Surface kursor("cursor.cur");
	Surface kolo("./kolo.png");

	vector<string> napisy;
 
	glowaPetlaGry(sdl, plansza, kursor, kolo, kik, napisy);

	return 0;
}
