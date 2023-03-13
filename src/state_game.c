
void state_game_press_space() {
	font_set_color(fonts[0], sdl_palette[8]);
	text_rect.x = 150;
	text_rect.y = 175;
	text_rect.h = fonts[0].height;
	font_render_text("Press SPACE to Continue", fonts[0], fvc_renderer, text_rect);
	if (keys[SDL_SCANCODE_SPACE] == 1) {	
		state_game_id = state_id_gameplay;
	}
}

#include "./state_game_play.c"
#include "./state_game_map.c"
#include "./state_game_hud.c"
#include "./state_game_first_ladder.c"
#include "./state_game_hen_gifts.c"
#include "./state_game_hen_kills.c"

void state_game_init() {
	state_game_hud_init();
}

void state_game_enter_level(int new_level) {
	player_update_level = 0;
	int old_level = player_level;
	player_level = new_level;
	ents[player_level][0].hp = player_hp;
	ents[player_level][0].state = ents[old_level][0].state;
	map_playfield_render(player_level);
	map_view_texture_update(player_level);
}


void state_game_new() {
	state_id = game;
	state_game_id = state_id_gameplay;
	player_game_new();
	map_handler_generate_all();
	ents[0][0].state = ent_state_player_controlled;
	//ents[0][0].state = ent_state_wandering;
	state_game_enter_level(0);
	map_playfield_render(player_level);
	map_view_texture_update(player_level);
	state_game_id = state_id_gameplay;
	//player_has_cleaver = 1;
	//player_has_feather = 1;
}


void state_game_frame() {
	if (player_update_level != 0) {
		state_game_enter_level(player_level + player_update_level);
	}
	player_hp = ents[player_level][0].hp;
	player_frame_counter++;

	if (keys[SDL_SCANCODE_TAB] == 1) {
		state_game_id = (state_game_id + 1) % 2;
		printf("tab\n");
	}
	switch(state_game_id) {
		case state_id_gameplay:
			state_game_play_frame();
			state_game_hud_render();
			break;
		case state_id_mapview:
			state_game_map_frame();
			break;
		case state_id_first_ladder:
			state_game_first_ladder();
			break;
		case state_id_hen_kills:
			state_game_hen_kills();
			break;
		case state_id_hen_gifts:
			state_game_hen_gifts();
			break;
	}
}
