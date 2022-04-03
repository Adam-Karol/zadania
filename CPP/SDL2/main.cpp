#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<time.h> // time()
#include <stdlib.h> // srand(), rand()
#include <exception>

#include "drawing.h"
#include "functions.h"
#include <iostream>

#include "stale.h"
#include "Surface.h"
#include "mechanikaGry.h"
#include "KolkoIKrzyzyk.h"

using namespace std;


#ifdef __cplusplus
extern "C"
#endif


int main(int argc, char **argv)
{
	KolkoIKrzyzyk kik;

	srand(time(0)); // seed rand

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console" / Windows (/SUBSYSTEM:WINDOWS)
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if( SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		cout << "SDL_Init error: \n" << SDL_GetError();
		return 1;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	int rc;
	bool fullscreen = false; // Tryb pe³noekranowy.
	if (fullscreen)
		rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	else
		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	if(rc != 0)
	{
		SDL_Quit();
		cout << "SDL_CreateWindowAndRenderer error: \n" << SDL_GetError();
		return 1;
	};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "Nasze okno");

	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_Texture *scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_ShowCursor(SDL_ENABLE);

	// wczytanie obrazka cs8x8.bmp
	Surface charset("./cs8x8.bmp");

	SDL_SetColorKey(charset.getPtr(), true, 0x000000);

	Surface plansza("./plansza.bmp");

	//Surface obrazek("./bullet.bmp");

	//Surface kursor("./kursor.bmp");
	Surface kursor("cursor.cur");

	//Surface prostokat("./prostokat.bmp");


	Surface kolo("./kolo.png");


	char text[128];
	const int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	const int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	const int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	int t1 = SDL_GetTicks();

	cout << "Time from sdl initialization: " << t1;

	int frames = 0;
	double fpsTimer = 0;
	double fps = 0;

	double worldTime = 0;

	double x = 50;
	double y = 50;
	double speed = 1000;

	//Surface gracz("./gracz.bmp");

	int mx = 0;
	int my = 0;
	bool czy_x = false;

	// main loop of the game
	bool quit = false;
	while(quit == false)
	{

		

		DrawSurface(screen, plansza.getPtr(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


		DrawLine(screen, SCREEN_WIDTH / 3, 0, SCREEN_HEIGHT, 0, 1, czarny);
		DrawLine(screen, SCREEN_WIDTH / 3 + 1, 0, SCREEN_HEIGHT, 0, 1, czarny);
		DrawLine(screen, SCREEN_WIDTH / 3 + 2, 0, SCREEN_HEIGHT, 0, 1, czarny);

		DrawLine(screen, 2 * (SCREEN_WIDTH / 3), 0, SCREEN_HEIGHT, 0, 1, czarny);
		DrawLine(screen, 2 * (SCREEN_WIDTH / 3) + 1, 0, SCREEN_HEIGHT, 0, 1, czarny);
		DrawLine(screen, 2 * (SCREEN_WIDTH / 3) + 2, 0, SCREEN_HEIGHT, 0, 1, czarny);

		DrawLine(screen, 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, 1, 0, czarny);
		DrawLine(screen, 0, SCREEN_HEIGHT / 3 + 1, SCREEN_WIDTH, 1, 0, czarny);
		DrawLine(screen, 0, SCREEN_HEIGHT / 3 + 2, SCREEN_WIDTH, 1, 0, czarny);

		DrawLine(screen, 0, 2 * (SCREEN_HEIGHT / 3), SCREEN_WIDTH, 1, 0, czarny);
		DrawLine(screen, 0, 2 * (SCREEN_HEIGHT / 3) + 1, SCREEN_WIDTH, 1, 0, czarny);
		DrawLine(screen, 0, 2 * (SCREEN_HEIGHT / 3) + 2, SCREEN_WIDTH, 1, 0, czarny);

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				//if ( x_i_o[i][j] == GRACZ1)
				if (kik.wartoscPola(i, j) == GRACZ1)
					postaw_o(j, i, plansza, kolo);
				else if (kik.wartoscPola(i, j) == GRACZ2)
					postaw_x(j, i, plansza);


		DrawSurface(screen, kursor.getPtr(), mx, my);


		/*DrawSurface(screen, prostokat, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);*/
		
		
		int t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		double delta = (t2 - t1) * 0.001;
		t1 = t2;
		//cout << "t1: " << t1 << " delta(sec): " << delta << endl;

		worldTime += delta;

		//SDL_FillRect(screen, NULL, czarny);

		fpsTimer += delta;

		if(fpsTimer > 0.5)
		{
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}

		// Drawing.

		//DrawSurface(screen, gracz.getPtr(), x, y);
	

		//// kopiowanie wybranego kawa³ka 
		//SDL_Rect rectangle;
		//rectangle.x = player1.x - (SCREEN_WIDTH / 2);
		//rectangle.y = player1.y - (SCREEN_HEIGHT / 2);
		//rectangle.w = SCREEN_WIDTH;
		//rectangle.h = SCREEN_HEIGHT;
		//SDL_BlitSurface(stageviewToDraw, &rectangle, screen, NULL);
		

		// tekst informacyjny / info text
		//DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		//sprintf_s(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		//DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		//sprintf_s(text, "Esc - wyjscie, Strzalki - sterowanie");
		//DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);


		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{

			mx = event.motion.x;
			my = event.motion.y;

			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button)
					{
					case SDL_BUTTON_LEFT:

						//if (czy_gra_trwa)
						if (kik.czyGraTrwa())
						{
							if (czy_x) // ruch x
							{
								//if (wstaw_do_tab(GRACZ2, x_i_o, mx, my))
								if (kik.wstawDoTab(GRACZ2, mx, my))
								{
									//if (sprawdz_wygrana(x_i_o, GRACZ2))
									if (kik.sprawdzWygrana(GRACZ2))
									{
										//czy_gra_trwa = false;
										kik.zakonczGre();
										DrawString(plansza.getPtr(), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Wygral gracz X", charset.getPtr());
									}

									kik.zwieksz_runde();
								}

								czy_x = false;
							}
							else // ruch o
							{
								if (kik.wstawDoTab(GRACZ1, mx, my))
								//if (wstaw_do_tab_si(GRACZ1, x_i_o))
								{
									if (kik.sprawdzWygrana(GRACZ1))
									{
										kik.zakonczGre();
										DrawString(plansza.getPtr(), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Wygral gracz O", charset.getPtr());
									}

									kik.zwieksz_runde();
								}

								czy_x = true;
							}

							
								
						}

						if (kik.czyGraTrwa() && kik.ktora_runda() == 9)
						{
								kik.zakonczGre();
								DrawString(plansza.getPtr(), SCREEN_WIDTH / 2 - 23, SCREEN_HEIGHT / 2, "REMIS", charset.getPtr());
						}

						break;


					}
					break;

				case SDL_KEYDOWN:
					/*cout << "x: " << x << " y: " << y << endl; */

					if(event.key.keysym.sym == SDLK_SPACE)
						quit = true;

					else if(event.key.keysym.sym == SDLK_UP)
					{
						//if (player1.y - player1.surface->h > 0)
							y -= (speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_DOWN)
					{
						//if (player1.y + player1.surface->h < STAGEVIEW_HEIGHT)
							y += (speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_LEFT)
					{
						//if (player1.x - player1.surface->w > 0)
							x -= (speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_RIGHT)
					{
						//if (player1.x + player1.surface->w < STAGEVIEW_WIDTH)
							x += (speed * delta);
					}


					break;

				case SDL_QUIT:
					quit = true;
					break;
			}
		}
		
		frames++;
	} // while end

	// zwolnienie powierzchni / freeing all surfaces
	// zwolnienie pamiêci

	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
