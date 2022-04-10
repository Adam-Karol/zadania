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
Surface::Surface()
{
	ptr = NULL;
}

// Metoda zwaracaj¹ca oryginalny wskaŸnik.
SDL_Surface* Surface::getPtr()
{
	return ptr;
}

void Surface::setPtr(SDL_Surface *ptr)
{
	this->ptr = ptr;
}

// Destruktor.
Surface::~Surface()
{
	if (ptr != NULL)
	{
		SDL_FreeSurface(this->ptr);
	}
}
