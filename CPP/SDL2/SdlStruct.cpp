#include "SdlStruct.h"
#include "drawing.h"
#include <iostream>
#include "stale.h"
#include "Surface.h"

SdlStruct::SdlStruct()
{
	// pass
}

void SdlStruct::utworzOknoIRenderer()
{
	if (fullscreen)
		rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	else
		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	if(rc != 0)
	{
		SDL_Quit();
		std::cout << "SDL_CreateWindowAndRenderer error: \n" << SDL_GetError();
		throw std::exception("SDL_CreateWindowAndRenderer error");
	};
}

void SdlStruct::ustawUstawienia(std::string nazwaOkna)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, nazwaOkna.c_str());

	this->screen.setPtr(SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
	this->scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_ShowCursor(SDL_ENABLE);

	// wczytanie obrazka cs8x8.bmp
	this->charset = new Surface("./cs8x8.bmp");

	SDL_SetColorKey(charset->getPtr(), true, 0x000000);
}

void SdlStruct::uruchom()
{
	if( SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cout << "SDL_Init error: \n" << SDL_GetError();
		throw std::exception("SDL_Init error");
	}

	this->utworzOknoIRenderer();
	this->ustawUstawienia("Kolko i krzyzyk");

	this->t1 = SDL_GetTicks();
	cout << "Time from sdl initialization: " << t1;

	this->czarny = SDL_MapRGB(screen.getPtr()->format, 0x00, 0x00, 0x00);
	this->zielony = SDL_MapRGB(screen.getPtr()->format, 0x00, 0xFF, 0x00);
	this->czerwony = SDL_MapRGB(screen.getPtr()->format, 0xFF, 0x00, 0x00);
	this->niebieski = SDL_MapRGB(screen.getPtr()->format, 0x11, 0x11, 0xCC);
}

// w tym momencie t2-t1 to czas w milisekundach,
// jaki uplyna³ od ostatniego narysowania ekranu
// delta to ten sam czas w sekundach
double SdlStruct::delta() // delta - zmianê wartoœci 
{
	return (this->t2 - this->t1) * 0.001;
}

void SdlStruct::ticks()
{
	this->t2 = SDL_GetTicks();

	this->worldTime += this->delta();

	this->t1 = this->t2;

	this->fpsTimer += this->delta();

	if (this->fpsTimer > 0.5)
	{
		this->fps = this->frames * 2;
		this->frames = 0;
		this->fpsTimer -= 0.5;
	}
}

void SdlStruct::updateTextureAndRender()
{
	SDL_UpdateTexture(scrtex, NULL, screen.getPtr()->pixels, screen.getPtr()->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void SdlStruct::wezPozycjeMyszki(SDL_Event& event)
{
	this->mx = event.motion.x;
	this->my = event.motion.y;
}

SdlStruct::~SdlStruct()
{
	if (this->charset)
		delete this->charset;

	// zwolnienie powierzchni / freeing all surfaces
	// zwolnienie pamiêci
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void SdlStruct::nextFrame()
{
	this->frames++;
}