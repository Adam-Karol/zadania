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
	Surface();

	// Metoda zwaracaj¹ca oryginalny wskaŸnik.
	SDL_Surface* getPtr();

	void setPtr(SDL_Surface *ptr);


	// Destruktor.
	~Surface();
};
