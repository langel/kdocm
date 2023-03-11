

typedef struct {
	int type;
	int dir; // right, up, left, down
	int xt; // tile positions
	int yt;
	int state;
	int hp;
	int collisions;
} ent;

#define ENTS_COUNT 128
ent ents[map_levels][ENTS_COUNT];

#define ent_state_dead 0
#define ent_state_wandering 1
#define ent_state_blocked 2
#define ent_state_dormant 3
#define ent_state_pursuit 4
#define ent_state_flee 5
#define ent_state_player_controlled 6

#define ent_nan 0
#define ent_player 1
#define ent_ladder_up 2
#define ent_ladder_down 3
#define ent_herb 4
#define ent_key 5
#define ent_coin 6
#define ent_coins 7
#define ent_chest 8
#define ent_chest_emptied 9
#define ent_mimic 10

// number of types per level
int map_ent_type_count[map_levels] = {0};
// number of ents per level
int map_ents_count[map_levels] = {0};
// ent types per level
int map_ent_types[map_levels][16] = {0};

typedef struct {
	int ent_types_count;
	int ent_types[16];
} map_ents_data_struct;

typedef struct {
	char name[16];
	int state;
	int hp;
	int damage_base;
	int damage_rand;
	char verb[16];
	SDL_Rect sprite;
	int xp;
} ent_type;

ent_type ent_types[42] = {
	{ "nan", ent_state_dead, 0, 0, 0, "does not exist", 
		{ 0, 0, 0, 0 }, 0 },
	{ "player", ent_state_wandering,	42, 10, 10, "quacks", 
		{ 0, 0, 20, 40 }, 0 },
	{ "ladder up", ent_state_dormant, 
		0, 0, 0, "ascends",
		{ 80, 0, 20, 20 }, 13 },
	{ "ladder down", ent_state_dormant, 
		0, 0, 0, "descends",
		{ 100, 0, 20, 20 }, 13 },
	{ "herb", ent_state_dormant, 0, 0, 0, "heals", 
		{ 0, 60, 20, 9 }, 0
	},
	{ "key", ent_state_dormant, 
		0, 0, 0, "unlocks",
		{ 0, 45, 10, 4 }, 0 },
	{ "coin",
		ent_state_dormant, 0, 0, 0, "plinks",
		{ 0, 52, 7, 3 }, 0 },
	{ "coins",
		ent_state_dormant, 0, 0, 0, "changles",
		{ 10, 51, 7, 7 }, 0 },
	{ "chest",
		ent_state_dormant, 0, 0, 0, "opens",
		{ 20, 40, 20, 20 }, 0 },
	{ "empty chest", ent_state_dead, 0, 0, 0, "sits",
		{ 40, 40, 20, 20 }, 0 },
	{ "mimic", ent_state_wandering, 
		43, 12, 12, "mawls",
		{ 60, 40, 20, 20 }, 120 },
};
