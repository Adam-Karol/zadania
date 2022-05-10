#pragma once

#include "SdlStruct.h"
#include <vector>
#include <string>
#include "stale.h"
#include "KolkoIKrzyzyk.h"
#include "mechanikaGry.h"

using namespace std;

void rysuj_plansze(SdlStruct &sdl, Surface &plansza);
void rysuj_o_i_x(SdlStruct& sdl, Surface& kolo, KolkoIKrzyzyk& kik);
void rysuj_napisy(vector<string>& napisy, SdlStruct& sdl);
void rysuj_kursor(SdlStruct& sdl, Surface& kursor);
void ruchGracza(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl, int gracz, double& czas);
void klikMyszka(SDL_Event& event, KolkoIKrzyzyk& kik, SdlStruct& sdl, vector<string>& napisy, double& czas);
void klawisz(SDL_Event& event, KolkoIKrzyzyk& kik, SdlStruct& sdl, bool& quit, vector<string>& napisy);
void obslugaZdarzen(SdlStruct& sdl, KolkoIKrzyzyk& kik, bool& quit, vector<string>& napisy, double& czas);
void sprRemis(KolkoIKrzyzyk& kik, vector<string>& napisy);
void mechanika_gry(KolkoIKrzyzyk& kik, vector<string>& napisy, SdlStruct& sdl, double& czas);
void glowaPetlaGry(SdlStruct& sdl, Surface& plansza, Surface& kursor, Surface& kolo, KolkoIKrzyzyk& kik, vector<string>& napisy);
