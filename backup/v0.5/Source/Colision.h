#pragma once
//Wymaga sdl2 do dzia³ania
// Funcja do wykrywania kolizji obiektów 2d w œrodkowisku sdl
//Zwarca od 1 do 4 w przypadku wykrycia kolizji a 0 w przypadku jej braku
//    2
//1       3
//    4
int Collision(SDL_Rect rect, SDL_Rect rect2);