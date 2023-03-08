#include "./grafx.c"


void core_init() {
	fcl_init();
	window_state_set_filename("kdocm");
	window_init("King Duck of Cluck Mountain");
	fvc_init(420, 200);
	grafx_init();
	//printf("init\n");
}

void core_main() {
	core_init();
	int xpos = 0;
	int running = 1;
	while (running) {
		SDL_SetRenderTarget(fvc_renderer, fvc_texture);
		fvc_set_draw_color(16);
		SDL_RenderFillRect(fvc_renderer, NULL);
		for (int i = 0; i < 16; i++) {
			fvc_set_draw_color(i);
			SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { xpos + (20 * i), 10, 15, 100 });
		}
		xpos++;
		if (xpos > 100) xpos = 0;
		int frame = (xpos >> 2) % 4;
		SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { frame * 20, 0, 20, 40 },
		&(SDL_Rect) { 100, 120, 20, 40 });
		SDL_RenderCopy(fvc_renderer, spriteshit, NULL, NULL);
		fcl_update();

		while (SDL_PollEvent(&event)) {
			fcl_event(event);
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = 0;
							break;
					}
					break;
			}
		}
	}
	printf("sdl quit\n");
	fcl_shutdown();
	return;
}
