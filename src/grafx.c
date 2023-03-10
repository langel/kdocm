


uint8_t palette[24][4] = {
	// 0
	{ 0xec, 0xe0, 0xd3, 0xff }, // beige
	{ 0xa6, 0xaf, 0xb7, 0xff }, // gray light
	{ 0x93, 0x7c, 0x65, 0xff }, // tan dark
	{ 0x62, 0x5c, 0x5a, 0xff }, // gray medium
	{ 0x37, 0x1b, 0x1b, 0xff }, // brown dark
	{ 0x71, 0x37, 0x25, 0xff }, // brown
	{ 0xb7, 0x3a, 0x2f, 0xff }, // red
	{ 0xe1, 0x7e, 0x39, 0xff }, // orange
	// 8
	{ 0xf2, 0xc2, 0x37, 0xff }, // yellow
	{ 0x6c, 0xa2, 0x39, 0xff }, // green light
	{ 0x36, 0x75, 0x3d, 0xff }, // green
	{ 0x3b, 0x4c, 0xa8, 0xff }, // blue
	{ 0x5f, 0x91, 0xc1, 0xff }, // blue light
	{ 0x6b, 0xc7, 0xab, 0xff }, // seafoam
	{ 0xd0, 0x58, 0x9f, 0xff }, // pink
	{ 0x8d, 0x55, 0xae, 0xff }, // violet
	// 16
	{ 0x2c, 0x2c, 0x2c, 0x2c }, // black
};

// used for writing bitmapped pixels to surfaces
uint32_t surface_palette[24];

SDL_Texture * spriteshit;

SDL_Texture * dirt_texture;


void grafx_init() {

	// convert paletter to indexed sdl colors	
	for (int i = 0; i < 16; i++) {
		fvc_set_color_index(i, palette[i][0], palette[i][1], palette[i][2]);
	}
	// convert palette for bitmap/surface usage
	for (int i = 0; i < 8; i++) {
		uint32_t color = 0;
		color += palette[i][0] << 24;
		color += palette[i][1] << 16;
		color += palette[i][2] << 8;
		color += 255;
		surface_palette[i] = color;
	}

	// load the spriteshit
	SDL_Surface * image = SDL_LoadBMP("assets/spriteshit.bmp");
	if (!image) {
		printf("ASSET LOAD ERROR: %s\n", SDL_GetError());
		exit(0);
	}
	printf("spriteshit pixel depth : %d\n", image->format->BitsPerPixel);
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 0)); 
	spriteshit = SDL_CreateTextureFromSurface(fvc_renderer, image);
	SDL_FreeSurface(image);

	// generate firt floor texture
	printf("creating dirt floor\n");
	uint32_t * dirt_pixels = malloc(SCREEN_W * SCREEN_H * 4);
	dirt_texture = SDL_CreateTexture(fvc_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H);
	for (int x = 0; x < SCREEN_W; x++) {
		for (int y = 0; y < SCREEN_H; y++) {
			int color_id = (rng8() & rng8() & rng8() & rng8() & rng8() & 13) ? 5 : 16;
			uint32_t dirt = 0;
			if (color_id == 16) {
				// add some noise to the dirt floor
				dirt += (palette[color_id][0] + (rand() % 16) - 8) << 24;
				dirt += (palette[color_id][1] + (rand() % 16) - 8) << 16;
				dirt += (palette[color_id][2] + (rand() % 16) - 8) << 8;
			}
			else dirt = 0x1f1f1f1f;
			dirt_pixels[x + y * SCREEN_W] = dirt;
		}
	}
	SDL_UpdateTexture(dirt_texture, NULL, dirt_pixels, SCREEN_W * 4);
	free(dirt_pixels);
}
