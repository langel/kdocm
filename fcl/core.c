#include "SDL.h"
SDL_Event event;

#include "./window.c"
#include "./frame.c"
#include "./keyboard.c"
#include "./mouse.c"

#include "./fac.c"
#include "./fvc.c"

void fcl_init() {
	keyboard_init();
	mouse_init();
	SDL_Init(SDL_INIT_EVERYTHING);
}

void fcl_event(SDL_Event event) {
	window_event(event);
	mouse_event(event);
}

void fcl_update() {
	keyboard_update();
	mouse_update();
	window_update();
	fvc_frame_next();
}

void fcl_shutdown() {
	SDL_Quit();
}
