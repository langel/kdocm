
char hen_kills_text[5][64] = {
	"\"You, silly drake, are no",
	"                   mother plucker!",
	"     Rot like forgotten chicken feed...!\"",
};



void state_game_hen_kills() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	// hen
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 300, 120, 80, 80 },
		&(SDL_Rect) { 40, 40, 80, 80 });
	// duck
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 380, 140, 40, 60 },
		&(SDL_Rect) { 340, 110, 40, 60 });
	// render text arrays
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 150;
	text_rect.y = 30;
	for (int i = 0; i < 5; i++) {
		font_render_text(hen_kills_text[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}
	// player dies
	player_hp = 0;
	ents[player_level][0].hp = 0;
	state_game_press_space();
}
