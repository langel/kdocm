

SDL_Texture * state_map_test_texture;


void state_map_new_map() {
	map_handler_generate_all();
	SDL_SetRenderTarget(fvc_renderer, state_map_test_texture);
	fvc_set_draw_color(16);
	SDL_RenderFillRect(fvc_renderer, NULL);
	int mapx = 9;
	int mapy = 14;
	for (int a = 0; a <= 6; a++) {
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				int tile = map_data[a][x][y];
				fvc_set_draw_color(tile2color[tile]);
				SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { mapx + x, mapy + y, 1, 1 });
			}
		}
		mapx += 9 + map_width;
		if (a == 3) {
			mapx = 9;
			mapy += 13 + map_height;
		}
	}
	cav_generate(20, 20);
	for (int x = 0; x < SCREEN_W; x++) {
		for (int y = 0; y < SCREEN_H; y++) {
			int tile = cav_data[x][y];
			fvc_set_draw_color(tile2color[tile]);
			SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { x, y, 1, 1 });
		}
	}
}

void state_map_test_init() {
	rng_reset(1337);
	state_map_test_texture = fvc_texture_create(SCREEN_W, SCREEN_H);
	state_map_new_map();
}

void state_map_test_frame() {
	static int xpos = 0;
	SDL_SetRenderTarget(fvc_renderer, fvc_texture);
	SDL_RenderCopy(fvc_renderer, state_map_test_texture, NULL, NULL);
	if (keys[SDL_SCANCODE_SPACE] == 1) state_map_new_map();
	// king duck
	int frame = (xpos >> 2) % 4;
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { frame * 20, 0, 20, 40 },
		&(SDL_Rect) { 100, 120, 20, 40 });
}
