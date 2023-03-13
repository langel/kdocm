
char hen_gifts_text[5][64] = {
	"\"You, mighty drake, are so",
	"      handsome and strong and a true",
	"            mother plucker for the ages!",
	"",
	"     Recieveth mine feather as tribute!\"",
};



void state_game_hen_gifts() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[8]);

	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 75;
	text_rect.y = 30;

	for (int i = 0; i < 5; i++) {
		font_render_text(hen_gifts_text[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}

	state_game_press_space();

}
