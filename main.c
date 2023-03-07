// gives program stdout access
#define SDL_MAIN_HANDLED

#include "./lib/core.c"
#include "./fcl/core.c"
#include "./src/core.c"



int main(int argc, char* args[]) {
	debug_output_target = all;
	debug_level = 4;
	debug_out(1, "King Duck of Cluck Mountain");
	core_main();
	return 0;
}
