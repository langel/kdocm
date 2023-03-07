#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "./fcl/core.c"
#include "./src/core.c"



int main(int argc, char* args[]) {
	debug_output_target = all;
	debug_level = 4;
	debug_out(1, "King Duck of Cluck Mountain");
	core_main();
	return 0;
}
