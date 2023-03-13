
SDL_Rect congration_title_sprite = { 0, 120, 420, 80};
SDL_Rect congration_title_rect = { 0, 110, 420, 80};
SDL_Rect congration_text_rect = { 60, 120, 300, 0 };


void state_congration_frame() {
	// bg
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	// cleaver
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 120, 80, 40, 40 },
		&(SDL_Rect) { 10, 30, 40, 40 });
	// feather
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 160, 80, 40, 40 },
		&(SDL_Rect) { 80, 15, 40, 40 });
	// duck
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 180, 0, 60, 80 },
		&(SDL_Rect) { 40, 10, 60, 80 });
	// title of game
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 0, 120, 380, 80 },
		&(SDL_Rect) { 20, 110, 380, 80 });
	// congration text
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 200, 80, 220, 30 },
		&(SDL_Rect) { 140, 10, 220, 30 });
	// copy text
	font_set_color(fonts[0], sdl_palette[0]);
	congration_text_rect.x = 130;
	congration_text_rect.y = 45;
	congration_text_rect.h = fonts[0].height;
	font_render_text("Thou art nownth skillethed with cleaver and feather!", fonts[0], fvc_renderer, congration_text_rect);
	// xp / gp / time
	font_set_color(fonts[1], sdl_palette[1]);
	congration_text_rect.x = 140;
	congration_text_rect.y = 70;
	congration_text_rect.h = fonts[1].height;
	char str[64];
	int tf = player_frame_counter % 60;
	int ts = ((player_frame_counter - tf) % 3600) / 60;
	int tm = (player_frame_counter - ts - tf) / 3600;
	sprintf(str, "%d xp   %d gp   %02d:%02d.%02d", player_xp, player_gp, tm, ts, tf);
	font_render_text(str, fonts[1], fvc_renderer, congration_text_rect);

	// SPACEBAR START?
	if (keys[SDL_SCANCODE_SPACE]) {
		state_id = 0;
	}
	if (frame_counter % 15 == 0) {
		if (frame_counter < 120) sfx_congration();
	}
}
