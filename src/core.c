#define SCREEN_W 420
#define SCREEN_H 200

int frame_counter;
SDL_Rect camera_rect = { 0, 0, 320, 200};

#include "./grafx.c"
#include "./cavern_gen.c"
#include "./map_handler.c"
#include "./map_grafx.c"
#include "./state_controller.c"

void core_init() {
	fcl_init();
	window_state_set_filename("kdocm");
	window_init("King Duck of Cluck Mountain");
	dpipe_init("src/map_grafx.c");
	fvc_init(SCREEN_W, SCREEN_H);
	grafx_init();
	map_grafx_init();
	state_controller_init();
	//printf("init\n");
}

void core_main() {
	frame_counter++;
	core_init();
	// XXX specific for dev pipeline
	SDL_MinimizeWindow(window);
	SDL_RestoreWindow(window);
//	SDL_RaiseWindow(window);
	window_focus();
	while (fcl_running) {
		SDL_SetRenderTarget(fvc_renderer, fvc_texture);
		state_controller_frame();
		frame_counter++;
		fcl_update();
		if (keys[SDL_SCANCODE_ESCAPE]) fcl_shutdown();
	}
	fcl_quit();
	return;
}
