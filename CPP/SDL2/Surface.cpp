#include <exception>
#include "drawing.h"
#include "Surface.h"

using namespace std;

// Definicje (implementacje) metod klasy.

// Konstruktor.
Surface::Surface(string bmpfile)
{
	ptr = IMG_Load(bmpfile.c_str());
	if(ptr == NULL)
		throw exception("IMG_Load failed.");
}

// Metoda zwaracaj¹ca oryginalny wskaŸnik.
SDL_Surface* Surface::getPtr()
{
	return ptr;
}

// Destruktor.
Surface::~Surface()
{
	SDL_FreeSurface(this->ptr);
}
