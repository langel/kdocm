#include "SDL.h"
SDL_Event fcl_event;

#include "./window.c"
#include "./frame.c"
#include "./keyboard.c"
#include "./mouse.c"

#include "./fac.c"
#include "./fvc.c"

int fcl_running;

void fcl_init() {
	keyboard_init();
	mouse_init();
	SDL_Init(SDL_INIT_EVERYTHING);
	fcl_running = 1;
}


void fcl_update() {
	fvc_frame_next();
	while (SDL_PollEvent(&fcl_event)) {
		window_event(fcl_event);
		mouse_event(fcl_event);
		if (fcl_event.type == SDL_QUIT) fcl_running = 0;
	}
	keyboard_update();
	mouse_update();
	window_update();
}

void fcl_shutdown() {
	SDL_Quit();
}
