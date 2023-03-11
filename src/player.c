
int player_level;
int player_gp;
int player_hp;
int player_hp_max;
int player_xp;
int player_steps;
int player_update_level;
int player_has_cleaver;
int player_frame_counter;

void player_game_new() {
	player_hp_max = 144;
	player_hp = player_hp_max;
	player_xp = 0;
	player_gp = 0;
	player_level = 0; // dungeon/map level
	player_has_cleaver = 0;
	player_frame_counter = 0;
}
