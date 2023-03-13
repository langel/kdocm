#define SCREEN_W 420
#define SCREEN_H 200

int frame_counter;
SDL_Rect text_rect;

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
	audio_init(32000, 2, 1024, AUDIO_F32SYS, &audio_callback);
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
	core_init();
	// XXX specific for dev pipeline
//	SDL_MinimizeWindow(window);
//	SDL_RestoreWindow(window);
//	SDL_RaiseWindow(window);
//	window_focus();
	frame_set_fps(60);
	while (fcl_running) {
		SDL_SetRenderTarget(fvc_renderer, fvc_texture);
		state_controller_frame();
		frame_counter++;
		frame_wait_next();
		fcl_update();
		if (keys[SDL_SCANCODE_ESCAPE]) fcl_shutdown();
	}
	fcl_quit();
	return;
}
