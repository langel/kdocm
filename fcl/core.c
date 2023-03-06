#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "./util/types.c"
#include "./util/strng.c"
#include "./util/curve.c"
#include "./util/lerps.c"
#include "./util/rngxp.c"
#include "./util/mouse.c"
#include "./util/frame.c"
#include "./util/debug.c"
#include "./fwi.c"
#include "./fac.c"
#include "./fvc.c"
#include "./util/dpipe.c"


int collision_detection(SDL_Rect a, SDL_Rect b) {
	if (a.x + a.w < b.x) return 0;
	if (a.x > b.x + b.w) return 0;
	if (a.y + a.h < b.y) return 0;
	if (a.y > b.y + b.h) return 0;
	return 1;
}
