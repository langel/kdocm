
void state_title_frame() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.x = 150;
	text_rect.y = 175;
	text_rect.h = fonts[0].height;
	font_render_text("Press SPACE for Adventure", fonts[0], fvc_renderer, text_rect);
	if (keys[SDL_SCANCODE_SPACE] == 1) {	
		state_game_new();
	}
}
