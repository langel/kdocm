#define state_id_gameplay 0
#define state_id_mapview 1
#define state_id_first_ladder 2
#define state_id_hen_gifts 3
#define state_id_hen_kills 4

int state_game_id;

int player_level;
int player_gp;
int player_hp;
int player_hp_max;
int player_xp;
int player_steps;
int player_update_level;
int player_has_cleaver;
int player_has_feather;
int player_frame_counter;
int player_won;

void player_game_new() {
	player_hp_max = 144;
	player_hp = player_hp_max;
	player_xp = 0;
	player_gp = 0;
	player_level = 0; // dungeon/map level
	player_has_cleaver = 0;
	player_has_feather = 0;
	player_frame_counter = 0;
	player_won = 0;
}
