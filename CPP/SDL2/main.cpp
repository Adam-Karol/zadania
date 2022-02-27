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

using namespace std;

#define SCREEN_WIDTH 540
#define SCREEN_HEIGHT 480

#ifdef __cplusplus
extern "C"
#endif

class Surface
{
private:
	SDL_Surface *ptr;

public:
	// Konstruktor.
	Surface(string bmpfile)
	{
		ptr = IMG_Load(bmpfile.c_str());
		if(ptr == NULL)
			throw exception("IMG_Load failed.");
	}

	// Metoda zwaracaj¹ca oryginalny wskaŸnik.
	SDL_Surface* getPtr()
	{
		return ptr;
	}

	// Destruktor.
	~Surface()
	{
		SDL_FreeSurface(ptr);
	}
};



void postaw_x(int x, int y, Surface plansza)
{
	if (x < 180 && y < 160)
	{
		DrawX(plansza.getPtr(), 90, 80, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (x < 180 && 160 < y < 320)
	{
		DrawX(plansza.getPtr(), 90, 240, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (x < 180 && 320 < y)
	{
		DrawX(plansza.getPtr(), 90, 400, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (180 < x < 360 && y < 160)
	{
		DrawX(plansza.getPtr(), 270, 80, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (360 < x && y < 160)
	{
		DrawX(plansza.getPtr(), 450, 80, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (180 < x < 360 && 160 < y < 320)
	{
		DrawX(plansza.getPtr(), 270, 240, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (360 < x && 160 < y < 320)
	{
		DrawX(plansza.getPtr(), 450, 240, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (360 < x && 320 < y)
	{
		DrawX(plansza.getPtr(), 450, 400, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
	if (180 < x < 360 && 320 < y)
	{
		DrawX(plansza.getPtr(), 270, 400, 100, SDL_MapRGB(plansza.getPtr()->format, 0x00, 0x00, 0x00));
	}
}



int main(int argc, char **argv)
{
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

	Surface obrazek("./bullet.bmp");

	//Surface kursor("./kursor.bmp");
	Surface kursor("cursor.cur");

	Surface prostokat("./prostokat.bmp");


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

	Surface gracz("./gracz.bmp");

	// Rysowanie.
	//DrawLine(gracz.getPtr(), 0, 9, 20, 1, 0, czerwony);
	//DrawLine(gracz.getPtr(), 0, 10, 20, 1, 0, czerwony);
	//DrawLine(gracz.getPtr(), 9, 0, 20, 0, 1, czerwony);
	//DrawLine(gracz.getPtr(), 10, 0, 20, 0, 1, czerwony);


	//DrawLine(plansza.getPtr(), 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, 1, 0, zielony);
	//DrawLine(plansza.getPtr(), SCREEN_WIDTH / 2, 0, SCREEN_HEIGHT, 0, 1, zielony);


	//DrawString(plansza.getPtr(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Hello!", charset.getPtr());
	//DrawPixel(plansza.getPtr(), random(SCREEN_WIDTH/3, 2*SCREEN_WIDTH/3), random(SCREEN_HEIGHT/3, 2*SCREEN_HEIGHT/3), zielony);
	//DrawRectangle(plansza.getPtr(), random(SCREEN_WIDTH/3, 2*SCREEN_WIDTH/3), random(SCREEN_HEIGHT/3, 2*SCREEN_HEIGHT/3),
	//		random(10, 50), random(10, 50), zielony, zielony);
	//DrawSurface(plansza.getPtr(), obrazek.getPtr(), 100, 100);

	//DrawCircle(plansza.getPtr(), 0, 0, 50, zielony, niebieski);
	//DrawCircle(plansza.getPtr(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, zielony, niebieski);
	//DrawCircle(plansza.getPtr(), SCREEN_WIDTH, SCREEN_HEIGHT / 2, 50, zielony, niebieski);
	//DrawCircle(plansza.getPtr(), 100, SCREEN_HEIGHT, 10, zielony, niebieski);

	//DrawX(plansza.getPtr(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, czerwony);

	//DrawLineAB(plansza, 100, 100, 200, 200, zielony);
	//DrawLineAB(plansza, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 400, 500, zielony);
	//DrawLineAB(plansza, 20, 20, 200, 500, zielony);
	//DrawLineAB(plansza, 500, 300, 100, 400, niebieski);
	//DrawLineAB(plansza.getPtr(), 100, 100, 100, 400, zielony);
	//DrawLineAB(plansza.getPtr(), 200, 450, 200, 0, niebieski);

	int mx = 0;
	int my = 0;
	bool czy = false;

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
							if (czy)
							{
								postaw_x(mx, my, plansza);
								czy = false;
							}
							else
							{
								DrawSurface(plansza.getPtr(), kolo.getPtr(), mx, my);
								czy = true;
							}


							cout << "mx: " << mx << " ";
							cout << "my: " << my << endl;

							

							break;
					}

					break;

					//if (event.button.button = SDL_BUTTON_LEFT)
					//{
					//	cout << "mx: " << mx << " ";
					//	cout << "my: " << my << endl;
					//}

				case SDL_KEYDOWN:
					/*cout << "x: " << x << " y: " << y << endl; */

					if(event.key.keysym.sym == SDLK_ESCAPE)
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
