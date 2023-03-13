

// MAPS ARE 128 x 80 tiles
#define map_width 128
#define map_height 80
#define map_levels 12
#define map_room_min_x 4
#define map_room_min_y 5

#define tile_empty 0
#define tile_rock 1
#define tile_water 2
#define tile_lava 3
#define tile_dirt 4

int tile2color[5] = { 16, 3, 11, 6, 4 };
int map_data[map_levels][map_width][map_height];
int room_centers[16][2];

typedef struct map_level_rule_struct {
	int map_max_size[2];
	int room_max_size[2];
	int room_count;
	int debris_rock_count;
	int debris_water_count;
	int debris_lava_count;
	int debris_dirt_count;
} map_level_rules;

map_level_rules level_rules[map_levels] = {
	{ // level 1
		{  32, 20 }, // max map size
		{   3,  4 }, // max room size
		3, 128, 1024, 0, 32 },
	{ // level 2
		{  80, 50 },
		{  28, 14 },
		4, 256, 512, 0, 64 },
	{ // level 3
		{  70, 80 }, // max map size
		{  32, 20 }, // max room size
		5, 512, 256, 0, 128 },
	{ // level 4
		{  80, 50 }, // max map size
		{  40, 24 }, // max room size
		6, 512, 128, 0, 256 },
	{ // level 5
		{  70, 78 }, // max map size
		{   3,  2 }, // max room size
		7, 128, 64, 0, 512 },
	{ // level 6
		{  60, 40 }, // max map size
		{  20,  8 }, // max room size
		8, 1024, 32, 0, 256 },
	{ // level 7
		{  80, 50 }, // max map size
		{  32, 20 }, // max room size
		9, 512, 16, 0, 128 },
	{ // level 8
		{ 126, 78 },
		{  48, 32 },
		15, 1024, 8, 0, 64 },
	{ // level 9
		{  32, 20 }, // max map size
		{   3,  4 }, // max room size
		3, 256, 4, 0, 32 },
	{ // level 10 // macguffin quest
		{  28, 20 }, // max map size
		{  7, 5 }, // max room size
		3, 512, 16, 128, 64 },
	{ // level 11 // macguffin quest
		{ 126, 78 }, // max map size
		{   3,  2 }, // max room size
		15, 128, 0, 1024, 128 },
	{ // level 12 // macguffin quest
		{ 63, 39 }, // max map size
		{  20,  8 }, // max room size
		3, 1024, 0, 2048, 256 },
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

