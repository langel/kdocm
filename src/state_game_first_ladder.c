char nar_player_death[] = "'Twas I was never one for living much really meh n'anywayz.";


char nar_story[7][64] = {
	"\"I must appease those pleasant peasants for I,",
	"   KING DUCK, alone retrieved thee golden crown",
	"     from the Cave of Grell yet no respect was found",
	"       showered upon thineself! They claim I am no",
	"         Mother Plucker and shalt I proveth them wrong?",
	"                Was it folly to enter Cluck Mountain??",
	"                        Perhaps! But King Duck Shall Prevail!\"",
};



void state_game_first_ladder() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	// duck
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 180, 0, 60, 80 },
		&(SDL_Rect) { 340, 0, 60, 80 });
	// text
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.w = SCREEN_W;
	text_rect.h = fonts[0].height;
	text_rect.x = 40;
	text_rect.y = 20;
	for (int i = 0; i < 7; i++) {
		font_render_text(nar_story[i], fonts[0], fvc_renderer, text_rect);
		text_rect.y += 20;
	}
	state_game_press_space();
}
