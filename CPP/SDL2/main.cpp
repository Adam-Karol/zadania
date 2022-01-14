#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<time.h> // time()
#include <stdlib.h> // srand(), rand()

#include "drawing.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define STAGEVIEW_WIDTH 1000
#define STAGEVIEW_HEIGHT 1000


// main
#ifdef __cplusplus
extern "C"
#endif

struct player
{
	double x;
	double y;
	SDL_Surface* surface;
	double speed;
	double radius = 10;

	int hitPoints = 100;
};

struct enemy
{
	double x;
	double y;
	SDL_Surface* surface;
	//int speed;
};

struct vector
{
	double x;
	double y;
};

struct point
{
	double x;
	double y;
};

struct bullets
{
	int number = 0;
	point position[100];
	
	vector direction[100];

	SDL_Surface* surface;
	double speed = 50;
	double timer = 0; // time since last bullets was added
	double radius = 5;
};

int random(int a, int b) // a = -1; b = 2 
{
	return (rand() % (b-a)) + a;
}

void addBullet(enemy enemy1, bullets* bullets1)
{
	int x = enemy1.x;
	int y = enemy1.y;

	int number = bullets1->number;

	bullets1->position[number].x = x;
	bullets1->position[number].y = y;

	int vx;
	int vy;
	do
	{
		vx = random(-1, 2);
		vy = random(-1, 2);
	}
	while (vx == 0 && vy == 0);

	bullets1->direction[number].x = vx; 
	bullets1->direction[number].y = vy;

	bullets1->number++;

}

void moveBullets(bullets* bullets1, double t)
{
	for (int i = 0; i < bullets1->number; i++)
	{
		double oldx = bullets1->position[i].x;
		double oldy = bullets1->position[i].y;

		double s = bullets1->speed;

		//printf("przesuniecie: %lf %lf\n", bullets1->direction[i].x * t, bullets1->direction[i].y * t);
		bullets1->position[i].x = oldx + bullets1->direction[i].x * s * t;
		bullets1->position[i].y = oldy + bullets1->direction[i].y * s * t;
	}
}

void drawBulletsOnSurface(SDL_Surface* screen, bullets bullets1)
{

	for (int i = 0; i < bullets1.number; i++)
	{
		int x = bullets1.position[i].x;
		int y = bullets1.position[i].y;

		//printf("%i %i\n", x, y);

		DrawSurface(screen, bullets1.surface, x, y);
	}
}

void newGame()
{
	printf("New Game\n");
}

