#define _USE_MATH_DEFINES
#include <string.h>
#include "Surface.h"
#include "KolkoIKrzyzyk.h"
#include "SdlStruct.h"
#include <vector>
#include "kontroler.h"

using namespace std;

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv)
{
	KolkoIKrzyzyk kik; // Odpowiedzialne za logikê gry. Model.
	SdlStruct sdl; // Odpowiedzialne za rysowanie okna. Widok.
	sdl.uruchom();

	Surface plansza("./plansza.bmp");
	Surface kursor("cursor.cur");
	Surface kolo("./kolo.png");

	vector<string> napisy;
 
	glowaPetlaGry(sdl, plansza, kursor, kolo, kik, napisy);

	return 0;
}
