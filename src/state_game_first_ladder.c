char nar_player_death[] = "'Twas I was never one for living much really meh n'anywayz.";


char nar_story[5][64] = {
	"\"Was it folly to enter Cluck Mountain??",
	"     Perhaps! But King Duck Shall Prevail!",

};



void state_game_first_ladder() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[8]);

	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 75;
	text_rect.y = 30;

	for (int i = 0; i < 5; i++) {
		font_render_text(nar_story[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}
	state_game_press_space();
}
