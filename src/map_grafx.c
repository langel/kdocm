SDL_Rect map_texture_rect = { 0, 0, map_width * 10, map_height * 10 };
SDL_Texture * map_texture;
SDL_Texture * map_view_texture;
int map_surface_width = map_width * 10;
int map_surface_height = map_height * 10;
int map_surface_size = map_width * 10 * map_height * 10 * 4;
uint32_t * map_surface_pixels;

int map_wall_pal[9][4] = {
	{ 2, 3, 4, 5 },
	{ 6, 5, 1, 7 },
	{ 2, 5, 6, 7 }, // herbs?
	{ 3, 5, 6, 7 },
	{ 4, 5, 6, 7 },
	{ 6, 2, 3, 5 },
	{ 4, 5, 7, 4 },
	{ 4, 6, 7, 1 },
	{ 5, 4, 6, 1 },
};

int tile_colors[8][4] = {
	{ 16, 16, 16, 16 }, // empty (uses no palette)
	{ 16, 16, 16, 16 }, // rock (uses different palette)
	{  5, 11, 12, 11 }, // water
	{  4,  6,  7,  8 }, // lava
	{  2,  4,  5,  5 }, // dirt
};

void map_grafx_init() {
	// setup map pixel ram and textures
	map_surface_pixels = malloc(map_surface_size);
	SDL_SetRenderTarget(fvc_renderer, NULL);
	map_texture = SDL_CreateTexture(fvc_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, map_width * 10, map_height * 10);
	SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
	map_view_texture = SDL_CreateTexture(fvc_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map_width * 2, map_height * 2);
}

// x,y = tile pos ; x2, y2 = pixel position of tile; mod = rate of pixel
int map_tile_pixel_visible(int map_level, int type, int x, int y, int x2, int y2, int mod) {
	if (x == 0 || y == 0 || x == map_width - 1 || y == map_height - 1) return 1;
	//return 1;
	int pxlrnd = (rand() % mod == 0);
	if (x2 < 4 && y2 < 4 && map_data[map_level][x-1][y-1] != type) return pxlrnd;
	else if (x2 < 2 && map_data[map_level][x-1][y] != type) return pxlrnd;
	else if (x2 < 4 && y2 > 6 && map_data[map_level][x-1][y+1] != type) return pxlrnd;
	else if (y2 > 7 && map_data[map_level][x][y+1] != type) return pxlrnd;
	else if (x2 > 7 && y2 > 6 && map_data[map_level][x+1][y+1] != type) return pxlrnd;
	else if (x2 > 7 && map_data[map_level][x+1][y] != type) return pxlrnd;
	else if (x2 > 6 && y2 < 4 && map_data[map_level][x+1][y-1] != type) return pxlrnd;
	else if (y2 < 2 && map_data[map_level][x][y-1] != type) return pxlrnd;
	else return 1;
}

void map_plot_wall_tile(int map_level, int x, int y) {
	int x1 = x * 10;
	int y1 = y * 10;
	SDL_Point map_pixel;
	int colors[4];
	for (int i = 0; i < 4; i++) colors[i] = map_wall_pal[map_level][i];
	int color_id;
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			if (map_tile_pixel_visible(map_level, 1, x, y, x2, y2, 7)) {
				color_id = colors[rng8() & 3];
				map_pixel.x = x1 + x2;
				map_pixel.y = y1 + y2;
				map_surface_pixels[map_pixel.x + map_pixel.y * map_surface_width] = surface_palette[color_id];
				if (y < map_height - 1) {
					map_surface_pixels[map_pixel.x + map_pixel.y * map_surface_width + 1] = surface_palette[color_id];
					map_surface_pixels[map_pixel.x + (map_pixel.y + 1) * map_surface_width] = surface_palette[color_id];
					map_surface_pixels[map_pixel.x + (map_pixel.y + 1) * map_surface_width + 1] = surface_palette[color_id];
				}
			}
		}
	}
}

void map_plot_tile(int map_level, int x, int y, int type) {
	int x1 = x * 10;
	int y1 = y * 10;
	SDL_Point map_pixel;
	int color_id;
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			if (map_tile_pixel_visible(map_level, 2, x, y, x2, y2, 5)) {
				color_id = tile_colors[type][rng8() & 3];
				map_pixel.x = x1 + x2;
				map_pixel.y = y1 + y2;
				map_surface_pixels[map_pixel.x + map_pixel.y * map_width * 10] = surface_palette[color_id];
			}
		}
	}
}

void map_playfield_render(int level) {
	// DRAW THE WHOLE MAP
	for (int i = 0; i < map_width * 10 * map_height * 10; i++) {
		map_surface_pixels[i] = (uint32_t) 0;
	}
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			int type = map_data[level][x][y];
			if (type == tile_rock) {
				map_plot_wall_tile(level, x, y);
			}
			if (type > tile_rock) {
				map_plot_tile(level, x, y, type);
			}
		}
	}
	SDL_UpdateTexture(map_texture, NULL, map_surface_pixels, map_surface_width * 4);
}


// XXX only show seent map tiles
void map_view_texture_update(int level) {
	SDL_Texture * stash = SDL_GetRenderTarget(fvc_renderer);
	// DRAW THE WHOLE MAP
	SDL_SetRenderTarget(fvc_renderer, map_view_texture);
	fvc_set_draw_color(7);
	SDL_Rect map_rect = { 0, 0, map_width * 2, map_height * 2 };
	SDL_RenderFillRect(fvc_renderer, &map_rect);
	SDL_Rect pixel = { 32, 20, 2, 2 };
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			int tile = map_data[level][x][y];
			if (tile == tile_empty) fvc_set_draw_color(7);
			if (tile == tile_rock) fvc_set_draw_color(6);
			if (tile == tile_water) fvc_set_draw_color(3);
			pixel.x = x << 1;
			pixel.y = y << 1;
			SDL_RenderFillRect(fvc_renderer, &pixel);
		}
	}
	SDL_SetRenderTarget(fvc_renderer, stash);
}

