#include "SDL.h"

#include "./window.c"
#include "./frame.c"
#include "./keyboard.c"
#include "./mouse.c"

#include "./fwi.c"
#include "./fac.c"
#include "./fvc.c"

void fcl_init() {
}

void fcl_event(SDL_Event event) {
	window_event(event);
	mouse_event(event);
}

void fcl_update() {
	keyboard_update();
	mouse_update();
	window_update();
}
