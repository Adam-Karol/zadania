#pragma once

#include <string>
#include "drawing.h"
#include "Surface.h"

struct SdlStruct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int rc;
	bool fullscreen = false; // Tryb pe³noekranowy.

	Surface screen;
	SDL_Texture *scrtex;

	Surface* charset;

	int t1; // czas 1
	int t2; // czas 2

	int frames = 0;
	double fpsTimer = 0;
	double fps = 0;
	double worldTime = 0;
	//double x = 50;
	//double y = 50;
	double speed = 1000;


	int mx = 0;
	int my = 0;


	int czarny;
	int zielony; 
	int czerwony; 
	int niebieski; 


	SdlStruct();
	void SdlStruct::uruchom();
	void utworzOknoIRenderer();
	void ustawUstawienia(std::string nazwaOkna);
	double delta();
	void ticks();
	void updateTextureAndRender();
	void wezPozycjeMyszki(SDL_Event& event);

	~SdlStruct();

	void nextFrame();
};
