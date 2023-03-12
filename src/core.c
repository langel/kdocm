#define SCREEN_W 420
#define SCREEN_H 200

int frame_counter;

#include "./grafx.c"
#include "./font.c"
#include "./sfx.c"
#include "./player.c"
#include "./camera.c"
#include "./map_data.c"
#include "./ent_data.c"
#include "./fov.c"
#include "./action_log.c"
#include "./ent_handler.c"
#include "./cavern_gen.c"
#include "./map_handler.c"
#include "./map_grafx.c"
#include "./state_controller.c"

void core_init() {
	fcl_init();
	window_state_set_filename("kdocm");
	window_init("King Duck of Cluck Mountain");
	dpipe_init("src/state_game_play.c");
	fvc_init(SCREEN_W, SCREEN_H);
	font_init();
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
