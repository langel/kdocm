
SDL_Rect hud_rect = { 320, 0, 100, 200 };
SDL_Rect hud_title_rect;


void state_game_hud_init() {
	hud_title_rect = (SDL_Rect) { 330, 2, 100, fonts[0].height };
}


void state_game_hud_render() {
	// clear hud space
	fvc_set_draw_color(17);
	SDL_RenderFillRect(fvc_renderer, &hud_rect);
	// title of game
	hud_title_rect.h = fonts[0].height;
	font_set_color(fonts[0], fvc_colors[1]);
	hud_title_rect.x = 330;
	hud_title_rect.y = 2;
	font_render_text("King Duck of", fonts[0], fvc_renderer, hud_title_rect);
	hud_title_rect.y = 14;
	font_render_text("Cluck Mountain", fonts[0], fvc_renderer, hud_title_rect);
	// footer
	font_set_color(fonts[2], fvc_colors[1]);
	hud_title_rect.y = 188;
	hud_title_rect.x = 322;
	hud_title_rect.h = fonts[2].height;
	font_render_text("#7DRL  2023  puke7", fonts[2], fvc_renderer, hud_title_rect);

	// PLAYER DATA
	hud_title_rect.x = 320;
	hud_title_rect.y = 48;
	hud_title_rect.h = fonts[0].height;
	SDL_Rect text = { 325, 30, 100, fonts[0].height };
	font_set_color(fonts[0], fvc_colors[0]);
	char words[32];
	// Health
	if (player_hp >= 0) sprintf(words, "Health  %d/%d", player_hp, player_hp_max);
	else sprintf(words, "Player Died.");
	font_render_text(words, fonts[0], fvc_renderer, text);
	// GP
	text.y += fonts[0].height;
	sprintf(words, "GP   %d", player_gp);
	font_render_text(words, fonts[0], fvc_renderer, text);
	// XP 
	text.y += fonts[0].height;
	sprintf(words, "XP   %d", player_xp);
	font_render_text(words, fonts[0], fvc_renderer, text);
	// Level 
	text.y += fonts[0].height;
	sprintf(words, "Depth   %1X", player_level + 1);
	font_render_text(words, fonts[0], fvc_renderer, text);

	// action text
	text.y += 10;
	font_set_color(fonts[2], fvc_colors[0]);
	text.h = fonts[2].height;
	text.y += fonts[2].height;
	int action_h = 8;
	// action log 1
   font_render_text(action_log_0[0], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_0[1], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_0[2], fonts[2], fvc_renderer, text);
	text.y += action_h;
	// action log 2
	text.y += 5;
   font_render_text(action_log_1[0], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_1[1], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_1[2], fonts[2], fvc_renderer, text);
	text.y += action_h;
	// action log 3
	text.y += 5;
   font_render_text(action_log_2[0], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_2[1], fonts[2], fvc_renderer, text);
	text.y += action_h;
   font_render_text(action_log_2[2], fonts[2], fvc_renderer, text);

	/*
	SDL_Rect ent_label_border = { 330, 32, 32, 10 };
	SDL_Rect ent_label_fill = { 332, 34, 28, 6 };
	SDL_Rect ent_label_text = { 380, 30, 28, fonts[0].height };
	for (int i = 0; i < 8; i++) {
		// ent border
		set_render_color(fvc_renderer, 0);
		SDL_RenderDrawRect(fvc_renderer, &ent_label_border);
		ent_label_border.y += 20;
		// ent fill
		set_render_color(fvc_renderer, i);
		SDL_RenderFillRect(fvc_renderer, &ent_label_fill);
		ent_label_fill.y += 20;
		// ent text
		char coll[10];
		sprintf(coll, "%d", ents[i].collisions);
		font_render_text(coll, fonts[0], fvc_renderer, ent_label_text);
		ent_label_text.y += 20;
	}
	*/
}


