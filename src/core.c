#define SCREEN_W 420
#define SCREEN_H 200

#include "./grafx.c"

void core_init() {
	fcl_init();
	window_state_set_filename("kdocm");
	window_init("King Duck of Cluck Mountain");
	fvc_init(SCREEN_W, SCREEN_H);
	grafx_init();
	//printf("init\n");
}

void core_main() {
	core_init();
	int xpos = 0;
	int ypos = 0;
	while (fcl_running) {
		SDL_SetRenderTarget(fvc_renderer, fvc_texture);
		xpos++;
		if (xpos % 120 == 0) ypos++;
		// dirt floor
		int dirtx = xpos % SCREEN_W;
		int dirty = ypos % SCREEN_H;
		SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
			&(SDL_Rect) { dirtx - SCREEN_W, dirty - SCREEN_H, SCREEN_W, SCREEN_H });
		SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
			&(SDL_Rect) { dirtx, dirty, SCREEN_W, SCREEN_H });
		SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
			&(SDL_Rect) { dirtx - SCREEN_W, dirty, SCREEN_W, SCREEN_H });
		SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
			&(SDL_Rect) { dirtx, dirty - SCREEN_H, SCREEN_W, SCREEN_H });
		// color bars
		for (int i = 0; i < 16; i++) {
			fvc_set_draw_color(i);
			SDL_RenderFillRect(fvc_renderer, 
				&(SDL_Rect) { (xpos + (20 * i)) % SCREEN_W, 10, 15, 100 });
		}
		// king duck
		int frame = (xpos >> 2) % 4;
		SDL_RenderCopy(fvc_renderer, spriteshit, 
			&(SDL_Rect) { frame * 20, 0, 20, 40 },
			&(SDL_Rect) { 100, 120, 20, 40 });

		fcl_update();
		if (keys[SDL_SCANCODE_ESCAPE]) fcl_running = 0;

	}
	printf("sdl quit\n");
	fcl_shutdown();
	return;
}