int main(int argc, char **argv)
{
	srand(time(0));





	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance;//, etiSpeed;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	//SDL_Surface *eti;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console" / Windows (/SUBSYSTEM:WINDOWS)
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy
	bool fullscreen = false;
	if (fullscreen)
		rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	else
		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	if(rc != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


	SDL_SetWindowTitle(window, "Bullet Hell Game");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_ShowCursor(SDL_ENABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	/*eti = SDL_LoadBMP("./eti.bmp");
	if(eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};*/
		
	SDL_Surface* stageview = SDL_LoadBMP("./stage_view.bmp");
	if(stageview == NULL) {
		printf("SDL_LoadBMP(stage_view.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		//SDL_FreeSurface(eti);
		SDL_Quit();
		return 1;
	};

	char text[128];
	const int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	const int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	const int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	printf("Time from sdl initialization: %i", t1);

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	//etiSpeed = 1;

	player player1;
	player1.x = STAGEVIEW_WIDTH / 2;
	player1.y = STAGEVIEW_HEIGHT / 2;
	player1.surface = SDL_LoadBMP("./player.bmp");
	player1.speed = 2000;
	player1.radius = 10;
	player1.hitPoints = 100;

	if(player1.surface == NULL)
	{
		printf("SDL_LoadBMP(player.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		//SDL_FreeSurface(eti);
		SDL_FreeSurface(stageview);
		SDL_Quit();
		return 1;
	};

	enemy enemy1;
	enemy1.surface = SDL_LoadBMP("./enemy1.bmp");
	enemy1.x = STAGEVIEW_WIDTH/2;
	enemy1.y = STAGEVIEW_HEIGHT / 3;

	if(enemy1.surface == NULL)
	{
		printf("SDL_LoadBMP(enemy1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(player1.surface);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		//SDL_FreeSurface(eti);
		SDL_FreeSurface(stageview);
		SDL_Quit();
		return 1;
	};

	bullets bullets1;
	bullets1.radius = 5;
	bullets1.surface = SDL_LoadBMP("./bullet1.bmp");
	if(bullets1.surface == NULL)
	{
		printf("SDL_LoadBMP(bullet1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(player1.surface);
		SDL_FreeSurface(enemy1.surface);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		//SDL_FreeSurface(eti);
		SDL_FreeSurface(stageview);
		SDL_Quit();
		return 1;
	};

	// linie naoko³o stageview
	DrawLine(stageview, 0, 0, 1000, 1, 0, niebieski);
	DrawLine(stageview, 0, 999, 1000, 1, 0, niebieski);
	DrawLine(stageview, 0, 0, 1000, 0, 1, niebieski);
	DrawLine(stageview, 999, 0, 1000, 0, 1, niebieski);

	SDL_Surface* stageviewToDraw = SDL_CreateRGBSurface(0, STAGEVIEW_WIDTH, STAGEVIEW_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	// main loop of the game
	while(!quit)
	{
		DrawSurface(stageviewToDraw, stageview, STAGEVIEW_WIDTH / 2, STAGEVIEW_HEIGHT / 2);
		
		// linie naoko³o stageviewToDraw
		DrawLine(stageviewToDraw, 1, 1, 1000, 1, 0, czerwony);
		DrawLine(stageviewToDraw, 1, 998, 1000, 1, 0, czerwony);
		DrawLine(stageviewToDraw, 1, 1, 1000, 0, 1, czerwony);
		DrawLine(stageviewToDraw, 998, 1, 1000, 0, 1, czerwony);


		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		//cout << "t1: " << t1 << " delta(sec): " << delta << endl;

		worldTime += delta;

		//distance += etiSpeed * delta;
		

		//SDL_FillRect(screen, NULL, czarny);

		/*DrawSurface(screen,
					eti,
					SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3,
					SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);*/

		fpsTimer += delta;
		if(fpsTimer > 0.5)
		{
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}


		// Drawing.

		DrawSurface(stageviewToDraw, enemy1.surface, enemy1.x, enemy1.y);

		moveBullets(&bullets1, delta);

		bullets1.timer += delta;
		if (bullets1.number < 50 && bullets1.timer >= 1.0)
		{
			addBullet(enemy1, &bullets1);

			bullets1.timer = 0;
		}

		drawBulletsOnSurface(stageviewToDraw, bullets1);

		DrawSurface(stageviewToDraw, player1.surface, player1.x, player1.y);
		
		// kopiowanie wybranego kawa³ka 
		SDL_Rect rectangle;
		rectangle.x = player1.x - (SCREEN_WIDTH / 2);
		rectangle.y = player1.y - (SCREEN_HEIGHT / 2);
		rectangle.w = SCREEN_WIDTH;
		rectangle.h = SCREEN_HEIGHT;
		SDL_BlitSurface(stageviewToDraw, &rectangle, screen, NULL);

		// Collisions.
		//collison(&player1, bullets1);



		
		// tekst informacyjny / info text
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf_s(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf_s(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);




		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while(SDL_PollEvent(&event))
		{
			
			switch(event.type)
			{
				case SDL_KEYDOWN:
					printf("x: %lf  y: %lf\n", player1.x, player1.y);
					//printf("delta: %lf\n", delta);

					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = 1;

					else if(event.key.keysym.sym == SDLK_n)
						newGame();

					else if(event.key.keysym.sym == SDLK_UP)
					{
						if (player1.y - player1.surface->h > 0)
							player1.y -= (player1.speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_DOWN)
					{
						if (player1.y + player1.surface->h < STAGEVIEW_HEIGHT)
							player1.y += (player1.speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_LEFT)
					{
						if (player1.x - player1.surface->w > 0)
							player1.x -= (player1.speed * delta);
					}
					else if(event.key.keysym.sym == SDLK_RIGHT)
					{
						if (player1.x + player1.surface->w < STAGEVIEW_WIDTH)
							player1.x += (player1.speed * delta);
					}


					break;

				/*case SDL_KEYUP:
					etiSpeed = 1.0;
					break;*/

				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
		
		frames++;
	} // while end


	// zwolnienie powierzchni / freeing all surfaces
	// zwolnienie pamiêci
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);

	//SDL_FreeSurface(eti);
	SDL_FreeSurface(stageview);
	SDL_FreeSurface(player1.surface);
	SDL_FreeSurface(enemy1.surface);

	SDL_FreeSurface(stageviewToDraw);

	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
