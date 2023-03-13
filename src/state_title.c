
void state_title_frame() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	// title
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 0, 120, 300, 80 },
		&(SDL_Rect) { 60, 40, 300, 80 });
	// duck
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 380, 140, 40, 60 },
		&(SDL_Rect) { 340, 10, 40, 60 });
	// hen
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 140, 0, 40, 40 },
		&(SDL_Rect) { 50, 140, 40, 40 });
	// space
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.x = 180;
	text_rect.y = 140;
	text_rect.h = fonts[0].height;
	font_render_text("Press SPACE for Adventure", fonts[0], fvc_renderer, text_rect);
	if (keys[SDL_SCANCODE_SPACE] == 1) {	
		state_game_new();
	}
	// byline
	text_rect.y = 160;
	text_rect.h = fonts[0].height;
	font_render_text("7DRL MMXXIII puke7 / Langel", fonts[0], fvc_renderer, text_rect);
}
