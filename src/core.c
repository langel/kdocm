
SDL_Event event;


uint8_t palette[16][4] = {
	{ 0xec, 0xe0, 0xd3, 0xff }, // beige
	{ 0xa6, 0xaf, 0xb7, 0xff }, // gray light
	{ 0x93, 0x7c, 0x65, 0xff }, // tan dark
	{ 0x62, 0x5c, 0x5a, 0xff }, // gray medium
	{ 0x37, 0x1b, 0x1b, 0xff }, // brown dark
	{ 0x71, 0x37, 0x25, 0xff }, // brown
	{ 0xb7, 0x3a, 0x2f, 0xff }, // red
	{ 0xe1, 0x7e, 0x39, 0xff }, // orange
	{ 0xf2, 0xc2, 0x37, 0xff }, // yellow
	{ 0x6c, 0xa2, 0x39, 0xff }, // green light
	{ 0x36, 0x75, 0x3d, 0xff }, // green
	{ 0x3b, 0x4c, 0xa8, 0xff }, // blue
	{ 0x5f, 0x91, 0xc1, 0xff }, // blue light
	{ 0x6b, 0xc7, 0xab, 0xff }, // seafoam
	{ 0xd0, 0x58, 0x9f, 0xff }, // pink
	{ 0x8d, 0x55, 0xae, 0xff }, // violet
};


void core_init() {
	SDL_Init(SDL_INIT_EVERYTHING);
//	keyboard_init();
	fcl_window_create("King Duck of Cluck Mountain", 1024, 576);
	fvc_init(420, 200);
	for (int i = 0; i < 16; i++) {
		fvc_set_color_index(i, palette[i][0], palette[i][1], palette[i][2]);
		fvc_set_draw_color(i);
		SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { 10 + (20 * i), 10, 15, 100 });
	}
	SDL_RenderPresent(fvc_renderer);
	printf("init\n");
}

void core_main() {
	core_init();
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
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
	SDL_Quit();
	return;
}
