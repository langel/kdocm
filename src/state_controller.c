#include "./state_crap_demo.c"
#include "./state_map_test.c"
#include "./state_map.c"

enum states {
	title,
	help,
	game_map,
	game_play,
	crap_demo,
	map_test,
} state_current;


void state_controller_init() {
	state_map_test_init();
	state_current = map_test;
}


void state_controller_frame() {
	switch (state_current) {
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
		case game_map:
			break;
		case game_play:
			break;
	}
}
