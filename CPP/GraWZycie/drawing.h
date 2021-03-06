#pragma once

extern "C" {
#include "./SDL2_h/SDL.h"
#include "./SDL2_h/SDL_main.h"
#include "./SDL2_h/SDL_image.h"

}

// Deklaracje funkcji.

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawLine2(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawLineAB(SDL_Surface* screen, int ax, int ay, int bx, int by, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void DrawCircle(SDL_Surface* screen, int x, int y, int r, Uint32 outlineColor, Uint32 fillColor);

void DrawX(SDL_Surface* screen, int x, int y, int l, Uint32 Color);
