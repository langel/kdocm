#define state_id_gameplay 0
#define state_id_mapview 1

int state_game_id;


void state_game_init() {
}

void state_game_enter_level(int new_level) {
	int old_level = player_level;
	player_level = new_level;
	ents[player_level][0].hp = player_hp;
	ents[player_level][0].state = ents[old_level][0].state;
	map_playfield_render(player_level);
}


void state_game_new() {
	state_id = game;
	state_game_id = state_id_gameplay;
	player_game_new();
	map_handler_generate_all();
	for (int i = 0; i < map_levels; i++) {
		ents_init(i);
		ent_load_type(i, 0, ent_player);
		ents[i][0].xt = map_width >> 1;
		ents[i][0].yt = map_height >> 1;
	}
	ents[0][0].hp = player_hp;
	//ents[0][0].state = ent_state_player_controlled;
	ents[0][0].state = ent_state_wandering;
	state_game_enter_level(4);
	map_playfield_render(player_level);
	map_view_texture_update(player_level);
}


void state_game_frame() {
	player_hp = ents[player_level][0].hp;
	player_frame_counter++;
	
	if (state_game_id == state_id_gameplay) {
		state_game_play_frame();
	}
	if (state_game_id == state_id_mapview) {
		state_game_map_frame();
	}
}
