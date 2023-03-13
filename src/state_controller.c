
enum states {
	title,
	help,
	game,
	crap_demo,
	map_test,
	congration,
} state_id;

#include "./state_game.c"
#include "./state_map_test.c"
#include "./state_crap_demo.c"
#include "./state_title.c"
#include "./state_congration.c"


void state_controller_init() {
	state_map_test_init();
	state_game_init();
	state_id = title;
}


void state_controller_frame() {
	if (player_won) {
		state_id = congration;
		player_won = 0;
		frame_counter = 0;
	}
	switch (state_id) {
		case crap_demo:
			state_crap_demo_frame();
			break;
		case map_test:
			state_map_test_frame();
			break;
		case title:
			state_title_frame();
			break;
		case help:
			break;
		case game:
			state_game_frame();
			break;
		case congration:
			state_congration_frame();
			break;
	}
}
