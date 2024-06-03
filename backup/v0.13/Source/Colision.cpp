#include <SDL.h>
#include "Colision.h"

int Collision(SDL_Rect rect, SDL_Rect rect2) {

	int width = rect.w;
	int height = rect.h;

	int width2 = rect2.w;
	int height2 = rect2.h;

	if (rect.x + width >= rect2.x &&
		rect.x - width2 <= rect2.x &&
		rect.y + height >= rect2.y &&
		rect.y - height2 <= rect2.y) {

		if (rect.y + height >= rect2.y &&
			rect.y + height - 10 <= rect2.y) {
			return 2;
		}

		if (rect.y - height2 <= rect2.y &&
			rect.y - (height2 - 10) >= rect2.y) {
			return 4;
		}

		if (rect.x - width2 <= rect2.x &&
			rect.x - (width2 - 10) >= rect2.x) {
			return 1;
		}
		
		if (rect.x + width >= rect2.x &&
			rect.x + width - 10 <= rect2.x) {
			return 3;
		}

	}
	return 0;
}

int SimpleCollision(SDL_Rect rect, SDL_Rect rect2) {

	int width = rect.w;
	int height = rect.h;

	int width2 = rect2.w;
	int height2 = rect2.h;

	if (rect.x + width >= rect2.x &&
		rect.x - width2 <= rect2.x &&
		rect.y + height >= rect2.y &&
		rect.y - height2 <= rect2.y) {	
		return 1;
	}
	return 0;
}