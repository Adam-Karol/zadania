#pragma once

#include <string>
#include "drawing.h"

using namespace std;

// Deklaracja klasy oraz pól i metod w niej.

class Surface
{
private:
	// Pola.
	SDL_Surface *ptr;

public:
	// Konstruktor.
	Surface(string bmpfile);

	// Metoda zwaracaj¹ca oryginalny wskaŸnik.
	SDL_Surface* getPtr();

	// Destruktor.
	~Surface();
};
