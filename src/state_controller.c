
enum states {
	title,
	help,
	game,
	crap_demo,
	map_test,
} state_id;

#include "./state_game_play.c"
#include "./state_game_map.c"
#include "./state_game.c"
#include "./state_map_test.c"
#include "./state_crap_demo.c"


void state_controller_init() {
	state_map_test_init();
	state_game_new();
}


void state_controller_frame() {
	switch (state_id) {
		case crap_demo:
			state_crap_demo_frame();
			break;
		case map_test:
			state_map_test_frame();
			break;
		case title:
			break;
		case help:
			break;
		case game:
			state_game_frame();
			break;
	}
}
