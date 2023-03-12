#define state_id_gameplay 0
#define state_id_mapview 1

int state_game_id;

#include "./state_game_play.c"
#include "./state_game_map.c"
#include "./state_game_hud.c"

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
	//ents[0][0].state = ent_state_player_controlled;
	ents[0][0].state = ent_state_wandering;
	state_game_enter_level(6);
	map_playfield_render(player_level);
	map_view_texture_update(player_level);
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
	
	if (state_game_id == state_id_gameplay) {
		state_game_play_frame();
		state_game_hud_render();
	}
	if (state_game_id == state_id_mapview) {
		state_game_map_frame();
	}
}
