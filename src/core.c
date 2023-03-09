#define SCREEN_W 420
#define SCREEN_H 200

#include "./grafx.c"
#include "./map_handler.c"
#include "./state_controller.c"

void core_init() {
	fcl_init();
	window_state_set_filename("kdocm");
	window_init("King Duck of Cluck Mountain");
	fvc_init(SCREEN_W, SCREEN_H);
	grafx_init();
	state_controller_init();
	//printf("init\n");
}

void core_main() {
	core_init();
	while (fcl_running) {
		SDL_SetRenderTarget(fvc_renderer, fvc_texture);
		state_controller_frame();
		fcl_update();
		if (keys[SDL_SCANCODE_ESCAPE]) fcl_running = 0;
		
	}
	printf("sdl quit\n");
	fcl_shutdown();
	return;
}
