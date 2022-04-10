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

int main(int argc, char **argv)
{
	KolkoIKrzyzyk kik;

	srand(time(0)); // seed rand

	SdlStruct sdl;
	sdl.uruchom();

	Surface plansza("./plansza.bmp");
	Surface kursor("cursor.cur");
	Surface kolo("./kolo.png");

	rysuj_plansze(sdl, plansza);

	// main loop of the game
	bool quit = false;
	while(quit == false)
	{		
		

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (kik.wartoscPola(i, j) == GRACZ1)
					postaw_o(j, i, sdl.screen, kolo);
				else if (kik.wartoscPola(i, j) == GRACZ2)
					postaw_x(j, i, sdl.screen);


		DrawSurface(sdl.screen.getPtr(), kursor.getPtr(), sdl.mx, sdl.my);

		sdl.ticks();
		sdl.updateTextureAndRender();

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

						//if (czy_gra_trwa)
						if (kik.czyGraTrwa())
						{
							if (kik.czyX()) // ruch x
							{
								//if (wstaw_do_tab(GRACZ2, x_i_o, mx, my))
								if (kik.wstawDoTab(GRACZ2, sdl.mx, sdl.my))
								{
									//if (sprawdz_wygrana(x_i_o, GRACZ2))
									if (kik.sprawdzWygrana(GRACZ2))
									{
										//czy_gra_trwa = false;
										kik.zakonczGre();
										DrawString(sdl.screen.getPtr(), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Wygral gracz X", sdl.charset->getPtr());
									}

									kik.zwieksz_runde();
									kik.zmienGracza();

								}


							}

							
								
						}

						if (kik.czyGraTrwa() && kik.ktora_runda() == 9)
						{
								kik.zakonczGre();
								DrawString(sdl.screen.getPtr(), SCREEN_WIDTH / 2 - 23, SCREEN_HEIGHT / 2, "REMIS", sdl.charset->getPtr());
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
					}


					break;

				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		if (kik.czyGraTrwa())
		{
			if (!kik.czyX()) // ruch o
			{
				//if (kik.wstawDoTab(GRACZ1, sdl.mx, sdl.my))
				if (kik.wstawDoTabSI(GRACZ1))
				{
					if (kik.sprawdzWygrana(GRACZ1))
					{
						kik.zakonczGre();
						DrawString(sdl.screen.getPtr(), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Wygral gracz O", sdl.charset->getPtr());
					}

					kik.zwieksz_runde();
					kik.zmienGracza();
				}


			}
		}

		
		sdl.nextFrame();
	} // while end


	return 0;
}
