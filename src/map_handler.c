
// MAPS ARE 128 x 80 tiles
#define map_width 128
#define map_height 80
#define map_levels 12
#define map_room_min_x 4
#define map_room_min_y 5

int map_data[map_levels][map_width][map_height];

typedef struct map_level_rules {
	int map_max_size[2];
	int room_max_size[2];
	int room_count;
	int debris_rock_count;
	int debris_water_count;
	int debris_lava_count;
} map_level_rules;

map_level_rules level_rules[map_levels] = {
	{ // level 1
		{  32, 20 }, // max map size
		{   3,  4 }, // max room size
		3, 128, 1024, 0 },
	{ // level 2
		{  80, 50 },
		{  28, 14 },
		9, 256, 512, 0 },
	{ // level 3
		{ 126, 78 }, // max map size
		{  32, 20 }, // max room size
		9, 512, 256, 0 },
	{ // level 4
		{  80, 50 }, // max map size
		{  40, 24 }, // max room size
		5, 512, 128, 0 },
	{ // level 5
		{ 126, 78 }, // max map size
		{   3,  2 }, // max room size
		9, 128, 64, 0 },
	{ // level 6
		{ 126, 78 }, // max map size
		{  20,  8 }, // max room size
		9, 1024, 32, 0 },
	{ // level 7
		{  80, 50 }, // max map size
		{  32, 20 }, // max room size
		9, 512, 16, 0 },
	{ // level 8
		{ 126, 78 },
		{  48, 32 },
		15, 1024, 8, 0 },
	{ // level 9
		{  32, 20 }, // max map size
		{   3,  4 }, // max room size
		3, 256, 4, 0 },
	{ // level 10 // macguffin quest
		{  80, 50 }, // max map size
		{  40, 24 }, // max room size
		5, 512, 16, 128 },
	{ // level 11 // macguffin quest
		{ 126, 78 }, // max map size
		{   3,  2 }, // max room size
		2, 128, 0, 1024 },
	{ // level 12 // macguffin quest
		{ 126, 78 }, // max map size
		{  20,  8 }, // max room size
		3, 1024, 0, 2048 },
};

// 1 : 3 rooms
// 2 : normal
// 3 : normal
// 4 : some water
// 5 : tiny rooms
// 6 : giant lake
// 7 : normal many grell
// 8 : giant rooms full of grell
// 9 : 3 rooms - 1 crown

// 0 is empty  16 (no color)
// 1 is rock   3
// 2 is water  11
// 3 is lava   6
// 3 is dirt   4

int tile2color[5] = { 16, 3, 11, 6, 4 };

// each tile type has 4 colors associated


void map_handler_generate_all(uint32_t seed) {
	// clear all map data with rocks
	for (int a = 0; a < map_levels; a++) {
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				map_data[a][x][y] = 4;
			}
		}
	}
	rng_reset(1337);
	int room_centers[16][2];
	for (int a = 0; a < map_levels; a++) {
		// make rooms	
		map_level_rules * level = &level_rules[a];
		for (int r = 0; r < level->room_count; r++) {
			SDL_Rect room;
			room.w = rngn() % level->room_max_size[0] + map_room_min_x;
			room.h = rngn() % level->room_max_size[1] + map_room_min_y;
			room.x = (map_width - level->map_max_size[0]) / 2 + (rngn() % (level->map_max_size[0] - room.w - 4)); 
			room.y = (map_height - level->map_max_size[1]) / 2 + (rngn() % (level->map_max_size[1] - room.h - 4)); 
			for (int x = room.x; x < room.x + room.w; x++) {
				for (int y = room.y; y < room.y + room.h; y++) {
					map_data[a][x][y] = 0;
				}
			}
			// cache room center position
			room_centers[r][0] = room.x + room.w / 2;
			room_centers[r][1] = room.y + room.h / 2;
		}
		// add rock debris
		for (int i = 0; i < level->debris_rock_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = 1;
		}
		// add water debris
		for (int i = 0; i < level->debris_water_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = 2;
		}
		// add lava debris
		for (int i = 0; i < level->debris_lava_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = 3;
		}

		// carve corridors between rooms
		for (int i = 1; i < level->room_count; i++) {
			// corridor cut outs between cavities
			int target = rngn() % (i);
			//printf("attaching cavity %d to cavity %d\n", i, target);
			// current room
			int crx = room_centers[i][0];
			int cry = room_centers[i][1];
			// target room
			int trx = room_centers[target][0];
			int try = room_centers[target][1];
			//printf("target room center x, y : %d, %d\n", tcx, tcy);
			if (crx >= trx) for (int x = trx; x <= crx; x++) {
				map_data[a][x][cry] = 0;		
			}
			else for (int x =  crx; x <= trx; x++) {
				map_data[a][x][cry] = 0;
			}
			if (cry >= try) for (int y = try; y <= cry; y++) {
				map_data[a][trx][y] = 0;
			}
			else for (int y =  cry; y <= try; y++) {
				map_data[a][trx][y] = 0;
			}
		}

	}
}
