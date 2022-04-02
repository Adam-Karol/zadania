#pragma once

#include <string>
#include "drawing.h"

using namespace std;

// Deklaracja klasy oraz p�l i metod w niej.

class Surface
{
private:
	// Pola.
	SDL_Surface *ptr;

public:
	// Konstruktor.
	Surface(string bmpfile);

	// Metoda zwaracaj�ca oryginalny wska�nik.
	SDL_Surface* getPtr();

	// Destruktor.
	~Surface();
};
