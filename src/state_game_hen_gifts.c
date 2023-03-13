
char hen_gifts_text[5][64] = {
	"\"You, mighty drake, are so",
	"     handsome and strong and a true",
	"        Mother Plucker for the ages!",
	"           Recieveth mine feather as tribute!\"",
};



void state_game_hen_gifts() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	// feather
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 160, 80, 40, 40 },
		&(SDL_Rect) { 130, 10, 40, 40 });
	// hen
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 300, 120, 80, 80 },
		&(SDL_Rect) { 40, 40, 80, 80 });
	// cleaver
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 120, 80, 40, 40 },
		&(SDL_Rect) { 315, 120, 40, 40 });
	// duck
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 380, 140, 40, 60 },
		&(SDL_Rect) { 340, 110, 40, 60 });
	// render text arrays
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 180;
	text_rect.y = 30;
	for (int i = 0; i < 5; i++) {
		font_render_text(hen_gifts_text[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}

	state_game_press_space();

}
