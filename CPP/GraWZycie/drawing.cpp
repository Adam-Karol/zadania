#include "drawing.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// Definicje (implementacje) funkcji.

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) 
{
	if (x >= 0 && y >= 0)
	{
		int bpp = surface->format->BytesPerPixel;
		Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
		*(Uint32*)p = color;
	}
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) 
{
	for(int i = 0; i < l; i++) 
	{
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};



// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);

	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};




void DrawCircle(SDL_Surface* screen, int a, int b, int r, Uint32 outlineColor, Uint32 fillColor)
{
	for (int x = -r; x <= r; x++)
	{
		int y = sqrt(r * r - x * x);
		int minus_y = -y;

		DrawPixel(screen, x + a, y + b, outlineColor);		
		DrawPixel(screen, x + a, minus_y + b, outlineColor);
		DrawLine(screen, x + a, minus_y + b, y - minus_y, 0, 1, fillColor);
	}
};



void DrawX(SDL_Surface* screen, int x, int y, int l, Uint32 Color)
{
	DrawLine(screen, x - l/2, y - l / 2, l, 1, 1, Color);
	DrawLine(screen, x - l / 2, y - l / 2 + 1, l, 1, 1, Color);
	DrawLine(screen, x - l / 2, y + l / 2, l, 1, -1, Color);
	DrawLine(screen, x + l / 2, y - l / 2 + 1, l, -1, 1, Color);
}



void DrawLineAB(SDL_Surface* screen, int ax, int ay, int bx, int by, Uint32 color)
{
	if (ax == bx)
	{
		if (ay > by)
		{
			int temp = ay;
			ay = by;
			by = temp;
			temp = ax;
			ax = bx; 
			bx = temp;
		}
		if (ay >= by)
			DrawLine(screen, ax, ay, ay - by, 0, 1, color);
		else
			DrawLine(screen, ax, ay, by - ay, 0, 1, color);
		return;
	}

	if (ax > bx)
	{
		int temp = ax; 
		ax = bx;
		bx = temp;
		temp = ay;
		ay = by;
		by = temp;
	}

	int a = ((ay - by) / (ax - bx));
	int b = ay - ((ax * ay) - (by * ax)) / (ax - bx);

	for (int x = ax; x <= bx; x++)
	{
		int y = a * x + b;
		cout << a << ' ' << b << endl;
		DrawPixel(screen, x, y, color);
		//cout << x << ' ' << y << endl;
	}
};

