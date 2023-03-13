
char hen_kills_text[5][64] = {
	"\"You, silly drake, are no",
	"                   mother plucker!",
	"     Rot like forgotten chicken feed...!\"",
};



void state_game_hen_kills() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[8]);

	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 75;
	text_rect.y = 30;

	// player dies
	player_hp = 0;
	ents[player_level][0].hp = 0;

	for (int i = 0; i < 5; i++) {
		font_render_text(hen_kills_text[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}
	state_game_press_space();
}
